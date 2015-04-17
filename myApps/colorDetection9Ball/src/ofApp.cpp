#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	#ifdef _USE_LIVE_VIDEO
	// camera
	grabber.initGrabber(capWidth, capHeight);
	#else
	player.loadMovie("9_ball_game.mov");
	player.play();
	#endif
	
	// gui
	panel.setup();
	reset.setup("reset");
	reset.addListener(this, &ofApp::resetRange);
	panel.add(&reset);
	minHue.setup("min hue", 15, 0, 255);
	panel.add(&minHue);
	maxHue.setup("max hue", 116, 0, 255);
	panel.add(&maxHue);
	minSaturation.setup("min saturation", 3, 0, 255);
	panel.add(&minSaturation);
	maxSaturation.setup("max saturation", 96, 0, 255);
	panel.add(&maxSaturation);
	minValue.setup("min value", 173, 0, 255);
	panel.add(&minValue);
	maxValue.setup("max value", 255, 0, 255);
	panel.add(&maxValue);}

//--------------------------------------------------------------
void ofApp::update(){
	
	ofColor color;
	color.setHsb((minHue + maxHue) / 2.0f, (minSaturation + maxSaturation) / 2.0f, (minValue + maxValue) / 2.0f);
	ofBackground(color);

	bool isFrameNew = false;
	
	#ifdef _USE_LIVE_VIDEO
	grabber.update();
	isFrameNew = grabber.isFrameNew();
	#else
	player.update();
	isFrameNew = player.isFrameNew();
	isFrameNew = true;
	#endif
	if(isFrameNew){
		
		// get rgb color image
		#ifdef _USE_LIVE_VIDEO
		colorImgRgb.setFromPixels(grabber.getPixels(), capWidth, capHeight);
		#else
		colorImgRgb.setFromPixels(player.getPixels(), capWidth, capHeight);
		#endif
		
		// get hsv color image
		colorImgHsv = colorImgRgb;
		colorImgHsv.convertRgbToHsv();
		
		// get specific color
		colorImgRng = colorImgHsv;
		unsigned char* pixelsRng = colorImgRng.getPixels();
		int length = capWidth * 3 * capHeight;
		for(int i = 0; i < length; i += 3){
			if(minHue <= pixelsRng[i + 0] && pixelsRng[i + 0] <= maxHue &&
				minSaturation <= pixelsRng[i + 1] && pixelsRng[i + 1] <= maxSaturation &&
				minValue <= pixelsRng[i + 2] && pixelsRng[i + 2] <= maxValue){
				pixelsRng[i + 0] = 255;
				pixelsRng[i + 1] = 255;
				pixelsRng[i + 2] = 255;
			}else{
				pixelsRng[i + 0] = 0;
				pixelsRng[i + 1] = 0;
				pixelsRng[i + 2] = 0;
			}
		}
		
		// cancel noise
		grayImgCclNis = colorImgRng;
		// opening
		grayImgCclNis.erode();
		grayImgCclNis.erode();
		grayImgCclNis.dilate();
		grayImgCclNis.dilate();
		// closing
		grayImgCclNis.dilate();
		grayImgCclNis.erode();
		
		// find contour
		contourFinder.findContours(grayImgCclNis, 20, capWidth * capHeight / 5, 5, true);
		
		// find best contour
		vector<ofxCvBlob> blobs =  contourFinder.blobs;
		ofPoint maxAreaPoint;
		float maxArea = 0.0f;
		for(int i = 0, size = blobs.size(); i < size; i++){
			if(blobs[i].area > maxArea){
				maxArea = blobs[i].area;
				maxAreaPoint = blobs[i].boundingRect.getCenter();
			}
		}
		
		maxAreaPoints.push_back(maxAreaPoint);
		
		// keep points of 5 frame
		while(maxAreaPoints.size() > 20){
			maxAreaPoints.erase(maxAreaPoints.begin());
		}
		
		ofPoint avgPoint = ofPoint(0, 0);
		for(int i = 0; i < maxAreaPoints.size(); i++){
			avgPoint += maxAreaPoints[i];
		}
		if(maxAreaPoints.size() > 0){
			avgPoint /= maxAreaPoints.size();
		}
		
		float maxDistance = ofGetWidth();
		for(int i = 0; i < blobs.size(); i++){
			ofPoint vec = avgPoint - blobs[i].boundingRect.getCenter();
			float distance = sqrt(pow(vec.x, 2.0f) + pow(vec.y, 2.0f));
			if(distance < maxDistance){
				maxDistance = distance;
				point = blobs[i].boundingRect.getCenter();
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	int margin = 20;
	
	ofSetColor(255);
	int width = ofGetWidth() / 3 - margin * 2;
	int height = ofGetHeight() / 3 - margin * 2;
	colorImgRgb.draw(margin, margin, width, height);
	colorImgHsv.draw(width + margin * 3, margin, width, height);
	colorImgRng.draw(width * 2 + margin * 5, margin, width, height);
	grayImgCclNis.draw(margin, height + margin * 3, width, height);
	contourFinder.draw(width + margin * 3, height + margin * 3, width, height);
	
	float x = point.x * width / capWidth;
	float y = point.y * height / capHeight;
	ofNoFill();
	ofSetColor(255, 0, 0);
	ofCircle(width * 2 + margin * 5 + x, height + margin * 3 + y, 10);
	
	ofSetColor(255);
	ofFill();
	colorImgRgb.draw(width + margin * 3, height * 2 + margin * 5, width, height);
	
	ofNoFill();
	ofSetColor(255, 0, 0);
	ofCircle(width + margin * 3 + x, height * 2 + margin * 5 + y, 10);
	ofFill();
	
	panel.draw();
	
	ofSetColor(0);
	ofDrawBitmapString("original", width / 2, margin * 2 + height);
	ofDrawBitmapString("rgb -> hsv", width * 3 / 2, margin * 2 + height);
	ofDrawBitmapString("detect specific color", width * 5 / 2, margin * 2 + height);
	ofDrawBitmapString("remove noise by erode and dilate", width / 4, (margin * 2 + height) * 2);
	ofDrawBitmapString("find contours", width * 3 / 2, (margin * 2 + height) * 2);
	ofDrawBitmapString("choose best contour", width * 5 / 2, (margin * 2 + height) * 2);
	ofDrawBitmapString("result", width * 3 / 2 + margin, (margin * 2 + height) * 3 - margin / 2);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

	#ifndef _USE_LIVE_VIDEO
	if(player.isPlaying()){
		player.setPaused(true);
	}else{
		player.setPaused(false);
	}
	#endif
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::resetRange(){
	
	minHue = 0;
	maxHue = 255;
	minSaturation = 0;
	maxSaturation = 255;
	minValue = 0;
	maxValue = 255;
}
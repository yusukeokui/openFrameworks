#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	ofToggleFullscreen();
	
	ofBackground(0);
	ofSetBackgroundAuto(false);
	
	cam.initGrabber(320, 240);
	
	regionSize = 30;
	xRegionsCnt = cam.getWidth() / regionSize;
	yRegionsCnt = cam.getHeight() / regionSize;
	for(int i = 0, size = xRegionsCnt * yRegionsCnt; i < size; i++){
		ofVec2f f;
		flows.push_back(f);
	}
	
	int index = 0;
	for(int i = -3; i <= 3; i += 3){
		for(int j = -2; j <= 2; j += 2){
			pair<int, int> pair;
			pair.first = xRegionsCnt / 2 + i;
			pair.second = yRegionsCnt / 2 + j;
			posPair[index] = pair;
			index++;
		}
	}
}

//--------------------------------------------------------------
void ofApp::update(){

	cam.update();
	
	if(cam.isFrameNew()){
		flow.setWindowSize(8);
		flow.calcOpticalFlow(cam);
		
		for(int i = 0; i < yRegionsCnt; i++){
			for(int j = 0; j < xRegionsCnt; j++){
				int x = j * regionSize;
				int y = i * regionSize;
				ofVec2f avg = flow.getAverageFlowInRegion(ofRectangle(x, y, regionSize, regionSize));
				flows[xRegionsCnt * i + j].x = avg.x;
				flows[xRegionsCnt * i + j].y = avg.y;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	imageCnt++;
	if(imageCnt % 60 == 0){
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		ostringstream oss;
		oss << "./images/" << imageCnt << ".jpg";
		image.saveImage(oss.str());
	}
	
	float camWidth = cam.getWidth();
	float camHeight = cam.getHeight();
	float scaleX = ofGetWidth() / camWidth;
	float scaleY = ofGetHeight() / camHeight;

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	
	ofSetColor(0, 0, 0, 10);
	ofRect(0, 0, 1, camWidth * scaleX, camHeight * scaleY);
	
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	
	ofVec2f torque;
	
	for(int i = 0; i < yRegionsCnt; i++){
		for(int j = 0; j < xRegionsCnt; j++){
			
			bool isMatch = false;
			for(int k = 0; k < 9; k++){
				if(j == posPair[k].first && i == posPair[k].second){
					isMatch = true;
					break;
				}
			}
			if(!isMatch) continue;
			
			ofVec2f start(j * regionSize + regionSize / 2, i * regionSize + regionSize / 2);
			ofVec2f end = start + flows[xRegionsCnt * i + j];
			ofVec2f vec = end - start;
			
			start *= ofVec2f(scaleX, scaleY);
			end *= ofVec2f(scaleX, scaleY);
			
			if(pow(vec.length(), 2.0f) > 50){
				
//				ofSetColor(0, 255, 255, 10);
//				float rectSizeX = regionSize * scaleX;
//				float rectSizeY = regionSize * scaleY;
//				ofCircle(start, rectSizeY / 3);
				
				int min = 100;
				int max = 255;
				brush.setup(30, 2, 10, ofColor(ofRandom(min, max), ofRandom(min, max), ofRandom(min, max)));
				brush.draw(start, end - start);
			}
		}
	}
	
	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofSetColor(255);
	cam.draw(ofGetWidth() - camWidth, ofGetHeight() - camHeight, camWidth, camHeight);
	
	ofSetColor(0, 0, 0,220);
	ofRect(ofGetWidth() - camWidth, ofGetHeight() - camHeight, camWidth, camHeight);
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

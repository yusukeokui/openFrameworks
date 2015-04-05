#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	cam.initGrabber(320, 240);
	
	ofEnableDepthTest();
	ofEnableLighting();
	light.setPosition(100, -1000, 0);
	light.enable();
	
	regionSize = 30;
	xRegionsCnt = cam.getWidth() / regionSize;
	yRegionsCnt = cam.getHeight() / regionSize;
	for(int i = 0, size = xRegionsCnt * yRegionsCnt; i < size; i++){
		ofVec2f f;
		flows.push_back(f);
	}
	
	box.setup(30, 0.01f);
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
	
	float camWidth = cam.getWidth();
	float camHeight = cam.getHeight();
	
	ofScale(ofGetWidth() / camWidth, ofGetHeight() / camHeight);

	ofSetColor(255);
	cam.draw(0, 0, camWidth, camHeight);
	
	ofSetColor(0, 0, 0, 220);
	ofRect(0, 0, 1, camWidth, camHeight);
	
//	ofSetColor(255, 0, 0);
//	flow.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	int range = 2;
	ofVec2f torque;
	
	for(int i = 0; i < yRegionsCnt; i++){
		for(int j = 0; j < xRegionsCnt; j++){
			
			if(i < yRegionsCnt / 2 - range || i > yRegionsCnt / 2 + range
			   || j < xRegionsCnt / 2 - range || j > xRegionsCnt / 2 + range){
				continue;
			}
			
			ofVec2f start(j * regionSize + regionSize / 2, i * regionSize + regionSize / 2);
			ofVec2f end = start + flows[xRegionsCnt * i + j];
			ofVec2f vec = end - start;
			
			if(pow(vec.length(), 2.0f) > 50){
				if(showFlow){
					ofSetColor(255, 255, 255);
					ofLine(start.x, start.y, 2, end.x, end.y, 2);
			
					ofSetColor(0, 255, 255);
					ofCircle(end.x, end.y, 2, 1);
				}
				
				torque += flows[xRegionsCnt * i + j];
			}
		}
	}
	
	ofSetColor(0, 255, 255, 255);
	box.draw(camWidth / 2, camHeight / 2, torque / 50.0f);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	switch(key){
			case 's':
			showFlow = true;
			break;
			case 'h':
			showFlow = false;
			break;
	}
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

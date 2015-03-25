#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);
	
	ofSetBackgroundAuto(false);
	
	dummyMouse.setup(ofGetWidth(), ofGetHeight());
	
	for(int i = 0; i < PARTICLE_NUM; i++){
		bool isClock;
		if(ofRandom(1) > 0.5f){
			isClock = true;
		}else{
			isClock = false;
		}
		float x = ofRandom(ofGetHeight()) + (ofGetWidth() - ofGetHeight()) / 2.0f;
		float y = ofRandom(ofGetHeight());
		ofColor color = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
		myParticles[i].setup(ofVec2f(x, y), ofRandom(radius / 6, radius / 2), isClock, color);
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	
	dummyMouse.update(ofGetWidth(), ofGetHeight());

	for(int i = 0; i < PARTICLE_NUM; i++){
		myParticles[i].update(ofVec2f(dummyMouse.x, dummyMouse.y), 100.0f);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	ofSetColor(0, 10);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	for(int i = 0; i < PARTICLE_NUM; i++){
		myParticles[i].draw();
	}
	
//	ofSetColor(255, 0, 0);
//	ofCircle(mouseX, mouseY, radius);
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

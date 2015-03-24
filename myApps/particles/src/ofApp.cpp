#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
//	ofxGuiSetFont("Questrial-Regular.ttf",10,true,true);
	ofxGuiSetTextPadding(4);
	ofxGuiSetDefaultWidth(300);
	ofxGuiSetDefaultHeight(18);
	
	gui.setup("panel");
	
	// Gushing Circle
	for(int i = 0; i < GUSHING_CIRCLES_NUM; i++){
		
		ofColor circleColor(ofRandom(255) / 1.5f, ofRandom(255) / 1.5f, 255, ofRandom(255));
		gushingCircles[i].init(circleColor);
	}
	
	// Gravity Circle
	for(int i = 0; i < GRABITY_RECTS_NUM; i++){
		
		gravityRects[i].init(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
		gravityRects2[i].init(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()));
	}
	
	// Bright Circle
	for(int i = 0; i < BRIGHT_CIRCLES_NUM; i++){
	
		brightCircles[i].setup(ofGetWidth(), ofGetHeight());
	}
}

//--------------------------------------------------------------
void ofApp::update(){
	
	int width = ofGetWidth();
	int height = ofGetHeight();
	
	if(isGushingCircle){
		for(int i = 0; i < GUSHING_CIRCLES_NUM; i++){
			gushingCircles[i].update(mouseX, mouseY, width, height, radius, GRABITY);
		}
	}else if(isBrightTrajectoryCircle){
		vector<BrightTrajectoryCircle> tmpVector;
		for(int i = 0; i < brightTrajectoryCircles.size(); i++){
			brightTrajectoryCircles[i].update();
			if(brightTrajectoryCircles[i].getAlpha() > 0){
				tmpVector.push_back(brightTrajectoryCircles[i]);
			}
		}
		brightTrajectoryCircles = tmpVector;
	}else if(isGravityRect){
		for(int i = 0; i < GRABITY_RECTS_NUM; i++){
			gravityRects[i].update(mouseX, mouseY);
		}
	}else if(isGravityRect2){
		for(int i = 0; i < GRABITY_RECTS_NUM; i++){
			gravityRects2[i].update(mouseX, mouseY);
		}
	}else if(isBrightCircle){
		for(int i = 0; i < BRIGHT_CIRCLES_NUM; i++){
			brightCircles[i].update(ofGetWidth(), ofGetHeight());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	gui.draw();
	
	if(isGushingCircle){
		for(int i = 0; i < GUSHING_CIRCLES_NUM; i++){
			gushingCircles[i].draw();
		}
	}else if(isBrightTrajectoryCircle){
		for(int i = 0; i < brightTrajectoryCircles.size(); i++){
			brightTrajectoryCircles[i].draw();
		}
	}else if(isGravityRect){
		// Gravity Circle
		for(int i = 0; i < GRABITY_RECTS_NUM; i++){
			gravityRects[i].draw();
		}
	}else if(isGravityRect2){
		// Gravity Circle
		for(int i = 0; i < GRABITY_RECTS_NUM; i++){
			gravityRects2[i].draw(threshold);
		}
	}else if(isBrightCircle){
		for(int i = 0; i < BRIGHT_CIRCLES_NUM; i++){
			brightCircles[i].draw();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
	
	if(key == 'q' || key == 'w' || key == 'e' || key == 'r' || key == 't'){
		isGushingCircle = false;
		isBrightTrajectoryCircle = false;
		isGravityRect = false;
		isGravityRect2 = false;
		isBrightCircle = false;
		gui.clear();
	}
 
	switch (key) {
		case 49: //1のキーコード
			blendMode = OF_BLENDMODE_ALPHA; //混色をアルファに
//			sprintf(eventString, "Alpha");
			break;
		case 50: //2のキーコード
			blendMode = OF_BLENDMODE_ADD; //混色を加算に
//			sprintf(eventString, "Add");
			break;
		case 51: //3のキーコード
			blendMode = OF_BLENDMODE_MULTIPLY; //混色を乗算に
//			sprintf(eventString, "Multiply");
			break;
		case 52: //4のキーコード
			blendMode = OF_BLENDMODE_SUBTRACT; //混色を減算に
//			sprintf(eventString, "Subtract");
			break;
		case 53: //5のキーコード
			blendMode = OF_BLENDMODE_SCREEN; //混色をスクリーンに
//			sprintf(eventString, "Screen");
			break;
		case 'q':
			isGushingCircle = true;
			ofBackground(0);
			blendMode = OF_BLENDMODE_ADD;
			gui.add(radius.setup( "radius", 5, 1, 100 ));
			break;
		case 'w':
			isBrightTrajectoryCircle = true;
			ofBackground(0);
			blendMode = OF_BLENDMODE_ADD;
			break;
		case 'e':
			isGravityRect = true;
			ofBackground(0);
			blendMode = OF_BLENDMODE_ADD;
			break;
		case 'r':
			isGravityRect2 = true;
			ofBackground(0);
			blendMode = OF_BLENDMODE_ADD;
			gui.add(threshold.setup( "threshold", 5, 0, 20 ));
			break;
		case 't':
			isBrightCircle = true;
			ofBackground(0);
			blendMode = OF_BLENDMODE_ADD;
			break;
		default:
			break;
	}
	
	ofEnableBlendMode(blendMode);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
	mouseX = x;
	mouseY = y;
	
	if(isBrightTrajectoryCircle){
		int randomRange = 10;
		for(int i = 0; i < 4; i++){
			BrightTrajectoryCircle brightTrajectoryCircle;
			brightTrajectoryCircle.init(ofRandom(x - randomRange, x + randomRange), ofRandom(y - randomRange, y + randomRange), ofColor(ofRandom(255), ofRandom(255), ofRandom(255), ofRandom(255)));
			brightTrajectoryCircles.push_back(brightTrajectoryCircle);
		}
	}
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



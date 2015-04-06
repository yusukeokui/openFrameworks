#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "Brush.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
private:
	ofVideoGrabber cam;
	ofxCv::FlowFarneback flow;
	
	int regionSize;
	int xRegionsCnt, yRegionsCnt;
	vector<ofVec2f> flows;
	pair<int, int> posPair[9];
	
	bool showFlow = false;
	
	Brush brush;
	
	ofImage image;
	int imageCnt;
};

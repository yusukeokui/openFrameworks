#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxGui.h"

//#define _USE_LIVE_VIDEO

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
	void resetRange();
	
private:
	#ifdef _USE_LIVE_VIDEO
	const int capWidth = 320;
	const int capHeight = 240;
	ofVideoGrabber grabber;
	#else
	const int capWidth = 628;
	const int capHeight = 476;
	ofVideoPlayer player;
	#endif
	
	ofxCvColorImage colorImgRgb;
	ofxCvColorImage colorImgHsv;
	ofxCvColorImage colorImgRng;
	ofxCvGrayscaleImage grayImgCclNis;
	ofxCvContourFinder contourFinder;
	ofPoint point;
	vector<ofPoint> maxAreaPoints;
	
	ofxPanel panel;
	ofxIntSlider minHue;
	ofxIntSlider maxHue;
	ofxIntSlider minSaturation;
	ofxIntSlider maxSaturation;
	ofxIntSlider minValue;
	ofxIntSlider maxValue;
	ofxButton reset;
};

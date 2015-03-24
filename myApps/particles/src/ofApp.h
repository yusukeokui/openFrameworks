#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxGui.h"
#include "GushingCircle.h"
#include "BrightTrajectoryCircle.h"
#include "GravityRect.h"
#include "GravityRect2.h"
#include "BrightCircle.h"

#define GUSHING_CIRCLES_NUM 100
#define GRABITY 0.08
#define GRABITY_RECTS_NUM 3000
#define BRIGHT_CIRCLES_NUM 10

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
	int mouseX, mousuY;
	ofBlendMode blendMode;
	
	ofxPanel gui;
	ofxFloatSlider radius;
	ofxFloatSlider threshold;
	
	GushingCircle gushingCircles[GUSHING_CIRCLES_NUM];
	vector<BrightTrajectoryCircle> brightTrajectoryCircles;
	GravityRect gravityRects[GRABITY_RECTS_NUM];
	GravityRect2 gravityRects2[GRABITY_RECTS_NUM];
	BrightCircle brightCircles[BRIGHT_CIRCLES_NUM];
	
	bool isGushingCircle;
	bool isBrightTrajectoryCircle;
	bool isGravityRect;
	bool isGravityRect2;
	bool isBrightCircle;
};

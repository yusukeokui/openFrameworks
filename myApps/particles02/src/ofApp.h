#pragma once

#include "ofMain.h"
#include "MyParticle.h"
#include "DummyMouse.h"

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
	const int radius = 60;
	static const int PARTICLE_NUM = 40;
	MyParticle myParticles[PARTICLE_NUM];
	DummyMouse dummyMouse;
};

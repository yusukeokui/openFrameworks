//
//  MyParticle.h
//  test008
//
//  Created by yusuke okui on 2015/03/25.
//
//

#ifndef __test008__MyParticle__
#define __test008__MyParticle__

#include <stdio.h>
#include "ofMain.h"

class MyParticle {
	
public:
	void setup(ofVec2f position, float radius, bool isClock, ofColor color);
	void update(ofVec2f gravityPos, float gravityConst);
	void draw();
	
	ofVec2f position;
	
private:
	ofVec2f gravityPos;
	float radius;
	bool isClock;
	ofColor color;
	float alpha;
	float angle;
};

#endif /* defined(__test008__MyParticle__) */

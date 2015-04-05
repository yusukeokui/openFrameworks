//
//  Box.h
//  test011
//
//  Created by yusuke okui on 2015/04/05.
//
//

#ifndef __test011__Box__
#define __test011__Box__

#include <stdio.h>
#include "ofMain.h"

class Box {
	
public:
	void setup(int size, float frictionConst);
	void update();
	void draw(float x, float y, ofVec2f torque);
	
private:
	int size;
	float frictionConst;
	ofVec2f rot;
	ofVec2f vel;
};

#endif /* defined(__test011__Box__) */

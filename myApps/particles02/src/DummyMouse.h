//
//  DummyMouse.h
//  test005_combination
//
//  Created by yusuke okui on 2015/03/23.
//
//

#ifndef __test005_combination__DummyMouse__
#define __test005_combination__DummyMouse__

#include <stdio.h>
#include "ofMain.h"

class DummyMouse {
	
public:
	void setup(int initX, int initY);
	void update(int width, int height);
	float x, y;
	
private:
	float vx, vy;
	float dstX, dstY;
	float power;
	float powerUp = 0.1;
	const float RADIUS = 15.0f;
	const float _SPEED = 0.05f;
	const float MAX_POWER = 2.0f;
	const int RED = 255;
	const int GREEN = 255;
	const int BLUE = 223;
};

#endif /* defined(__test005_combination__DummyMouse__) */
//
//  BrightCircle.h
//  test005_combination
//
//  Created by yusuke okui on 2015/03/23.
//
//

#ifndef __test005_combination__BrightCircle__
#define __test005_combination__BrightCircle__

#include <stdio.h>
#include "ofMain.h"

class BrightCircle {
	
public:
	void setup(int initX, int initY);
	void update(int width, int height);
	void draw();
	
private:
	float x, y, vx, vy;
	float dstX, dstY;
	float power;
	float powerUp = 0.1;
	const float RADIUS = 15.0f;
	const float _SPEED = 0.1f;
	const float MAX_POWER = 2.0f;
	const int RED = 255;
	const int GREEN = 255;
	const int BLUE = 223;
};

#endif /* defined(__test005_combination__BrightCircle__) */

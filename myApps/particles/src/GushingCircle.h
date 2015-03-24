//
//  GushingCircle.h
//  test005_combination
//
//  Created by yusuke okui on 2015/03/04.
//
//

#ifndef __test005_combination__GushingCircle__
#define __test005_combination__GushingCircle__

#include <stdio.h>
#include "ofMain.h"

#define SPEED 1
#define RADIUS_UP 0.5

class GushingCircle {
	
public:
	void init(ofColor color);
	void initSpeed();
	void update(int x, int y, int width, int height, float radius, float gravity);
	void draw();
	
private:
	float _x, _y;
	float _radius;
	float _speedX;
	float _speedY;
	ofColor _color;
};

#endif /* defined(__test005_combination__GushingCircle__) */
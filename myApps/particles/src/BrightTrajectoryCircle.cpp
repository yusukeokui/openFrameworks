//
//  BrightCircle.cpp
//  test005_combination
//
//  Created by yusuke okui on 2015/03/05.
//
//

#include "BrightTrajectoryCircle.h"

void BrightTrajectoryCircle::init(int x, int y, ofColor color){

	_x = x;
	_y = y;
	_color = color;
	alpha = 255;
	radius = ofRandom(10, 20);
}

void BrightTrajectoryCircle::update(){
	
	alpha += ALPHA_STEP;
}

void BrightTrajectoryCircle::draw(){
	
	ofSetColor(_color, alpha);
	ofCircle(_x, _y, radius);
}

int BrightTrajectoryCircle::getAlpha(){
	
	return alpha;
}

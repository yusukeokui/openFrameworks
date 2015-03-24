//
//  GravityRect2.cpp
//  test005_combination
//
//  Created by yusuke okui on 2015/03/05.
//
//

#include "GravityRect2.h"

void GravityRect2::init(float x, float y){
	
	_x = x;
	_y = y;
}

void GravityRect2::update(int centX, int centY){
	
	float diffX = centX - _x;
	float diffY = centY - _y;
	float acc = 50 / (diffX * diffX + diffY * diffY);
	float accX = acc * diffX;
	float accY = acc * diffY;
	int maxWidth = ofGetWidth();
	int maxHeight = ofGetHeight();
	
	_vx += accX;
	_vy += accY;
	_x += _vx;
	_y += _vy;
	
	_vx *= 0.96;
	_vy *= 0.96;
	
	if (_x > maxWidth)
		_x = 0;
	else if (_x < 0)
		_x = maxWidth;
	if (_y > maxHeight)
		_y = 0;
	else if (_y < 0)
		_y = maxHeight;
}

void GravityRect2::draw(float threshold){
	
	ofSetColor(ofColor(200, 200, 255));
	
	float width, height;
	
	if(_vx >= 0){
		width = 10 / (_vx - threshold);
	}else{
		width = 10 / (_vx + threshold);
	}
	if(_vy >= 0){
		height = 10 / (_vy - threshold);
	}else{
		height = 10 / (_vy + threshold);
	}
	
	ofRect(_x, _y, width, height);
}

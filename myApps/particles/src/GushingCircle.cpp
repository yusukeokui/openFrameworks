//
//  GushingCircle.cpp
//  test005_combination
//
//  Created by yusuke okui on 2015/03/04.
//
//

#include "GushingCircle.h"

// ---------------------------------------
void GushingCircle::init(ofColor color){
	
	_x = ofGetWidth() / 2;
	_y = ofGetWidth() / 2;
	this->initSpeed();
	_color = color;
}

// ---------------------------------------
void GushingCircle::initSpeed(){
	
	ofVec2f vec(0, SPEED * 2.5f);
	
	if(ofRandom(10) < 5){
		_speedX = ofRandom(vec.x, vec.y);
	}else{
		_speedX = -ofRandom(vec.x, vec.y);
	}

	if(ofRandom(10) < 5){
		_speedY = (SPEED * 2.5f - abs(_speedX));
	}else{
		_speedY = -(SPEED * 2.5f - abs(_speedX));
	}
}

// ---------------------------------------
void GushingCircle::update(int x, int y, int width, int height, float radius, float gravity){
	
	if(_x + _radius < 0 || _x - _radius > width || _y + _radius < 0 || _y - _radius > height){
		_x = x;
		_y = y;
		_radius = radius;
		this->initSpeed();
	}
	_speedY += gravity;
	_x += _speedX;
	_y += _speedY;
	_radius += RADIUS_UP;
}

// ---------------------------------------
void GushingCircle::draw(){
	
	ofSetColor(_color);
	
	ofCircle(_x, _y, _radius);
}
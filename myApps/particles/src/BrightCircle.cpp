//
//  BrightCircle.cpp
//  test005_combination
//
//  Created by yusuke okui on 2015/03/23.
//
//

#include "BrightCircle.h"

void BrightCircle::setup(int width, int height){
	
	x = width / 2.0f;
	y = height / 2.0f;
	
	dstX = ofRandom(width);
	dstY = ofRandom(height);
	
	power = ofRandom(MAX_POWER);
}

void BrightCircle::update(int width, int height){
	
	float dx = dstX - x;
	float dy = dstY - y;
	float d = sqrt(dx * dx + dy * dy);
	if(d < 1.0f){
		d = 1.0f;
	}
	
	vx += _SPEED * dx / d;
	vy += _SPEED * dy / d;
	
	x += vx;
	y += vy;
	
	vx *= 0.99f;
	vy *= 0.99f;
	
	if(d < 50.0f){
		dstX = ofRandom(width * 1.0f / 5.0f, width * 4.0f / 5.0f);
		dstY = ofRandom(height * 1.0f / 5.0f, height * 4.0f / 5.0f);
	}
	
	power += powerUp;
	if(power > MAX_POWER){
		power = MAX_POWER;
		powerUp *= -1;
	}else if(power < 0){
		power = 0;
		powerUp *= -1;
	}
}

void BrightCircle::draw(){
	
	float _x = x;
	float _y = y;
	
	float num = RADIUS * 2;
	
	float colorPwr = power / num;
	ofSetColor(RED * colorPwr, GREEN * colorPwr, BLUE * colorPwr);
	
	for(int i = 0; i < num; i++){
		
		ofCircle(_x, _y, i + 1);
	}
}

//
//  MyParticle.cpp
//  test008
//
//  Created by yusuke okui on 2015/03/25.
//
//

#include "MyParticle.h"

void MyParticle::setup(ofVec2f position, float radius, bool isClock, ofColor color){
	
	// init position
	this->position.set(position);
	
	// init radius
	this->radius = radius;
	
	// init direction
	this->isClock = isClock;
	
	// init color
	this->color = color;
}

void MyParticle::update(ofVec2f gravityPos, float gravityConst){
	
	this->gravityPos.set(gravityPos);
	
	// calc gravity
	ofVec2f gravityVec = gravityPos - position;
	float distance = gravityVec.length();
	gravityVec.normalize();
	ofVec2f gravity = gravityVec * gravityConst / pow(distance, 2.0f);
	
	// calc velocity vector
	ofVec2f velocityUnitVec;
	float rotRad;
	if(isClock){
		rotRad = -TWO_PI / 4.0f;
	}else{
		rotRad = TWO_PI / 4.0f;
	}
	velocityUnitVec.x = gravityVec.x * cos(rotRad) - gravityVec.y * sin(rotRad);
	velocityUnitVec.y = gravityVec.x * sin(rotRad) + gravityVec.y * cos(rotRad);
	
	// calc velocity
	float velocity = sqrt(distance * gravity.length());
	float vx = velocity * velocityUnitVec.x;
	float vy = velocity * velocityUnitVec.y;
	
	// update position
	position.x += vx;
	position.y += vy;
	
	// update alpha
	alpha = pow(velocity, 3.0f) * 100;
	
	// update angle
	if(gravityVec.y >= 0.0f){
		angle = asin(gravityVec.x);
	}else{
		angle = -asin(gravityVec.x);
	}
	angle *= 360.0f / TWO_PI;
	
}

void MyParticle::draw(){
	
	if(alpha > 3){
	
		ofSetColor(color, alpha);
		//		ofSetColor(color);

		// circle
		//		ofCircle(position.x, position.y, radius);
	
		// rect
		//	ofPushMatrix();
		//	ofTranslate(position.x, position.y);
		//	ofRotateZ(-angle);
		//	ofRect(-radius / 2.0f, -radius / 2.0f, radius, radius);
		//	ofPopMatrix();
		
		// line
		ofSetLineWidth(2);
		ofLine(position.x, position.y, gravityPos.x, gravityPos.y);
	}
}

//
//  Box.cpp
//  test011
//
//  Created by yusuke okui on 2015/04/05.
//
//

#include "Box.h"

void Box::setup(int size, float frictionConst){

	this->size = size;
	this->frictionConst = frictionConst;
}

void Box::update(){
	
}

void Box::draw(float x, float y, ofVec2f torque){
	
	torque -= frictionConst * vel;
	vel += torque;
	rot += vel;
	
	ofBoxPrimitive box;
	box.setPosition(0, 0, 0);
	box.set(size);
	
	ofPushMatrix();
	ofTranslate(x, y, 100);
	ofRotateY(-rot.x);
	ofRotateX(-rot.y);
	box.draw();
	ofPopMatrix();
}

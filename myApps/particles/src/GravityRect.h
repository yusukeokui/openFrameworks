//
//  GravityRect.h
//  test005_combination
//
//  Created by yusuke okui on 2015/03/05.
//
//

#ifndef __test005_combination__GravityRect__
#define __test005_combination__GravityRect__

#include <stdio.h>
#include "ofMain.h"

class GravityRect {
	
public:
	void init(float x, float y);
	void update(int centX, int centY);
	void draw();
	
private:
	float _x, _y;
	float _vx, _vy;
};

#endif /* defined(__test005_combination__GravityRect__) */

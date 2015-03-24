//
//  BrightCircle.h
//  test005_combination
//
//  Created by yusuke okui on 2015/03/05.
//
//

#ifndef __test005_combination__BrightTrajectoryCircle__
#define __test005_combination__BrightTrajectoryCircle__

#include <stdio.h>
#include "ofMain.h"

# define ALPHA_STEP -5

class BrightTrajectoryCircle {
	
public:
	void init(int x, int y, ofColor color);
	void update();
	void draw();
	int getAlpha();
	
private:
	float _x, _y;
	ofColor _color;
	int alpha;
	float radius;
};

#endif /* defined(__test005_combination__BrightTrajectoryCircle__) */

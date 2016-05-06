//
//  explosionAnimation.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/12/16.
//
//

#ifndef __CLP_Knoxville_Wall__explosionAnimation__
#define __CLP_Knoxville_Wall__explosionAnimation__

#include <stdio.h>
#include "baseAnimation.h"
#include "ofxSimpleTimer.h"

class ExplosionAnimation : public BaseAnimation {
public:
    
    ExplosionAnimation(){}
    void setup();
    void update();
    void draw();
    
    void onTimerComplete(string &name);
    
    ParticleManager pm;
    ofParameter<float> frequency;
    
    ofxSimpleTimer *timer;
};

#endif /* defined(__CLP_Knoxville_Wall__explosionAnimation__) */

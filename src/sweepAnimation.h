//
//  sweepAnimation.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#ifndef __CLP_Knoxville_Wall__sweepAnimation__
#define __CLP_Knoxville_Wall__sweepAnimation__

#include <stdio.h>
#include "baseAnimation.h"
#include "ofxSimpleTimer.h"

class SweepAnimation : public BaseAnimation {
public:
    void setup();
    void update();
    void draw();
    
    void onTimerComplete(string &name);
    
    
    ofParameter<int> velocity;
    ofParameter<float> spawnProb;
    
    
    ParticleManager pm;
    
    ofxSimpleTimer *timer;
    
};

#endif /* defined(__CLP_Knoxville_Wall__sweepAnimation__) */

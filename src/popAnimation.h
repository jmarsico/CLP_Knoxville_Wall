//
//  popAnimation.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#ifndef __CLP_Knoxville_Wall__popAnimation__
#define __CLP_Knoxville_Wall__popAnimation__

#include <stdio.h>
#include "baseAnimation.h"
#include "ofxSimpleTimer.h"

class PopAnimation : public BaseAnimation {
public:
    void setup();
    void update();
    void draw();
    void pause();
    void start();
    
    void onTimerComplete(string &name);
    
    ofParameter<float> spawnProb;
    ofParameter<float> frequency;
    
    ParticleManager pm;
    ofxSimpleTimer *timer;
    
    
};

#endif /* defined(__CLP_Knoxville_Wall__popAnimation__) */

//
//  userPopAnimation.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 6/22/16.
//
//

#ifndef __CLP_Knoxville_Wall__userPopAnimation__
#define __CLP_Knoxville_Wall__userPopAnimation__

#include <stdio.h>
#include "baseAnimation.h"
#include "ofxSimpleTimer.h"

class UserPopAnimation  {
public:
    void setup();
    void update();
    void draw();
    void pause();
    void start();
    
    void userTimeAdded(int _duration);
    void userSetSize(int size);
    
    void onTimerComplete(string &name);
    
    ofParameter<float> spawnProb;
    ofParameter<float> frequency;
    
    ParticleManager pm;
    ofxSimpleTimer *timer;
    ofxSimpleTimer *userTimer;
    int size;
    
    
};



#endif /* defined(__CLP_Knoxville_Wall__userPopAnimation__) */

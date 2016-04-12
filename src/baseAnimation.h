//
//  baseAnimation.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#ifndef __CLP_Knoxville_Wall__baseAnimation__
#define __CLP_Knoxville_Wall__baseAnimation__

#include <stdio.h>
#include "ofMain.h"
#include "particleManager.h"

class BaseAnimation {
public:
    BaseAnimation();
    virtual void setup();
    virtual void update();
    virtual void draw();
    
    ofParameterGroup parameters;
    ofParameter<float> brightness;
    
};

#endif /* defined(__CLP_Knoxville_Wall__baseAnimation__) */

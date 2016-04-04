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

class BaseAnimation {
public:
    virtual void setup();
    virtual void update();
    virtual void draw();
    
    ofParameterGroup parameters;
    
};

#endif /* defined(__CLP_Knoxville_Wall__baseAnimation__) */

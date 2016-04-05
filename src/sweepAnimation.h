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

class SweepAnimation : public BaseAnimation {
public:
    void setup();
//    void update();
//    void draw();
    
    ofParameter<int> velocity;
    ofParameter<float> spawnProb;
    
    
    
};

#endif /* defined(__CLP_Knoxville_Wall__sweepAnimation__) */

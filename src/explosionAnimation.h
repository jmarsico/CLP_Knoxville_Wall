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

class ExplosionAnimation : public BaseAnimation {
public:
    
    ExplosionAnimation(){}
    void setup(ParticleManager* _pm);
    void update();
    void draw();
    
    
    ParticleManager* pm;
    ofParameter<float> frequency;
};

#endif /* defined(__CLP_Knoxville_Wall__explosionAnimation__) */

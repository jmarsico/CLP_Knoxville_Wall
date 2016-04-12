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

class PopAnimation : public BaseAnimation {
public:
    void setup(ParticleManager* _pm);
    void update();
    void draw();
    
    ofParameter<float> spawnProb;
    ofParameter<int> spawnSize;
    
    ParticleManager* pm;
    
    
};

#endif /* defined(__CLP_Knoxville_Wall__popAnimation__) */

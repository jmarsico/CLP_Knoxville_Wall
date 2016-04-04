//
//  sweepAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "sweepAnimation.h"

void SweepAnimation::setup(){
    parameters.setName("Sweep Anim");
    parameters.add(velocity.set("velocity", 0.0, 0.0, 1.0));
    parameters.add(spawnProb.set("spawn prob", 0.0, 0.0, 1.0));
}
//
//  popAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "popAnimation.h"

void PopAnination::setup(){
    parameters.setName("Pop Anim");
    parameters.add(velocity.set("velocity", 0.0, 0.0, 1.0));
}



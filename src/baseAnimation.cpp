//
//  baseAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "baseAnimation.h"

BaseAnimation::BaseAnimation(){
    parameters.add(brightness.set("brightness", 0.0, 0.0, 1.0));
}
void BaseAnimation::setup(){}
void BaseAnimation::update(){}
void BaseAnimation::draw(){}


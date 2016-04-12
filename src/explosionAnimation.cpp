//
//  explosionAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/12/16.
//
//

#include "explosionAnimation.h"

//-----------------------------------------------------
void ExplosionAnimation::setup(ParticleManager* _pm){
    pm = _pm;
    brightness = 1.f;
    parameters.setName("explode");
    parameters.add(frequency.set("frequency", 0.0, 0.0, 1.0));
}

//-----------------------------------------------------
void ExplosionAnimation::update(){
    
    if(ofGetFrameNum() % ((int)(1000 * (1.0 - frequency)) + 20) == 0){
        pm->explosion(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), 100);
    }
    pm->update(ofVec2f(0,0));
}

//-----------------------------------------------------
void ExplosionAnimation::draw(){
    
    pm->draw(brightness.get());
}
//
//  particle.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/1/16.
//
//

#include "particle.h"

void Particle::setup(ofVec2f _loc, ofVec2f _vel, float _ageSpeed){
    loc = _loc;
    vel = _vel;
    acc.set(0, 0);
    lifeSpan = 255.f;
    ageSpeed = _ageSpeed;
    bTimeToDie = false;
    
    
}

void Particle::update(ofVec2f _force){
    vel += acc;
    loc += vel;
    
    lifeSpan -= ageSpeed;
    if(lifeSpan <= 0){
        bTimeToDie = true;
    }
    
    if(loc.x > ofGetWidth() + 50
       || loc.x < 0 - 50
       || loc.y > ofGetHeight() + 50
       || loc.y < 0 - 50){
        bTimeToDie = true;
    }
}


void Particle::draw(){
    ofFill();
    ofSetColor(255, lifeSpan);
    ofDrawCircle(loc, 5);
}


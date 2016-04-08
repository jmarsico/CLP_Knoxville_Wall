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
    
    bNoise = false;
    
    counterInc = ofRandom(0.1);
    counterX = ofRandom(10);
    counterY = ofRandom(10);
}

void Particle::update(ofVec2f _force){
    
    if(bNoise){
        counterX += counterInc;
        counterY += counterInc;
        vel.x += 2*ofSignedNoise(counterX);
        vel.y += 2*ofSignedNoise(counterY);
    } else {
    
        vel += acc;
    }
    
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


void Particle::turnOnNoise(bool _noise){
    bNoise = _noise;
}


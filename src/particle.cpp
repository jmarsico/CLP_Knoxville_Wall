//
//  particle.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/1/16.
//
//

#include "particle.h"



void Particle::setup(ofVec2f _loc, ofVec2f _vel, float _ageSpeed, float _size){
    loc = _loc;
    vel = _vel;
    acc.set(0, 0);
    lifeSpan = 255.f;
    ageSpeed = _ageSpeed;
    bTimeToDie = false;
    
    bNoise = false;
    size = _size;
    
    counterInc = ofRandom(0.1);
    counterX = ofRandom(10);
    counterY = ofRandom(10);
    
    maxW = 1300;
    maxH = 1080;
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
    

    
    if(loc.x >= maxW
       || loc.x <= 0
       || loc.y >= maxH
       || loc.y <= 0){
        bTimeToDie = true;
    }
}


void Particle::draw(float _brightness){
    ofFill();
    ofSetColor(255, lifeSpan * _brightness);
    ofDrawCircle(loc, size);
}


void Particle::turnOnNoise(bool _noise){
    bNoise = _noise;
}


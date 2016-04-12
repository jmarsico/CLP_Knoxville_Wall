//
//  popAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "popAnimation.h"

void PopAnimation::setup(ParticleManager* _pm){
    
    pm = _pm;
    
    parameters.setName("Pop Anim");
    parameters.add(spawnProb.set("spawnProb", 0.0, 0.0, 1.0));
    parameters.add(spawnSize.set("spawn size", 5, 1, 100));
    
}


void PopAnimation::update(){
    
    int wait = 1 + (int)ofRandom((100.f * (1.1f -spawnProb)) + 5);
    ofLog() << wait;
    if(ofGetFrameNum() % wait  == 1){
        
        for(size_t i = 0; i < spawnSize; i++){
            pm->addParticle(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()/2 - 200, ofGetHeight()/2 + 200)));
        }
    }
    
    pm->update(ofVec2f(0,0));
    
}


void PopAnimation::draw(){
    pm->draw(brightness);
}

//
//  particleManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "particleManager.h"



ParticleManager::ParticleManager(){
    
}

void ParticleManager::setup(){
    
    parameters.add(drag.set("drag", 0.0, -1.0, 1.0));
    parameters.add(ageSpeed.set("ageSpeed", 0.0, 0.5, 1.0));
    
}

void ParticleManager::update(ofVec2f _acc){
    acc = _acc;
    for(size_t i = 0; i < particles.size(); i++){
        particles[i].update(acc);
    }
}


void ParticleManager::draw(){
    for(size_t i = 0; i < particles.size(); i++){
        particles[i].draw();
    }
}
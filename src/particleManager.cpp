//
//  particleManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "particleManager.h"


//----------------------------------------------------------
ParticleManager::ParticleManager(){
    
}

//----------------------------------------------------------
void ParticleManager::setup(){
    
    parameters.add(drag.set("drag", 0.0, -1.0, 1.0));
    parameters.add(ageSpeed.set("ageSpeed", 0.0, 0.5, 1.0));
    
}

//----------------------------------------------------------
void ParticleManager::update(){
    
    //update particles
    for(size_t i = 0; i < particles.size(); i++){
        particles[i].update(acc);
        if(particles[i].bTimeToDie) particles.erase(particles.begin() + i);
    }
    
    //update vehicles
    for(size_t i = 0; i < vehicles.size(); i++){
        vehicles[i].update();
        if(vehicles[i].bTimeToDie) vehicles.erase(vehicles.begin() + i);
    }
    
}

void ParticleManager::setForces(ofVec2f _acc){
    acc = _acc;
}

//----------------------------------------------------------
void ParticleManager::draw(float _brightness){
    for(size_t i = 0; i < particles.size(); i++){
        particles[i].draw(_brightness);
    }
}

//----------------------------------------------------------
void ParticleManager::explosion(ofVec2f _loc, int numParts){
    
    ofLogNotice("ParticleManager") << "explosion";
    for(size_t i = 0; i < numParts; i++){
        Particle p;
        ofVec2f vel(ofRandom(-2, 2), ofRandom(-2,2));
        p.setup(_loc, vel, 3);
        p.turnOnNoise(true);
        
        particles.push_back(p);
        
        
    }
    
}

//----------------------------------------------------------
void ParticleManager::addParticle(ofVec2f _loc){
    Particle p;
    p.setup(_loc, ofVec2f(0,0), 5);
    p.turnOnNoise(false);
    particles.push_back(p);
}

void ParticleManager::addVehicle(ofVec2f _loc, ofVec2f _dest){
    Vehicle v;
    v.setup(_loc, _dest, ofRandom(4, 10));
    
    vehicles.push_back(v);
}





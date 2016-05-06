//
//  vehicle.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 5/4/16.
//
//
//
// code based on Daniel Shiffman's Nature of Code
// http://natureofcode.com/book/chapter-6-autonomous-agents/

#include "vehicle.h"

//-------------------------------------------------------------
void Vehicle::setup(ofVec2f startLoc, ofVec2f _destination, float _size, float _speed){
    loc = startLoc;
    dest = _destination;
    size = ofMap(_size, 0, 100, 5, 40);
    
    acc.set(0, 0);
    vel.set(0,0);
    
    
    maxSpeed = ofMap(_speed, 0, 100, 30, 100);
    maxForce = 2.0;
    
    bTimeToDie = false;
    
}

//-------------------------------------------------------------
void Vehicle::update(){
   
    seek();
    vel += acc;
    vel.limit(maxSpeed);
    loc += vel;
    acc *= 0;
    
    if (loc.x > dest.x - 20 && loc.x < dest.x + 20){
        bTimeToDie = true;
    }
}

//-------------------------------------------------------------
void Vehicle::applyForce(ofVec2f force){
    acc += force;
}

//-------------------------------------------------------------
void Vehicle::seek(){
    ofVec2f desired = dest - loc;
    desired.normalize();
    desired *= maxForce;
    
    ofVec2f steer = desired - vel;
    steer.limit(maxForce);
    applyForce(steer);
    
}

//-------------------------------------------------------------
void Vehicle::changeDestination(ofVec2f _destination){
    dest = _destination;
}

//-------------------------------------------------------------
void Vehicle::draw(){
    ofSetColor(255);
    ofFill();
    
    float theta = vel.angle(ofVec2f(0,1));
    ofPushMatrix();
    ofTranslate(loc);
    ofRotate(theta);
    float r = size;
    ofDrawTriangle(0, -r*2, -r, r*2, r, r*2);
    ofPopMatrix();
}




//
//  sweepAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "sweepAnimation.h"

//-----------------------------------------------------
void SweepAnimation::setup(){
    
    pm.setup();
    
    timer = new ofxSimpleTimer();
    
    timer->setName("sweepAnimTimer");
    timer->setTime(1000, 2);
    timer->start();
    
    parameters.setName("Sweep Anim");
    parameters.add(velocity.set("velocity", 0.0, 0.0, 1.0));
    parameters.add(spawnProb.set("spawn prob", 0.0, 0.0, 1.0));
    
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &SweepAnimation::onTimerComplete);
    
}

//-----------------------------------------------------
void SweepAnimation::update(){
    pm.update();
    timer->update();
}

//-----------------------------------------------------
void SweepAnimation::pause(){
    timer->pause();
}

//-----------------------------------------------------
void SweepAnimation::start(){
    timer->start();
}

//-----------------------------------------------------
void SweepAnimation::onTimerComplete(string &name){
    if(name == "sweepAnimTimer"){
        
        timer->setTime(ofRandom(500, 5000), 2);
        timer->reset();
        timer->start();
        
        float prob = ofRandom(1.);
        float probThresh = 1.0 - spawnProb;
        
        if(prob > probThresh){
            ofVec2f start(ofRandom(100), ofRandom(100));
            ofVec2f end(ofRandom(100), ofRandom(100));
            pm.addVehicle(pm.deNormalize(start), pm.deNormalize(end), ofRandom(100), ofRandom(100));
        }
    }
}

//-----------------------------------------------------
void SweepAnimation::draw(){
    pm.draw(brightness);
}




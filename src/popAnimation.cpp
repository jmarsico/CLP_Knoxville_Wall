//
//  popAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "popAnimation.h"

void PopAnimation::setup(){
    
    pm.setup();
    
    parameters.setName("Pop Anim");
    parameters.add(spawnProb.set("spawnProb", 0.0, 0.0, 1.0));
    parameters.add(frequency.set("spawn size", 5, 1, 100));
    
    timer = new ofxSimpleTimer();
    timer->setName("popTimer");
    timer->setTime(1000, 2);
    timer->start();
    
}


void PopAnimation::update(){
    
    timer->update();
    
}


void PopAnimation::draw(){
    pm.draw(brightness);
}


void PopAnimation::onTimerComplete(string &name){
    if(name == "popTimer"){
        
        //reset timer based on frequency parameter
        int newTime = int((1.1f - frequency) * ofRandom(100, 1500));
        timer->setTime(newTime, 2);
        timer->reset();
        timer->start();
        
        float prob = ofRandom(1.);
        float probThresh = 1.0 - spawnProb;
        
        if(prob > probThresh){
            ofVec2f loc(ofRandom(100), ofRandom(100));
            pm.addParticle(pm.deNormalize(loc));
        }
    }
}
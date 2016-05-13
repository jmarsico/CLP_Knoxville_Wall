//
//  popAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "popAnimation.h"

//-----------------------------------------------------
void PopAnimation::setup(){
    pm.setup();
    
    parameters.setName("Pop Anim");
    parameters.add(spawnProb.set("spawnProb", 0.0, 0.0, 1.0));
    parameters.add(frequency.set("spawn size", 5, 1, 100));
    
    timer = new ofxSimpleTimer();
    timer->setName("popTimer");
    timer->setTime(1000, 2);
    timer->start();
    
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &PopAnimation::onTimerComplete);
}

//-----------------------------------------------------
void PopAnimation::update(){
    timer->update();
    pm.update();
}

//-----------------------------------------------------
void PopAnimation::draw(){
    pm.draw(brightness);
}

//-----------------------------------------------------
void PopAnimation::pause(){
    timer->pause();
}

//-----------------------------------------------------
void PopAnimation::start(){
    timer->start();
}

//-----------------------------------------------------
void PopAnimation::onTimerComplete(string &name){
    if(name == "popTimer"){
        
        //reset timer based on frequency parameter
        int newTime = int((1.1f - frequency) * ofRandom(10, 150));
        timer->setTime(newTime, 2);
        timer->reset();
        timer->start();
        
        float prob = ofRandom(1.);
        float probThresh = 1.0 - spawnProb;
        
        if(prob > probThresh){
            ofVec2f loc(ofRandom(1,99), ofRandom(1,99));
            bool noise;
            float num = ofRandom(1);
            num > 0.8 ? noise = true : noise = false;
            
            pm.addParticle(pm.deNormalize(loc), 10, noise);
        }
    }
}
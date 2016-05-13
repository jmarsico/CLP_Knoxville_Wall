//
//  explosionAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/12/16.
//
//

#include "explosionAnimation.h"

//-----------------------------------------------------
void ExplosionAnimation::setup(){
    pm.setup();
    brightness = 1.f;
    parameters.setName("explode");
    parameters.add(frequency.set("frequency", 0.0, 0.0, 1.0));
    
    timer = new ofxSimpleTimer();
    timer->setName("explodeAnimTimer");
    timer->setTime(1000, 2);
    timer->start();
    
    maxW = ofGetWidth();
    maxH = ofGetHeight();
    
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &ExplosionAnimation::onTimerComplete);
    
}

//-----------------------------------------------------
void ExplosionAnimation::update(){
    pm.update();
    timer->update();
}

//-----------------------------------------------------
void ExplosionAnimation::pause(){
    timer->pause();
}

//-----------------------------------------------------
void ExplosionAnimation::start(){
    timer->start();
}

//-----------------------------------------------------
void ExplosionAnimation::onTimerComplete(string &name){
    if(name == "explodeAnimTimer"){
        
        ofVec2f loc(ofRandom(100), ofRandom(100));
        pm.explosion(pm.deNormalize(loc), ofRandom(60,150), ofRandom(1.0));
        
        //reset timer based on frequency parameter
        int newTime = int((1.1f - frequency) * ofRandom(1000, 15000));
        timer->setTime(newTime, 2);
        timer->reset();
        timer->start();
    }
}

//-----------------------------------------------------
void ExplosionAnimation::draw(){
    pm.draw(brightness);
}


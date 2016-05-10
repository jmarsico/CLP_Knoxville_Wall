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
    
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &ExplosionAnimation::onTimerComplete);
    
}

//-----------------------------------------------------
void ExplosionAnimation::update(){
    
    pm.update();
    timer->update();
    
}


void ExplosionAnimation::onTimerComplete(string &name){
    if(name == "explodeAnimTimer"){
        pm.explosion(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), 100, ofRandom(1.0));
        
        
    
        //reset timer based on frequency parameter
        int newTime = int((1.1f - frequency) * ofRandom(1000, 15000));
        timer->setTime(newTime, 2);
        timer->reset();
        timer->start();
    }
}


void ExplosionAnimation::draw(){
    pm.draw(brightness);
}


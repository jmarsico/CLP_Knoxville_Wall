//
//  userPopAnimation.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 6/22/16.
//
//

#include "userPopAnimation.h"

//-----------------------------------------------------
void UserPopAnimation::setup(){
    pm.setup();
    
    spawnProb = 1.0;
    frequency = 100;
    
    timer = new ofxSimpleTimer();
    timer->setName("userPopTimer");
    timer->setTime(10, 2);
    
    
    userTimer = new ofxSimpleTimer();
    userTimer->setName("userDurationTimer");
    
    size = 10;
    
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &UserPopAnimation::onTimerComplete);
}

//-----------------------------------------------------
void UserPopAnimation::update(){
    timer->update();
    userTimer->update();
    pm.update();
}

//-----------------------------------------------------
void UserPopAnimation::draw(){
    pm.draw(255);
        
    
}

//-----------------------------------------------------
void UserPopAnimation::pause(){
    timer->pause();
    
}

//-----------------------------------------------------
void UserPopAnimation::start(){
    timer->start();
}

void UserPopAnimation::userTimeAdded(int _duration){
    userTimer->setTime(_duration, 1);
    userTimer->reset();
    userTimer->start();
    start();
    ofLog() << "user time added" << _duration;
}

void UserPopAnimation::userSetSize(int _size){
    size = _size;
}

//-----------------------------------------------------
void UserPopAnimation::onTimerComplete(string &name){
    if(name == "userPopTimer"){
        
          //reset timer based on frequency parameter
        int newTime = ofRandom(10);
        timer->setTime(newTime, 2);
        timer->reset();
        timer->start();
        
        for(size_t i = 0; i < 10; i++){
            ofVec2f loc(ofRandom(1,100), ofRandom(1,100));
    //        bool noise;
    //        float num = ofRandom(1);
    //        num > 0.6 ? noise = true : noise = false;
            
            pm.addParticle(pm.deNormalize(loc), size, false);
        }

    }
    
    if(name == "userDurationTimer"){
        ofLog() << "user pop timer over";
        pause();
    }
}
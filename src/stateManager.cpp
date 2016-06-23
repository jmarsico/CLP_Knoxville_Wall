//
//  stateManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "stateManager.h"

ofEvent<bool> StateManager::userControl = ofEvent<bool>();
ofEvent<void> StateManager::sceneChange = ofEvent<void>();
ofEvent<bool> StateManager::turnOnOff = ofEvent<bool>();


//------------------------------------------------------------
StateManager::StateManager(){
    
    bUserInControl = false;
    currentScene = (int)ofRandom(5);
    
    //set up timers
    userControlTimer = new ofxSimpleTimer();
    userControlTimer->setTime(20000, 1);
    userControlTimer->setName("userControlTimer");
//    userControlTimer->debugStart();
    
    sceneTimer = new ofxSimpleTimer();
    sceneTimer->setTime(10000,1);
    sceneTimer->setName("sceneTimer");
    sceneTimer->start();
    
    //set up event listeners
    //timer listener
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &StateManager::onTimerComplete);
    ofAddListener(OscManager::userCommand, this, &StateManager::onUserInControl);
    
    
    currentTime = (ofGetHours() * 60) + ofGetMinutes();
    lastTime = currentTime;
    
}


//------------------------------------------------------------
void StateManager::update(){
    
    if(getIsUserInControl() == false) sceneTimer->update();
    userControlTimer->update();
    checkTime();
}


//------------------------------------------------------------
void StateManager::onUserInControl(int &seconds){
    
    //turn on the user timer (or reset it)
    userControlTimer->setTime(seconds * 1000, 1);
    userControlTimer->reset();
    userControlTimer->start();
    
    //set the user in control flag to rue;
    bUserInControl = true;
    bool uc = true;
    ofNotifyEvent(userControl, uc);
    
    //pause the scene timer
    sceneTimer->pause();
    
    //log it
    ofLogVerbose("StateManager") << "user in control event";
}

//------------------------------------------------------------
void StateManager::onTimerComplete(string &name){
    
    //user timer
    if(name == "userControlTimer"){
        //send out event notifying end of user control
        bool uc = false;
        
        //set user control flag to fals
        bUserInControl = false;
        ofNotifyEvent(userControl, uc);
        
        //restart the scene timer
        sceneTimer->start();
        userControlTimer->pause();
        
        //log it
        ofLogVerbose("StateManager") << "user control timer complete";
    }
    
    //scene timer
    else if(name == "sceneTimer"){
        
        //send out event to change scene
        bool sc = true;
        ofNotifyEvent(sceneChange);
        
        //get a new random time for next scene change
        int newTimerLength = (int)ofRandom(60 * 1000,  120 * 1000);
        
        //set up the new timer and start it
        sceneTimer->setTime(newTimerLength, 1);
        sceneTimer->start();
        
        //log it
        ofLogVerbose("StateManager") << "scenetimer complete;  new time until scene change: " << newTimerLength;
    }
}

//------------------------------------------------------------
void StateManager::setTurnOnTime(string _timeStamp){
    vector<string> timeParts = ofSplitString(_timeStamp, ":");
    ofLogNotice("StateManager") << "Turn on time: " << _timeStamp;
    
    turnOnTime = (ofToInt(timeParts[0]) * 60) + ofToInt(timeParts[1]);

}


//------------------------------------------------------------
void StateManager::setTurnOffTime(string _timeStamp){
    vector<string> timeParts = ofSplitString(_timeStamp, ":");
    ofLogNotice("StateManager") << "Turn on time: " << _timeStamp;
    
    turnOffTime = (ofToInt(timeParts[0]) * 60) + ofToInt(timeParts[1]);
    
}


//------------------------------------------------------------
void StateManager::checkTime(){
    currentTime = (ofGetHours() * 60) + ofGetMinutes();
    
    if(lastTime < turnOnTime && currentTime >= turnOnTime){
        bool trueBool = true;
        ofNotifyEvent(turnOnOff, trueBool);
        ofLogNotice("statemanager") << "TURN ON";
    }
    
    if(lastTime < turnOffTime && currentTime >= turnOffTime){
        bool falseBool = false;
        ofNotifyEvent(turnOnOff, falseBool);
        ofLogNotice("statemanager") << "TURN OFF";
    }
    
    lastTime = currentTime;
    
    
    
    
}




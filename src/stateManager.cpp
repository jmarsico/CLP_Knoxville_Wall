//
//  stateManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "stateManager.h"

ofEvent<void> StateManager::endUserControl = ofEvent<void>();
ofEvent<void> StateManager::sceneChange = ofEvent<void>();


//------------------------------------------------------------
StateManager::StateManager(){
    
    bUserInControl = false;
    currentScene = (int)ofRandom(5);
    
    //set up timers
    userControlTimer = new ofxSimpleTimer();
    userControlTimer->setTime(1000, 1);
    userControlTimer->setName("inUseTimer");
    userControlTimer->start();
    
    sceneTimer = new ofxSimpleTimer();
    sceneTimer->setTime(10000,1);
    sceneTimer->setName("sceneTimer");
    sceneTimer->start();
    
    //set up event listeners
    //timer listener
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &StateManager::onTimerComplete);
    ofAddListener(OscManager::userCommand, this, &StateManager::onUserInControl);
    
}


//------------------------------------------------------------
void StateManager::update(){
    sceneTimer->update();
    userControlTimer->update();
}


//------------------------------------------------------------
void StateManager::onUserInControl(bool &t){
    
    //turn on the user timer (or reset it)
    userControlTimer->reset();
    userControlTimer->start();
    
    //set the user in control flag to rue;
    bUserInControl = true;
    
    //pause the scene timer
    sceneTimer->pause();
    
    //log it
    ofLogVerbose("StateManager") << "user in control event";
}

//------------------------------------------------------------
void StateManager::onTimerComplete(string &name){
    
    //user timer
    if(name == "inUseTimer"){
        //send out event notifying end of user control
        bool uc = true;
        ofNotifyEvent(endUserControl);
        
        //set user control flag to fals
        bUserInControl = false;
        
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
        int newTimerLength = (int)ofRandom(1000, 6000);
        
        //set up the new timer and start it
        sceneTimer->setTime(newTimerLength, 1);
        sceneTimer->start();
        
        //log it
        ofLogVerbose("StateManager") << "scenetimer complete;  new time until scene change: " << newTimerLength;
    }
}
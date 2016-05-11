//
//  oscManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/20/16.
//
//

#include "oscManager.h"


ofEvent<int> OscManager::userCommand = ofEvent<int>();
ofEvent<ExplosionMsg> OscManager::explosion = ofEvent<ExplosionMsg>();
ofEvent<SweepMsg> OscManager::sweep = ofEvent<SweepMsg>();


void OscManager::setup(){
    receiver.setup(12345);
    sender.setup("192.168.1.200", 23456);
    
    heartBeat = new ofxSimpleTimer();
    heartBeat->setTime(1000, 10);
    heartBeat->setName("heartbeat");
    heartBeat->start();
    
    defaultWaitTime = 20;
    
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &OscManager::timerComplete);
    
}

void OscManager::update(){
    heartBeat->update();
    
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
//        ofLog() << "got a message" << m.getAddress();
        
        if(m.getAddress() == "/explode"){
            
            float x = m.getArgAsFloat(0);
            float y = m.getArgAsFloat(1);
            float size = m.getArgAsFloat(2);
            
            
            ofNotifyEvent(userCommand, defaultWaitTime);
            
            //send an explosion event
            ExplosionMsg em(ofVec2f(x,y), size);
            ofNotifyEvent(explosion, em);
            
            ofLogNotice("OscManager") << "received explode message";
            
        }
        else if(m.getAddress() == "/sweep"){
            float startX = m.getArgAsFloat(0);
            float startY = m.getArgAsFloat(1);
            float endX = m.getArgAsFloat(2);
            float endY = m.getArgAsFloat(3);
            
            ofNotifyEvent(userCommand, defaultWaitTime);
            
            SweepMsg sm(ofVec2f(startX, startY), ofVec2f(endX, endY));
            ofNotifyEvent(sweep, sm);
            
            ofLogNotice("OscManager") << "received sweep message";
            
        }
        else if(m.getAddress() == "/dots"){
            ofNotifyEvent(userCommand, defaultWaitTime);
        }
        else if(m.getAddress() == "/pause"){
            int pauseLength = m.getArgAsInt(0);
            ofNotifyEvent(userCommand, pauseLength);
        }
        
        
    }

    
}


void OscManager::timerComplete(string &name){
    if(name == "heartbeat"){
        heartBeat->reset();
        heartBeat->start();
    }
    
    //send heartbeat
    ofxOscMessage m;
    m.setAddress("/heartbeat");
    m.addIntArg(1);
    sender.sendMessage(m, false);

    
}


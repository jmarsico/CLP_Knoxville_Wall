//
//  oscManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/20/16.
//
//

#include "oscManager.h"


//ofEvent<string> OscManager::command = ofEvent<string>();


void OscManager::setup(){
    receiver.setup(12345);
    sender.setup("127.0.0.1", 23456);
    
    heartBeat = new ofxSimpleTimer();
    heartBeat->setTime(1000, 10);
    heartBeat->setName("heartbeat");
    heartBeat->start();
    
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &OscManager::timerComplete);
    
}

void OscManager::update(){
    heartBeat->update();
    
    
    // check for waiting messages
    while(receiver.hasWaitingMessages()){
        // get the next message
        ofxOscMessage m;
        receiver.getNextMessage(m);
        
//        if(m.getAddress() == "/explode"){
//            ofNotifyEvent(command, "explode");
//            
//        }
//        else if(m.getAddress() == "/sweep"){
//            ofNotifyEvent(command, "sweep");
//        }
         if(m.getAddress() == "/dots"){
            string t = "dots";
            ofNotifyEvent(command, t);
        }
        
        
    }

    
}


void OscManager::timerComplete(string &name){
    if(name == "heartbeat"){
        ofLog() << "heartbeat";
        heartBeat->reset();
        heartBeat->start();
    }
    
    //send heartbeat
    ofxOscMessage m;
    m.setAddress("/heartbeat");
    m.addIntArg(1);
    sender.sendMessage(m, false);

    
}


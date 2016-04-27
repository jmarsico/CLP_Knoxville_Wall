//
//  oscManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/20/16.
//
//

#include "oscManager.h"


ofEvent<UserCommand> OscManager::userCommand = ofEvent<UserCommand>();


void OscManager::setup(StateManager* _state){
    state = _state;
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
        string s = "";
        
        if(m.getAddress() == "/explode"){
            
            float x = m.getArgAsFloat(0);
            float y = m.getArgAsFloat(1);
            float size = m.getArgAsFloat(2);
            
            uc.command = UserCommand::EXPLOSION;
            uc.loc.x = m.getArgAsFloat(0);
            uc.loc.y = m.getArgAsFloat(1);
            uc.size = m.getArgAsFloat(2);
            
            ofNotifyEvent(userCommand, uc);
            
            
            
            
            
//            x = ofMap(x, 0.0, 1.0, scene->getTopLeft().x, scene->getBottomRight().x);
            
            
            //mutex here!
//            std::unique_lock<std::mutex> lock(mutex);
//            scene->getParticles().explosion(ofVec2f(x,y), size);
            
        }
        else if(m.getAddress() == "/sweep"){
            s = "sweep";
            ofNotifyEvent(userCommand, s);
        }
         if(m.getAddress() == "/dots"){
             s = "dots";
            ofNotifyEvent(userCommand, s);
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


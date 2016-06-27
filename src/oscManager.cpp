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
ofEvent<DotsMsg> OscManager::dots = ofEvent<DotsMsg>();
ofEvent<bool> OscManager::turnOnOff = ofEvent<bool>();


void OscManager::setup(){
    receiver.setup(12345);
    sender.setup("127.0.0.1", 23456);

    heartBeat = new ofxSimpleTimer();
    heartBeat->setTime(10000, 1);
    heartBeat->setName("heartbeat");
    heartBeat->start();

    defaultWaitTime = 20;

    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &OscManager::timerComplete);

    pauseTimeRemaining = 0;

}

void OscManager::setPauseTimeRemaining(float _time){
    pauseTimeRemaining = (int)_time;
}

void OscManager::update(bool _bSendingToLights){
    heartBeat->update();
    bSendingToLights = _bSendingToLights;

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
            float speed = m.getArgAsInt(4);

            ofNotifyEvent(userCommand, defaultWaitTime);

            SweepMsg sm(ofVec2f(startX, startY), ofVec2f(endX, endY), speed);
            ofNotifyEvent(sweep, sm);

            ofLogNotice("OscManager") << "received sweep message";

        }
        else if(m.getAddress() == "/dots"){
            int size = m.getArgAsInt(0);
            int duration = m.getArgAsInt(1);

            ofNotifyEvent(userCommand, defaultWaitTime);

            DotsMsg dm(size, duration);
            ofNotifyEvent(dots, dm);
        }
        else if(m.getAddress() == "/pause"){
            int pauseLength = m.getArgAsInt(0);
            ofNotifyEvent(userCommand, pauseLength);
            ofLogNotice("OscManager") << "Turn ON OSC command received. Pause length: " << pauseLength;
        }
        else if(m.getAddress() == "/turnOnOff"){
            bool trueBool = m.getArgAsBool(0);
            ofNotifyEvent(turnOnOff, trueBool);
            if(trueBool) {
              ofLogNotice("OscManager") << "Turn ON OSC command received";
            } else {
              ofLogNotice("OscManager") << "Turn OFF OSC command received";
            }

        }
        else if(m.getAddress() == "/turnOff"){
            bool falseBool = false;
            ofNotifyEvent(turnOnOff, falseBool);
            ofLogNotice("OscManager") << "Turn OFF OSC command received";
        }
    }
}


void OscManager::timerComplete(string &name){
    if(name == "heartbeat"){
        heartBeat->setTime(10000, 2);
        heartBeat->reset();
        heartBeat->start();
        //send heartbeat
        ofxOscMessage m;
        m.setAddress("/heartbeat");
        m.addIntArg(ofGetFrameRate());
        m.addBoolArg(bSendingToLights);
        m.addFloatArg(pauseTimeRemaining);
        sender.sendMessage(m, false);
    }




}

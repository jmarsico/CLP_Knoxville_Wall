//
//  logger.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 5/4/16.
//
//

#include "logger.h"


void Logger::setup(string filePath){
    loggingPath = filePath;
    
    ofLog() << "logging path: " << loggingPath;
    logTimer = new ofxSimpleTimer();
    logTimer->setTime(10000, 10);
    logTimer->setName("logTimer");
    logTimer->start();
    
    ofAddListener(ofxSimpleTimer::TIMER_COMPLETE, this, &Logger::onTimerComplete);
}


void Logger::update(){
    logTimer->update();
}

void Logger::logToFile(string message){
    ofLogToFile(loggingPath.c_str(), true);
    ofLog() <<  message;
    ofLogToConsole();
}


void Logger::onTimerComplete(string &name){
    if(name == "logTimer"){
        stringstream msg;
        msg << "Framerate: " << ofToString((int)ofGetFrameRate());
        logToFile(msg.str());
        logTimer->reset();
        logTimer->start();
    }
    
    

}


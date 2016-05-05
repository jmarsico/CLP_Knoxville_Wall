//
//  logger.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 5/4/16.
//
//

#ifndef __CLP_Knoxville_Wall__logger__
#define __CLP_Knoxville_Wall__logger__

#include <stdio.h>
#include "ofMain.h"
#include "ofxSimpleTimer.h"
#include "oscManager.h"

class Logger{
public:
    Logger(){};
    void setup(string filePath);
    void update();
    void logToFile(string message);
    void onTimerComplete(string &name);
    
    
    
    string loggingPath;
    ofxSimpleTimer* logTimer;
    
    
};

#endif /* defined(__CLP_Knoxville_Wall__logger__) */

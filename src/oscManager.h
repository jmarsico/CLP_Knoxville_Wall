//
//  oscManager.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/20/16.
//
//

#ifndef __CLP_Knoxville_Wall__oscManager__
#define __CLP_Knoxville_Wall__oscManager__

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxSimpleTimer.h"
#include "msgTypes.h"

class OscManager{
    
public:
    OscManager(){}
    
    void setup();
    void update();
    void timerComplete(string & name);
    
    ofxOscReceiver receiver;
    ofxOscSender   sender;
    
    ofxSimpleTimer *heartBeat;
    
    static ofEvent<void> userCommand;
    static ofEvent<ExplosionMsg> explosion;
    static ofEvent<SweepMsg> sweep;
    
    mutable std::mutex mutex;
    

};

#endif /* defined(__CLP_Knoxville_Wall__oscManager__) */

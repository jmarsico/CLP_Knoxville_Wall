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
    
    static ofEvent<int> userCommand;
    static ofEvent<ExplosionMsg> explosion;
    static ofEvent<SweepMsg> sweep;
    static ofEvent<DotsMsg> dots;
    static ofEvent<bool> turnOnOff;
    
    mutable std::mutex mutex;
    
    int defaultWaitTime;
    

};

#endif /* defined(__CLP_Knoxville_Wall__oscManager__) */

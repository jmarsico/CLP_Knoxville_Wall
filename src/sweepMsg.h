//
//  sweep.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 5/4/16.
//
//

#ifndef CLP_Knoxville_Wall_sweep_h
#define CLP_Knoxville_Wall_sweep_h

#include "ofMain.h"

class SweepMsg {
public:
    SweepMsg(ofVec2f _loc, ofVec2f _dest, int _speed){
        loc = _loc;
        dest = _dest;
        speed = _speed;
    }
    
    ofVec2f loc;
    ofVec2f dest;
    int speed;
};

#endif

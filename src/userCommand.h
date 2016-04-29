//
//  userCommand.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/27/16.
//
//

#ifndef __CLP_Knoxville_Wall__userCommand__
#define __CLP_Knoxville_Wall__userCommand__

#include <stdio.h>
#include "ofMain.h"

class UserCommand{
public:
    
    UserCommand();
    
    ofVec2f loc;
    ofVec2f force;
    int freq;
    int size;
    
    int command;
    
    enum commandType {
        EXPLOSION,
        SWEEP,
        DOTS
    };
    
};

#endif /* defined(__CLP_Knoxville_Wall__userCommand__) */
//
//  dotsMsg.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 6/20/16.
//
//

#ifndef CLP_Knoxville_Wall_dotsMsg_h
#define CLP_Knoxville_Wall_dotsMsg_h

#include <stdio.h>
#include "ofMain.h"

class DotsMsg {
public:
    DotsMsg(int _size, int _duration){
        size = _size;
        duration = _duration;
    }
    
    int size;
    int duration;
};

#endif

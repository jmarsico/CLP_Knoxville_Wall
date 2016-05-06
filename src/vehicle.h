//
//  vehicle.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 5/4/16.
//
//

#ifndef __CLP_Knoxville_Wall__vehicle__
#define __CLP_Knoxville_Wall__vehicle__

#include <stdio.h>
#include "ofMain.h"


class Vehicle{
public:
    Vehicle(){};
    void setup(ofVec2f _startLoc, ofVec2f _destination, float _size, float _speed);
    void update();
    void seek();
    void applyForce(ofVec2f force);
    void draw();
    
    void changeDestination(ofVec2f _destination);
    
    ofVec2f loc;
    ofVec2f vel;
    ofVec2f acc;
    ofVec2f dest;
    
    float maxSpeed;
    float maxForce;
    float size;
    
    bool bTimeToDie;
    
};

#endif /* defined(__CLP_Knoxville_Wall__vehicle__) */

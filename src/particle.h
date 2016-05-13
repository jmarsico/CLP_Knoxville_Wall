//
//  particle.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/1/16.
//
//

#ifndef __CLP_Knoxville_Wall__particle__
#define __CLP_Knoxville_Wall__particle__

#include <stdio.h>
#include "ofMain.h"

class Particle {
public:
    Particle(){};
    
    void setup(ofVec2f _loc, ofVec2f _vel, float _ageSpeed, float _size);
    void update(ofVec2f _force);
    void draw(float _brightness);
    
    void turnOnNoise(bool _noise);
    
    
    ofVec2f loc;
    ofVec2f vel;
    ofVec2f acc;
    float lifeSpan;
    float ageSpeed;
    bool bTimeToDie;
    ofPolyline shape;
    
    float counterInc;
    float counterX;
    float counterY;
    
    float size;
    int maxW, maxH;
    
    bool bNoise;
    
};

#endif /* defined(__CLP_Knoxville_Wall__particle__) */

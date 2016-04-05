//
//  particleManager.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#ifndef __CLP_Knoxville_Wall__particleManager__
#define __CLP_Knoxville_Wall__particleManager__

#include <stdio.h>
#include "ofMain.h"
#include "particle.h"

class ParticleManager {
public:
    ParticleManager();
    
    //pointer to the statemanager
    void setup();
    
    
    void update(ofVec2f _acc);
    
    void explosion(ofVec2f _loc);
    
    
    void draw();
    
    
    ofParameterGroup parameters;
    ofParameter<float> drag;
    ofParameter<int> ageSpeed;
    ofVec2f acc;
    
    
private:
    
    vector<Particle> particles;

};

#endif /* defined(__CLP_Knoxville_Wall__particleManager__) */
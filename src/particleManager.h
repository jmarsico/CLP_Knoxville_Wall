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
#include "vehicle.h"

class ParticleManager {
public:
    ParticleManager();
    
    //pointer to the statemanager
    void setup();
    
    void addParticle(ofVec2f _loc);
    void addVehicle(ofVec2f _loc, ofVec2f _dest);
    void update();
    void setForces(ofVec2f);
    
    void explosion(ofVec2f _loc, int numParts);
    
    
    void draw(float _brightness);
    
    
    ofParameterGroup parameters;
    ofParameter<float> drag;
    ofParameter<int> ageSpeed;
    ofVec2f acc;
    
    
private:
    
    vector<Particle> particles;
    vector<Vehicle> vehicles;

};

#endif /* defined(__CLP_Knoxville_Wall__particleManager__) */

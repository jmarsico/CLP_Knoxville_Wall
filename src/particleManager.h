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
    
    void addParticle(ofVec2f _loc, float _size = 5);
    void addVehicle(ofVec2f _loc, ofVec2f _dest, float size, float speed);
    void update();
    void setForces(ofVec2f);
    void explosion(ofVec2f _loc, int numParts, float startingVel);
    void draw(float _brightness);
    
    ofVec2f deNormalize(ofVec2f &inputVec);
    
    
    ofParameterGroup parameters;
    ofParameter<float> drag;
    ofParameter<int> ageSpeed;
    ofVec2f acc;
    
    
private:
    
    vector<Particle> particles;
    vector<Vehicle> vehicles;
    
    ofVec2f topLeft, bottomRight;

};

#endif /* defined(__CLP_Knoxville_Wall__particleManager__) */

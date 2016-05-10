//
//  settingsGenerator.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 5/9/16.
//
//

#ifndef __CLP_Knoxville_Wall__settingsGenerator__
#define __CLP_Knoxville_Wall__settingsGenerator__

#include <stdio.h>
#include "ofMain.h"
#include "ofxEasing.h"

class SettingsGenerator {
public:
    SettingsGenerator();
    void generateNewTargets();
    void update(float time);
    
    
    //fluid params to be changed generatively
    float fDissipation;
    float fVorticity;
    float fViscosity;
    float fSpeed;
    float fCellSize;
    
    //animation params to be changed generatively
    float exlBright;
    float popBright;
    float sweepBright;

    float initTime;
    float endTime;
    
    
};

#endif /* defined(__CLP_Knoxville_Wall__settingsGenerator__) */

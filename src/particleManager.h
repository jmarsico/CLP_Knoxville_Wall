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
#include "guiElement.h"

class ParticleManager : public GuiElement {
public:
    ParticleManager();
    
    //pointer to the statemanager
    void setup();
    
    
    void update();
    
    
    void draw();
    
    
private:
    vector<Particle> particles;
    
};

#endif /* defined(__CLP_Knoxville_Wall__particleManager__) */

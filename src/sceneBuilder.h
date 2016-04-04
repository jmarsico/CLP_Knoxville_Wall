//
//  sceneBuilder.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#ifndef __CLP_Knoxville_Wall__sceneBuilder__
#define __CLP_Knoxville_Wall__sceneBuilder__

#include <stdio.h>
#include "ofMain.h"
#include "stateManager.h"
#include "sweepAnimation.h"
#include "popAnimation.h"
#include "particleManager.h"
#include "guiElement.h"
#include "fluidManager.h"


extern ofEvent<int> onSceneChange;


class SceneBuilder : GuiElement{
public:
    SceneBuilder();
    void setup(StateManager *_state);
    
    void drawAnimation();
    
    void generateScene();
    
    void update();
    
    
private:
    StateManager *state;
    ParticleManager particles;
    SweepAnimation sweep;
    PopAnimation pop;
    
    FluidManager fluid;
    
    int drawWidth, drawHeight;
    
    ofFbo animationFbo;
    
};

#endif /* defined(__CLP_Knoxville_Wall__sceneBuilder__) */

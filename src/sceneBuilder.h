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
#include "ofxFastFboReader.h"


//extern ofEvent<int> onSceneChange;
//extern ofEvent<bool> onUserInControl;
//extern ofEvent<bool> onFullUserControl;


class SceneBuilder {
public:
    SceneBuilder();
    ~SceneBuilder();
    void setup(StateManager *_state);
    void updateAnimation();
    void drawAnimation();
    void generateSceneSettings(int &newScene);
    void update();
    void drawModeSetName(int &_value);
    ofPixels generateFinalComposite();
    void draw();
    
    ofParameterGroup parameters;
    ofParameter<int>drawMode;
    ofParameter<string>drawName;
    
    ofParameterGroup fluidParams;
    
protected:
    

    
    StateManager *state;
    ParticleManager particles;
    SweepAnimation sweep;
    PopAnimation pop;

    FluidManager fluid;
    
    int drawWidth, drawHeight;
    
    ofFbo animationFbo;
    ofFbo compositeFbo;
    
    ofPixels compositePix;
    ofxFastFboReader reader;
    
};

#endif /* defined(__CLP_Knoxville_Wall__sceneBuilder__) */
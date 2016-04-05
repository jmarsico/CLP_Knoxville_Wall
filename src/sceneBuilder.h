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
#include "ofxGui.h"


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
    void drawModeSetName(const int &_value);
    void generateFinalComposite();
    ofPixels getPixels();
    void draw();
    
    ofParameterGroup getFluidParams();
    ofParameterGroup getAnimationParams();
    
    

    
    ofFbo animationFbo;
    ofFbo compositeFbo;
    
    FluidManager fluid;
    
protected:
    
    ofParameterGroup animParams;
    ofParameter<int>drawMode;
    ofParameter<string>drawName;
    
    ofParameterGroup fluidParams;
    
    StateManager *state;
    ParticleManager particles;
    SweepAnimation sweep;
    PopAnimation pop;


    
    int drawWidth, drawHeight;
    

    
    ofPixels compositePix;
    ofxFastFboReader reader;
    
};

#endif /* defined(__CLP_Knoxville_Wall__sceneBuilder__) */

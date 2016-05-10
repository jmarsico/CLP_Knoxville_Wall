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
#include "ofxEasing.h"
#include "stateManager.h"
#include "sweepAnimation.h"
#include "popAnimation.h"
#include "particleManager.h"
#include "guiElement.h"
#include "fluidManager.h"
#include "ofxFastFboReader.h"
#include "explosionAnimation.h"
#include "ofxGoogleAnalytics.h"

#include "oscManager.h"
#include "msgTypes.h"
#include "logger.h"



class SceneBuilder {
public:
    SceneBuilder();
    ~SceneBuilder();
    void setup(StateManager *_state, ofxGoogleAnalytics *_ga, ofVec2f _topLeft, ofVec2f _bottomRight);
    void updateAnimation();
    void updateGenerativeSettings();
    void drawAnimation();
    void update();
    void drawModeSetName(const int &_value);
    void generateFinalComposite();
    ofPixels getPixels();
    void draw();
    
    ofVec2f getTopLeft() { return topLeft; }
    ofVec2f getBottomRight() { return bottomRight; }
    
    ofParameterGroup getFluidParams() { return fluidParams; };
    ofParameterGroup getAnimationParams() { return animParams; };
    
    void onExplosionEvent(ExplosionMsg &em);
    void onSweepEvent(SweepMsg &sm);
    void onSceneChange();
    void onUserControl(bool &uc);

    ofVec2f deNormalize(ofVec2f &inputVector);
    
    
    ofFbo animationFbo;
    ofFbo compositeFbo;
    
    FluidManager fluid;
    
protected:
    
    StateManager *state;
    ofxGoogleAnalytics *ga;
    
    ofParameterGroup animParams;
    ofParameter<bool>bUserInControl;
    ofParameter<int>drawMode;
    ofParameter<string>drawName;
    ofParameter<float>transitionTime;
    ofParameter<float>particleForceX;
    ofParameter<float>particleForceY;
    
    
    
    ofParameterGroup fluidParams;
    
    //particle managers
    ParticleManager userPM;
    
    //generative animations
    SweepAnimation sweepAnim;
    PopAnimation popAnim;
    ExplosionAnimation explodeAnim;
    
    //world size variables
    int drawWidth, drawHeight;
    ofVec2f topLeft;
    ofVec2f bottomRight;
    
    ofPixels compositePix;
    ofxFastFboReader reader;
    
    
    struct generativeSetting {
        //fluid params to be changed generatively
        float fDissipation;
        float fVorticity;
        float fViscosity;
        float fSpeed;
        float fCellSize;
        float fGravityX;
        float fGravityY;
        
        //animation params to be changed generatively
        float exlBright;
        float popBright;
        float sweepBright;
    };
    
    generativeSetting oldGenParams;
    generativeSetting newGenParams;
    float initTime;
    float endTime;
    
};

#endif /* defined(__CLP_Knoxville_Wall__sceneBuilder__) */

// =============================================================================
//
// Copyright (C) 2016 Jakob Marsico <http://ultralowres.com>
// based on example code from Christopher Baker <http://christopherbaker.net>



#pragma once


#include "ofMain.h"
#include "ofxJSONRPC.h"
#include "fluidManager.h"
#include "ofxGui.h"



class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void setupServer();
    
    void setupGui();
//    void setupFluid();
    
    
    void updateAnimation();
//    void updateFluid();
    
    void drawAnimationFbo();
    
    void drawModeSetName(int &_value);

    
    void getSlider(ofx::JSONRPC::MethodArgs& args);
    void ping();
    void pong();

    ofx::HTTP::JSONRPCServer server;
    int drawWidth, drawHeight;
    
    
    //GUI
    ofxPanel			gui;
    ofParameter<float>	guiFPS;
    ofParameter<string> ipAddress;
    ofParameter<bool>	doFullScreen;
    ofParameter<bool>	toggleGuiDraw;
    ofParameter<bool>   toggleFluidDraw;
    ofParameter<bool>   sendOut;
    ofParameter<int>	drawMode;
    ofParameter<string> drawName;

    
    fluidManager fluid;
    
    
    ///////////////////// ANIMATION //////////////////////////////
    ofFbo animationFbo;

private:


    // We use a mutex to protect any variables that can be
    // modified by multiple clients.  In our case, userText must be protected.
    // We mark the mutex as mutable so that it can be used in const functions.
    mutable std::mutex mutex;
    
    
    // set any update uniforms in this function
    ofEasyCam cam;

};

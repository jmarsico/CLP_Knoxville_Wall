// =============================================================================
//
// Copyright (C) 2016 Jakob Marsico <http://ultralowres.com>
// based on example code from Christopher Baker <http://christopherbaker.net>



#pragma once


#include "ofMain.h"
#include "ofxJSONRPC.h"
#include "stateManager.h"
#include "sceneBuilder.h"
#include "ofxGui.h"
#include "FluidManager.h"
#include "csvLoader.h"
#include "lightPoint.h"
#include "kinetManager.h"


class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyReleased(int key);
    
    void setupServer();
    
    void setupGui();


    
    void getSlider(ofx::JSONRPC::MethodArgs& args);
    void ping();
    void pong();

    ofx::HTTP::JSONRPCServer server;
    int drawWidth, drawHeight;
    
    
    //GUI
    ofxPanel fluidGui;
    ofxPanel animGui;
    ofxPanel systemGui;
    ofParameter<int> FPS;
    ofParameter<bool> bShowAnim;
    ofParameter<bool> bSendToWall;
    
    
    StateManager state;
    SceneBuilder scene;
    CsvLoader csv;
    KinetManager kinet;
    
    vector<LightPoint> lights;
    ofPixels compPix;
    
    
    

private:


    // We use a mutex to protect any variables that can be
    // modified by multiple clients.  In our case, userText must be protected.
    // We mark the mutex as mutable so that it can be used in const functions.
    mutable std::mutex mutex;


};

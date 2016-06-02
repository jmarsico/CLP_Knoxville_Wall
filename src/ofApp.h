// =============================================================================
//
// Copyright (C) 2016 Jakob Marsico <http://ultralowres.com>



#pragma once


#include "ofMain.h"
#include "stateManager.h"
#include "sceneBuilder.h"
#include "ofxGui.h"
#include "fluidManager.h"
#include "csvLoader.h"
#include "lightPoint.h"
#include "kinetManager.h"
#include "oscManager.h"
#include "ofxGoogleAnalytics.h"



class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyReleased(int key);


    void setupGui();
    void handleEvent(string & name);



    int drawWidth, drawHeight;


    //GUI
    ofxPanel fluidGui;
    ofxPanel animGui;
    ofxPanel systemGui;
    ofParameter<int> FPS;
    ofParameter<bool> bShowAnim;
    ofParameter<bool> bSendToWall;
    ofParameter<bool> mouseLoc;


    StateManager state;
    SceneBuilder scene;
    CsvLoader csv;
    KinetManager kinet;

    vector<LightPoint> lights;
    vector<uint8_t> lightVals;
    ofPixels compPix;


    OscManager osc;
    ofxGoogleAnalytics ga;
    
    

private:


    // We use a mutex to protect any variables that can be
    // modified by multiple clients.  In our case, userText must be protected.
    // We mark the mutex as mutable so that it can be used in const functions.
    mutable std::mutex mutex;


};

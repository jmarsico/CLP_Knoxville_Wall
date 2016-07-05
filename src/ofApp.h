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



class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();
    void keyReleased(int key);

    void turnOffLights();
    void turnOnLights();

    void setupGui();

    void onSchedulerEvent(bool &onOff);
    void onOscOnOff(bool &onOff);


    //GUI
    ofxPanel fluidGui;
    ofxPanel animGui;
    ofxPanel systemGui;
    ofParameter<int> FPS;
    ofParameter<bool> bShowAnim;
    ofParameter<bool> mouseLoc;
    ofParameter<int> avgSampSize;
    ofParameter<bool> bSendToLights;
    bool bShowGui;
    
    StateManager state;
    SceneBuilder scene;
    KinetManager kinet;
    OscManager osc;

    CsvLoader csv;
    vector<LightPoint> lights;
    vector<uint8_t> lightVals;
    ofPixels compPix;
    
    ofImage logo;
    ofImage teenRoom;
    ofImage frontWall;
    ofImage entrance;
    
    ofParameter<bool> bTestSequence;
    ofParameter<int> testCurrentLight;

};

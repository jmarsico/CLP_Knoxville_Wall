// =============================================================================
//
// Copyright (C) 2016 Jakob Marsico <http://ultralowres.com>



#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(44);
//    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //set up google analytics
    ga.setShouldReportFramerates(true);
    ga.setFramerateReportInterval(60);
    ga.setEnabled(true);
    ga.setUserID("ULR_Studio");
    ga.setup("UA-77526554-1",				//google track ID << REPLACE WITH YOURS!
             "CLP-Knoxville",	//app name
             "v1",									//app version
             "01",						//ap id
             "01"				//app installer id
             );

    
    
    
    
    scene.setup(&state, &ga, ofVec2f(0,200), ofVec2f(ofGetWidth(),500));

    //setup the JSONRPC server
    setupGui();

    drawWidth = 1280;
    drawHeight = 720;

    csv.loadLightPoints("allPoints.csv");

    for(size_t i = 0; i < csv.getNumLights(); i++){
        LightPoint lp;
        ofVec2f p = csv.getLightLoc(i);
        ofVec2f trans(50, 300);
        p += trans;

        p *= 2.0;
        lp.setup(p);
        lights.push_back(lp);
        
        lightVals.push_back(0);
    }
    ofLogNotice("ofApp::setup") << "number of lights from CSV: " << lights.size();

    
    kinet.setup(lights.size());

    osc.setup();
    

}

//------------------------------------------------------
void ofApp::update(){
    FPS = ofGetFrameRate();

    ofSetColor(255);
    osc.update();
    scene.update();
    state.update();

    scene.generateFinalComposite();
    compPix = scene.getPixels();

    
    
    for(size_t i = 0; i < lights.size(); i++){
        ofVec2f loc = lights[i].getLoc();
        int val = compPix.getColor(loc.x, loc.y).getBrightness();
        lights[i].setAvgSamplingSize(avgSampSize);
        lights[i].setCurrentVal(val);
        lightVals[i] = lights[i].getAvgVal();
    }

    if(bSendToLights){
        kinet.update(lightVals);
        kinet.send();
    }
    
    ga.update();
}

void ofApp::handleEvent(string &name){
    ofLog() << "event! " << name;
}


//------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofSetColor(255);


    if(bShowAnim) scene.draw();


    systemGui.draw();
    animGui.draw();
    fluidGui.draw();


    for(size_t i = 0; i < lights.size(); i ++){
        lights[i].draw();
    }

    if(mouseLoc){
        ofDrawBitmapStringHighlight(ofToString(mouseX) + "," + ofToString(mouseY), mouseX, mouseY);
    }

 }



//------------------------------------------------------
void ofApp::setupGui(){


    int guiColorSwitch = 0;
    ofColor guiHeaderColor[2];
    guiHeaderColor[0].set(200, 150);
    guiHeaderColor[1].set(150, 150);
    ofColor guiFillColor[2];
    guiFillColor[0].set(200, 150);
    guiFillColor[1].set(200, 150);


    systemGui.setup("system", "systemSettings.xml");
    systemGui.add(FPS.set("framerate", 0, 0, 100));
    systemGui.add(bShowAnim.set("show anim", false));
    systemGui.add(bSendToWall.set("send to lights", false));
    systemGui.add(mouseLoc.set("show mouselocation", false));
    systemGui.add(avgSampSize.set("smoothing", 1, 1, 20));
    systemGui.add(bSendToLights.set("lights on/off", true));
    systemGui.setPosition(ofPoint(10,10));
//
    fluidGui.setup("fluid", "settings.xml");
    fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    fluidGui.add(scene.getFluidParams());
//
//
//
//
    animGui.setup("animation", "animSettings.xml");
    animGui.add(scene.getAnimationParams());

    // if the settings file is not present the parameters will not be set during this setup

    systemGui.loadFromFile("systemSettings.xml");
    fluidGui.loadFromFile("settings.xml");
    animGui.loadFromFile("animSettings.xml");

    fluidGui.minimizeAll();
    animGui.minimizeAll();

    fluidGui.setPosition(ofGetWidth() - fluidGui.getWidth() - 10,10);
    systemGui.setPosition(ofGetWidth() - fluidGui.getWidth() - systemGui.getWidth() - 20, 10);
    animGui.setPosition(systemGui.getPosition().x, 10 + systemGui.getHeight());
}


//------------------------------------------------------
void ofApp::exit(){

    // Set the logger back to the default to make sure any
    // remaining messages are logged correctly.
    ofLogToConsole();
    ofClear(0);
}


void ofApp::keyReleased(int key){
}

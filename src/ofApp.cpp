// =============================================================================
//
// Copyright (C) 2016 Jakob Marsico <http://ultralowres.com>



#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(44);
//    ofSetLogLevel(OF_LOG_VERBOSE);


    scene.setup(&state, ofVec2f(0,290), ofVec2f(ofGetWidth(),620));
    state.setTurnOnTime("8:00");
    state.setTurnOffTime("23:00");

    //setup the JSONRPC server
    setupGui();

    drawWidth = 1280;
    drawHeight = 720;

    csv.loadLightPoints("allPoints.csv");

    for(size_t i = 0; i < csv.getNumLights(); i++){
        LightPoint lp;
        ofVec2f p = csv.getLightLoc(i);
        ofVec2f trans(18, 220);
        p += trans;

        p *= 2.7;
        lp.setup(p);
        lights.push_back(lp);

        lightVals.push_back(0);
    }
    ofLogNotice("ofApp::setup") << "number of lights from CSV: " << lights.size();

    kinet.setup(lights.size());
    osc.setup();

    logo.load("textLogo.png");
    bShowGui = false;


    ofAddListener(StateManager::turnOnOff, this, &ofApp::onSchedulerEvent);
    ofAddListener(OscManager::turnOnOff, this, &ofApp::onOscOnOff);

}

//------------------------------------------------------
void ofApp::update(){
    FPS = ofGetFrameRate();

    ofSetColor(255);
    osc.update(bSendToLights);
    scene.update();
    state.update();

    osc.setPauseTimeRemaining(state.getPauseTimeRemaining());

    scene.generateFinalComposite();
    compPix = scene.getPixels();


    //if sending to lights, update from animation
    for(size_t i = 0; i < lights.size(); i++){
        ofVec2f loc = lights[i].getLoc();
        int val = compPix.getColor(loc.x, loc.y).getBrightness();
        lights[i].setAvgSamplingSize(avgSampSize);
        lights[i].setCurrentVal(val);

        //if we are sending to the wall, take light val
        //if not, send zeros
        if(bSendToLights){
            lightVals[i] = lights[i].getAvgVal();
        } else {
            lightVals[i] = 0;
        }
    }

    //update the kinet manager
    kinet.update(lightVals);
    //send to the wall
    kinet.send();

    //update the google analytics
}

void ofApp::handleEvent(string &name){
    ofLog() << "event! " << name;
}


//------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofSetColor(255);

    for(size_t i = 0; i < lights.size(); i ++){
        lights[i].draw();
    }

    ofSetColor(255);
    logo.draw(20,20, logo.getWidth() * 0.20, logo.getHeight() * 0.20  );

    ofSetColor(50);
    if(bShowAnim) scene.draw();

    ofSetColor(255);
    if(bShowGui){
        systemGui.draw();
        animGui.draw();
        fluidGui.draw();
        ofShowCursor();
    } else { ofHideCursor();}

    if(mouseLoc){
        ofDrawBitmapStringHighlight(ofToString(mouseX) + "," + ofToString(mouseY), mouseX, mouseY);
    }

    //draw lines showing different sections
    ofSetColor(200);
    ofDrawLine(345, 350, 345, 600);
    ofDrawLine(1547, 350, 1547, 600);
    ofSetColor(255);


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
void ofApp::turnOffLights(){

    bSendToLights = false;
    for(size_t i = 0; i < lightVals.size(); i++){
        lightVals[i] = 0;
    }
    kinet.update(lightVals);
    kinet.send();


}

//------------------------------------------------------
void ofApp::turnOnLights(){
    bSendToLights = true;

}

//------------------------------------------------------
void ofApp::onSchedulerEvent(bool &onOff){
    if(onOff == true){
        turnOnLights();
        ofLog() << "TURN ON LIGHTS FROM SCHEDULE";
    } else if(onOff == false){
        turnOffLights();
        ofLog() << "TURN OFF LIGHTS FROM SCHEDULE";
    }
}

//------------------------------------------------------
void ofApp::onOscOnOff(bool &onOff){
    if(onOff == true){
        turnOnLights();
    } else if(onOff == false){
        turnOffLights();
    }
}



//------------------------------------------------------
void ofApp::exit(){

    // Set the logger back to the default to make sure any
    // remaining messages are logged correctly.
    ofLogToConsole();
    ofClear(0);

    turnOffLights();


}


void ofApp::keyReleased(int key){
    if(key == 'g'){
        bShowGui = !bShowGui;
    }
}

// =============================================================================
//
// Copyright (C) 2016 Jakob Marsico <http://ultralowres.com>
// based on example code from Christopher Baker <http://christopherbaker.net>



#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);

    scene.setup(&state, ofVec2f(60,300), ofVec2f(1080,450));
    
    //setup the JSONRPC server
    setupServer();
    setupGui();
    
    drawWidth = ofGetWidth();
    drawHeight = ofGetHeight();
    
    csv.loadLightPoints("allPoints.csv");
    
    for(size_t i = 0; i < csv.getNumLights(); i++){
        LightPoint lp;
        ofVec2f p = csv.getLightLoc(i);
        ofVec2f trans(50, 300);
        p += trans;
        
        p *= 1.5;
        lp.setup(p);
        lights.push_back(lp);
    }
    ofLogNotice("ofApp::setup") << "number of lights from CSV: " << lights.size();
    
    kinet.setup(lights.size());

    osc.setup(&scene);
    
}

//------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    FPS = ofGetFrameRate();

    ofSetColor(255);
    scene.update();
    
    scene.generateFinalComposite();
    compPix = scene.getPixels();
    
    for(size_t i = 0; i < lights.size(); i++){
        ofVec2f loc = lights[i].getLoc();
        int val = compPix.getColor(loc.x, loc.y).getBrightness();
        lights[i].setCurrentVal(val);
    }
    
    osc.update();
    
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
    
    fluidGui.setPosition(10,10);
    systemGui.setPosition(20 + fluidGui.getWidth(), 10);
    animGui.setPosition(20 + fluidGui.getWidth(), 10 + systemGui.getHeight());
}


//------------------------------------------------------
void ofApp::exit(){
    
    // Set the logger back to the default to make sure any
    // remaining messages are logged correctly.
    ofLogToConsole();
}

//------------------------------------------------------
void ofApp::setupServer(){
    ofx::HTTP::JSONRPCServerSettings settings;
    settings.setPort(8197);
    
    // Initialize the server.
    server.setup(settings);
    server.registerMethod("test-slider",
                          "Send a JSONRPC slider",
                          this,
                          &ofApp::getSlider);
    
    // Start the server.
    server.start();

}


//------------------------------------------------------
void ofApp::getSlider(ofx::JSONRPC::MethodArgs& args){
    std::unique_lock<std::mutex> lock(mutex);
    ofLog() << ofToFloat(args.params.asString());
}


void ofApp::keyReleased(int key){
}


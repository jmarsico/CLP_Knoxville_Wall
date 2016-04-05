// =============================================================================
//
// Copyright (C) 2016 Jakob Marsico <http://ultralowres.com>
// based on example code from Christopher Baker <http://christopherbaker.net>



#include "ofApp.h"


void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetLogLevel(OF_LOG_VERBOSE);

    //setup the JSONRPC server
    setupServer();
    setupGui();
    
    drawWidth = ofGetWidth();
    drawHeight = ofGetHeight();
    
    
    // Animation

    
    scene.setup(&state);
    
    fluid.init(drawWidth, drawHeight);
    
}

//------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));

    scene.update();
    
    fluid.update(scene.animationFbo);

}


//------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    
    fluid.draw(5);
    
//    scene.update();
    scene.generateFinalComposite();
    scene.draw();
//    scene.compositeFbo.draw(0,0);
//    scene.fluid.draw(4);
    
//    ofImage img;
//    img.setFromPixels(scene.getPixels());
//    img.draw(0,0);
    
    systemGui.draw();
    animGui.draw();
    fluidGui.draw();
    
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
    
    
    systemGui.setup("system");
    systemGui.add(FPS.set("framerate", 0, 0, 100));
    systemGui.setPosition(ofPoint(10,10));
    
    fluidGui.setup("fluid", "fluidSettings.xml");
    fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    fluidGui.add(scene.fluidParams);
    fluidGui.setPosition(systemGui.getWidth() + 20, 10);
    
    
    
    animGui.setup("animation", "animSettings.xml");
    animGui.add(scene.parameters);
    animGui.setPosition(systemGui.getWidth() + 30 + fluidGui.getWidth(), 10);
    
    // if the settings file is not present the parameters will not be set during this setup

    
    fluidGui.loadFromFile("settings.xml");
    animGui.loadFromFile("animSettings.xml");
    
    fluidGui.minimizeAll();
    animGui.minimizeAll();
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


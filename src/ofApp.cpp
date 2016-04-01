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
    
    drawWidth = ofGetWidth();
    drawHeight = ofGetHeight();
    
    
    // Animation
    animationFbo.allocate(drawWidth, drawHeight);
    animationFbo.begin();
    ofClear(0);
    animationFbo.end();
    
    
    setupGui();

    fluid.init(drawWidth, drawHeight);
    
    
}

//------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
//    deltaTime = ofGetElapsedTimef() - lastTime;
//    lastTime = ofGetElapsedTimef();
    
    updateAnimation();
    drawAnimationFbo();
    fluid.update(animationFbo);

}

//------------------------------------------------------
void ofApp::updateAnimation(){
    
    ofFill();
    
}

//------------------------------------------------------
void ofApp::drawAnimationFbo(){
    
    animationFbo.begin();
    ofClear(0);
    ofBackground(0);
    ofFill();
    ofSetColor(255);
    ofDrawCircle(700, 200, 200 * ofNoise(ofGetElapsedTimef()));
    animationFbo.end();
    
}




//--------------------------------------------------------------
void ofApp::drawModeSetName(int &_value) {
    switch(_value) {
        case DRAW_COMPOSITE:		drawName.set("Composite"); break;
        case DRAW_PARTICLES:		drawName.set("Particles"); break;
        case DRAW_FLUID_FIELDS:		drawName.set("Fluid Fields"); break;
        case DRAW_FLUID_DENSITY:    drawName.set("Fluid Density"); break;
        case DRAW_FLUID_OBSTACLE:	drawName.set("Fluid Obstacle"); break;
//        case DRAW_OPTICAL_FLOW:		drawName.set("Optical Flow"); break;
        case DRAW_SOURCE:			drawName.set("Source"); break;
    }
}



//------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    fluid.draw(drawMode);
    gui.draw();
    
 }



//------------------------------------------------------
void ofApp::setupGui(){
    
    
    gui.setup("settings");
    gui.setDefaultBackgroundColor(ofColor(0, 0, 0, 127));
    gui.setDefaultFillColor(ofColor(160, 160, 160, 160));
    gui.add(guiFPS.set("average FPS", 0, 0, 60));
    gui.add(doFullScreen.set("fullscreen (F)", false));
    gui.add(toggleGuiDraw.set("show gui (G)", false));
    gui.add(drawMode.set("draw mode", DRAW_COMPOSITE, DRAW_COMPOSITE, DRAW_SOURCE));
    drawMode.addListener(this, &ofApp::drawModeSetName);
    gui.add(drawName.set("MODE", "draw name"));
    
    
    
    int guiColorSwitch = 0;
    ofColor guiHeaderColor[2];
    guiHeaderColor[0].set(200, 150);
    guiHeaderColor[1].set(150, 150);
    ofColor guiFillColor[2];
    guiFillColor[0].set(200, 150);
    guiFillColor[1].set(200, 150);
    

    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(fluid.opticalFlow.parameters);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(fluid.velocityMask.parameters);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(fluid.fluidSimulation.parameters);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(fluid.particleFlow.parameters);
    
    // if the settings file is not present the parameters will not be set during this setup
    if (!ofFile("settings.xml"))
        gui.saveToFile("settings.xml");
    
    gui.loadFromFile("settings.xml");
    
    gui.minimizeAll();
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


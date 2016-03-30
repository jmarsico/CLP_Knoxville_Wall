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
    
    
    setupFluid();
    setupGui();

    
    
}

//------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
    deltaTime = ofGetElapsedTimef() - lastTime;
    lastTime = ofGetElapsedTimef();
    
    updateAnimation();
    drawAnimationFbo();
    updateFluid();
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

//------------------------------------------------------
void ofApp::updateFluid(){
    opticalFlow.setSource(animationFbo.getTexture());
    opticalFlow.update();
    
    velocityMask.setDensity(animationFbo.getTexture());
    velocityMask.setVelocity(opticalFlow.getOpticalFlow());
    velocityMask.update();
    
    fluidSimulation.addVelocity(opticalFlow.getOpticalFlowDecay());
    fluidSimulation.addDensity(velocityMask.getColorMask());
    fluidSimulation.addTemperature(velocityMask.getLuminanceMask());
    fluidSimulation.update();
    
    if (particleFlow.isActive()) {
        particleFlow.setSpeed(fluidSimulation.getSpeed());
        particleFlow.setCellSize(fluidSimulation.getCellSize());
        particleFlow.addFlowVelocity(opticalFlow.getOpticalFlow());
        particleFlow.addFluidVelocity(fluidSimulation.getVelocity());
        //		particleFlow.addDensity(fluidSimulation.getDensity());
        particleFlow.setObstacle(fluidSimulation.getObstacle());
    }
    particleFlow.update();

}


//--------------------------------------------------------------
void ofApp::drawModeSetName(int &_value) {
    switch(_value) {
        case DRAW_COMPOSITE:		drawName.set("Composite"); break;
        case DRAW_PARTICLES:		drawName.set("Particles"); break;
        case DRAW_FLUID_FIELDS:		drawName.set("Fluid Fields"); break;
        case DRAW_FLUID_TEMPERATURE:drawName.set("Fld Temperature"); break;
        case DRAW_FLUID_DIVERGENCE: drawName.set("Fld Divergence"); break;
        case DRAW_FLUID_VORTICITY:	drawName.set("Fluid Vorticity"); break;
        case DRAW_FLUID_BUOYANCY:	drawName.set("Fluid Buoyancy"); break;
        case DRAW_FLUID_OBSTACLE:	drawName.set("Fluid Obstacle"); break;
        case DRAW_OPTICAL_FLOW:		drawName.set("Optical Flow"); break;
        case DRAW_SOURCE:			drawName.set("Source"); break;
    }
}



//------------------------------------------------------
void ofApp::draw(){
    
    ofBackground(0);
    switch(drawMode.get()) {
        case DRAW_COMPOSITE: drawComposite(); break;
        case DRAW_PARTICLES: drawParticles(); break;
        case DRAW_FLUID_FIELDS: drawFluidFields(); break;
        case DRAW_FLUID_DENSITY: drawFluidDensity(); break;
        case DRAW_FLUID_TEMPERATURE: drawFluidTemperature(); break;
        case DRAW_FLUID_DIVERGENCE: drawFluidDivergence(); break;
        case DRAW_FLUID_VORTICITY: drawFluidVorticity(); break;
        case DRAW_FLUID_BUOYANCY: drawFluidBuoyance(); break;
        case DRAW_FLUID_OBSTACLE: drawFluidObstacle(); break;
        case DRAW_OPTICAL_FLOW: drawOpticalFlow(); break;
        case DRAW_SOURCE: drawSource(); break;
    }

    gui.draw();
    
 }

//--------------------------------------------------------------
void ofApp::drawComposite(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    fluidSimulation.draw(_x, _y, _width, _height);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    if (particleFlow.isActive())
        particleFlow.draw(_x, _y, _width, _height);
    
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawParticles(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    if (particleFlow.isActive())
        particleFlow.draw(_x, _y, _width, _height);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFluidFields(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    pressureField.setPressure(fluidSimulation.getPressure());
    pressureField.draw(_x, _y, _width, _height);
    velocityTemperatureField.setVelocity(fluidSimulation.getVelocity());
    velocityTemperatureField.setTemperature(fluidSimulation.getTemperature());
    velocityTemperatureField.draw(_x, _y, _width, _height);
    temperatureField.setTemperature(fluidSimulation.getTemperature());
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFluidDensity(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    
    fluidSimulation.draw(_x, _y, _width, _height);
    
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFluidVelocity(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    if (showScalar.get()) {
        ofClear(0,0);
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        //	ofEnableBlendMode(OF_BLENDMODE_DISABLED); // altenate mode
        displayScalar.setSource(fluidSimulation.getVelocity());
        displayScalar.draw(_x, _y, _width, _height);
    }
    if (showField.get()) {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        velocityField.setVelocity(fluidSimulation.getVelocity());
        velocityField.draw(_x, _y, _width, _height);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFluidPressure(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofClear(128);
    if (showScalar.get()) {
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        displayScalar.setSource(fluidSimulation.getPressure());
        displayScalar.draw(_x, _y, _width, _height);
    }
    if (showField.get()) {
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        pressureField.setPressure(fluidSimulation.getPressure());
        pressureField.draw(_x, _y, _width, _height);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFluidTemperature(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    if (showScalar.get()) {
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        displayScalar.setSource(fluidSimulation.getTemperature());
        displayScalar.draw(_x, _y, _width, _height);
    }
    if (showField.get()) {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        temperatureField.setTemperature(fluidSimulation.getTemperature());
        temperatureField.draw(_x, _y, _width, _height);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFluidDivergence(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    if (showScalar.get()) {
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        displayScalar.setSource(fluidSimulation.getDivergence());
        displayScalar.draw(_x, _y, _width, _height);
    }
    if (showField.get()) {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        temperatureField.setTemperature(fluidSimulation.getDivergence());
        temperatureField.draw(_x, _y, _width, _height);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFluidVorticity(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    if (showScalar.get()) {
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        displayScalar.setSource(fluidSimulation.getConfinement());
        displayScalar.draw(_x, _y, _width, _height);
    }
    if (showField.get()) {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(255, 255, 255, 255);
        velocityField.setVelocity(fluidSimulation.getConfinement());
        velocityField.draw(_x, _y, _width, _height);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFluidBuoyance(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    if (showScalar.get()) {
        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
        displayScalar.setSource(fluidSimulation.getSmokeBuoyancy());
        displayScalar.draw(_x, _y, _width, _height);
    }
    if (showField.get()) {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        velocityField.setVelocity(fluidSimulation.getSmokeBuoyancy());
        velocityField.draw(_x, _y, _width, _height);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawFluidObstacle(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    fluidSimulation.getObstacle().draw(_x, _y, _width, _height);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawMask(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    velocityMask.draw(_x, _y, _width, _height);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawOpticalFlow(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    if (showScalar.get()) {
        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
        displayScalar.setSource(opticalFlow.getOpticalFlowDecay());
        displayScalar.draw(0, 0, _width, _height);
    }
    if (showField.get()) {
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        velocityField.setVelocity(opticalFlow.getOpticalFlowDecay());
        velocityField.draw(0, 0, _width, _height);
    }
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawSource(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    animationFbo.draw(_x, _y, _width, _height);
    ofPopStyle();
}

////--------------------------------------------------------------
//void ofApp::drawMouseForces(int _x, int _y, int _width, int _height) {
//    ofPushStyle();
//    ofClear(0,0);
//    
//    for(int i=0; i<mouseForces.getNumForces(); i++) {
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
//        if (mouseForces.didChange(i)) {
//            ftDrawForceType dfType = mouseForces.getType(i);
//            if (dfType == FT_DENSITY)
//                mouseForces.getTextureReference(i).draw(_x, _y, _width, _height);
//        }
//    }
//    
//    for(int i=0; i<mouseForces.getNumForces(); i++) {
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        if (mouseForces.didChange(i)) {
//            switch (mouseForces.getType(i)) {
//                case FT_VELOCITY:
//                    velocityField.setVelocity(mouseForces.getTextureReference(i));
//                    velocityField.draw(_x, _y, _width, _height);
//                    break;
//                case FT_TEMPERATURE:
//                    temperatureField.setTemperature(mouseForces.getTextureReference(i));
//                    temperatureField.draw(_x, _y, _width, _height);
//                    break;
//                case FT_PRESSURE:
//                    pressureField.setPressure(mouseForces.getTextureReference(i));
//                    pressureField.draw(_x, _y, _width, _height);
//                    break;
//                default:
//                    break;
//            }
//        }
//    }
//    
//    ofPopStyle();
//}

//--------------------------------------------------------------
void ofApp::drawVelocityDots(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    velocityDots.setVelocity(fluidSimulation.getVelocity());
    velocityDots.draw(_x, _y, _width, _height);
    ofPopStyle();
}


//------------------------------------------------------
void ofApp::setupGui(){
    
    
    gui.setup("settings");
    gui.setDefaultBackgroundColor(ofColor(0, 0, 0, 127));
    gui.setDefaultFillColor(ofColor(160, 160, 160, 160));
    gui.add(guiFPS.set("average FPS", 0, 0, 60));
    gui.add(doFullScreen.set("fullscreen (F)", false));
//    doFullScreen.addListener(this, &ofAppBaseGLWindow::setFullscreen);
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
    gui.add(opticalFlow.parameters);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(velocityMask.parameters);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(fluidSimulation.parameters);
    
    gui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    gui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    gui.add(particleFlow.parameters);
    
    // if the settings file is not present the parameters will not be set during this setup
    if (!ofFile("settings.xml"))
        gui.saveToFile("settings.xml");
    
    gui.loadFromFile("settings.xml");
    
    gui.minimizeAll();
}

//------------------------------------------------------
void ofApp::setupFluid(){
    // process all but the density on 16th resolution
    flowWidth = drawWidth / 4;
    flowHeight = drawHeight / 4;
    
    // FLOW & MASK
    opticalFlow.setup(flowWidth, flowHeight);
    velocityMask.setup(drawWidth, drawHeight);
    
    // FLUID & PARTICLES
    fluidSimulation.setup(flowWidth, flowHeight, drawWidth, drawHeight);
    particleFlow.setup(flowWidth, flowHeight, drawWidth, drawHeight);

    velocityDots.setup(flowWidth / 4, flowHeight / 4);
    
    // VISUALIZATION
    displayScalar.setup(flowWidth, flowHeight);
    velocityField.setup(flowWidth / 4, flowHeight / 4);
    temperatureField.setup(flowWidth / 4, flowHeight / 4);
    pressureField.setup(flowWidth / 4, flowHeight / 4);
    velocityTemperatureField.setup(flowWidth / 4, flowHeight / 4);
    
    // MOUSE DRAW
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


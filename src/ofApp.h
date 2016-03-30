// =============================================================================
//
// Copyright (C) 2016 Jakob Marsico <http://ultralowres.com>
// based on example code from Christopher Baker <http://christopherbaker.net>



#pragma once


#include "ofMain.h"
#include "ofxJSONRPC.h"
#include "ofxFlowTools.h"
#include "ofxGui.h"

using namespace flowTools;

enum drawModeEnum{
    DRAW_COMPOSITE = 0,
    DRAW_FLUID_DENSITY,
    DRAW_PARTICLES,
    DRAW_FLUID_FIELDS,
    DRAW_FLUID_TEMPERATURE,
    DRAW_FLUID_DIVERGENCE,
    DRAW_FLUID_VORTICITY,
    DRAW_FLUID_BUOYANCY,
    DRAW_FLUID_OBSTACLE,
    DRAW_OPTICAL_FLOW,
    DRAW_SOURCE,
};

class ofApp: public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void setupServer();
    
    void setupGui();
    void setupFluid();
    
    
    void updateAnimation();
    void updateFluid();
    
    void drawAnimationFbo();
    
    void drawModeSetName(int &_value);

    
    void getSlider(ofx::JSONRPC::MethodArgs& args);
    void ping();
    void pong();

    ofx::HTTP::JSONRPCServer server;
    
    // FlowTools
    
    
    void drawComposite(){ drawComposite(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawComposite(int _x, int _y, int _width, int _height);
    void drawParticles(){ drawParticles(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawParticles(int _x, int _y, int _width, int _height);
    void drawFluidFields(){ drawFluidFields(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawFluidFields(int _x, int _y, int _width, int _height);
    void drawFluidDensity(){ drawFluidDensity(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawFluidDensity(int _x, int _y, int _width, int _height);
    void drawFluidVelocity(){ drawFluidVelocity(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawFluidVelocity(int _x, int _y, int _width, int _height);
    void drawFluidPressure(){ drawFluidPressure(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawFluidPressure(int _x, int _y, int _width, int _height);
    void drawFluidTemperature(){ drawFluidTemperature(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawFluidTemperature(int _x, int _y, int _width, int _height);
    void drawFluidDivergence(){ drawFluidDivergence(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawFluidDivergence(int _x, int _y, int _width, int _height);
    void drawFluidVorticity(){ drawFluidVorticity(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawFluidVorticity(int _x, int _y, int _width, int _height);
    void drawFluidBuoyance(){ drawFluidBuoyance(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawFluidBuoyance(int _x, int _y, int _width, int _height);
    void drawFluidObstacle(){ drawFluidObstacle(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawFluidObstacle(int _x, int _y, int _width, int _height);
    void drawMask(){ drawMask(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawMask(int _x, int _y, int _width, int _height);
    void drawOpticalFlow(){ drawOpticalFlow(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawOpticalFlow(int _x, int _y, int _width, int _height);
    void drawSource(){ drawSource(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawSource(int _x, int _y, int _width, int _height);
    void drawMouseForces(){ drawMouseForces(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawMouseForces(int _x, int _y, int _width, int _height);
    void drawVelocityDots(){ drawVelocityDots(0, 0, ofGetWindowWidth(), ofGetWindowHeight()); }
    void drawVelocityDots(int _x, int _y, int _width, int _height);
    
    ofFbo               flowFbo;
    
    int					flowWidth;
    int					flowHeight;
    int					drawWidth;
    int					drawHeight;
    int                 planWidth;
    int                 planHeight;
    
    ftOpticalFlow		opticalFlow;
    ftVelocityMask		velocityMask;
    ftFluidSimulation	fluidSimulation;
    ftParticleFlow		particleFlow;
    
    ofParameterGroup	visualizeParameters;
    ftDisplayScalar		displayScalar;
    ftVelocityField		velocityField;
    ftTemperatureField	temperatureField;
    ftPressureField		pressureField;
    ftVTField			velocityTemperatureField;
    
    ftVelocitySpheres	velocityDots;
    
    int					numDrawForces;
    ftDrawForce*		flexDrawForces;
    int deltaTime, lastTime;
    
    
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
    ofParameter<bool>	showScalar;
    ofParameter<bool>	showField;
    ofParameter<float>	displayScalarScale;
    ofParameter<float>	velocityFieldScale;
    ofParameter<float>	temperatureFieldScale;
    ofParameter<float>	pressureFieldScale;
    ofParameter<bool>	velocityLineSmooth;
    


    


    void setDisplayScalarScale(float& _value) { displayScalar.setScale(_value); }
    void setVelocityFieldScale(float& _value) { velocityField.setVelocityScale(_value); velocityTemperatureField.setVelocityScale(_value); }
    void setTemperatureFieldScale(float& _value) { temperatureField.setTemperatureScale(_value); velocityTemperatureField.setTemperatureScale(_value); }
    void setPressureFieldScale(float& _value) { pressureField.setPressureScale(_value); }
    void setVelocityLineSmooth(bool& _value) { velocityField.setLineSmooth(_value); velocityTemperatureField.setLineSmooth(_value);  }

    
    
    
    
    
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

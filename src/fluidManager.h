//
//  fluidManager.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 3/30/16.
//
//

#ifndef __CLP_Knoxville_Wall__fluidManager__
#define __CLP_Knoxville_Wall__fluidManager__

#include <stdio.h>
#include "ofMain.h"
#include "ofxFlowTools.h"


using namespace flowTools;

enum drawModeEnum{
    DRAW_COMPOSITE = 0,
    DRAW_PARTICLES,
    DRAW_FLUID_FIELDS,
    DRAW_FLUID_DENSITY,
    DRAW_FLUID_OBSTACLE,
//    DRAW_OPTICAL_FLOW,
    DRAW_SOURCE,
};

class FluidManager  {
    
public:
    FluidManager(){}
    void init(int w, int h);
    void update(const ofFbo &inputFbo);
    void draw(int _mode);
    
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
    
    
    void setDisplayScalarScale(float& _value) { displayScalar.setScale(_value); }
    void setVelocityFieldScale(float& _value) { velocityField.setVelocityScale(_value); velocityTemperatureField.setVelocityScale(_value); }
    void setTemperatureFieldScale(float& _value) { temperatureField.setTemperatureScale(_value); velocityTemperatureField.setTemperatureScale(_value); }
    void setPressureFieldScale(float& _value) { pressureField.setPressureScale(_value); }
    void setVelocityLineSmooth(bool& _value) { velocityField.setLineSmooth(_value); velocityTemperatureField.setLineSmooth(_value);  }
    
    
    
    
    ofFbo               flowFbo;
    ofFbo               inputFbo;
    
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

    
    
};


#endif /* defined(__CLP_Knoxville_Wall__fluidManager__) */

//
//  fluidManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 3/30/16.
//
//

#include "fluidManager.h"


void FluidManager::init(int w, int h){
    
    drawWidth = w;
    drawHeight = h;
    
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
    
    
    

}


void FluidManager::update(ofFbo *_inputFbo){
    inputFbo = _inputFbo;
    opticalFlow.setSource(inputFbo->getTexture());
    opticalFlow.update();
    
    velocityMask.setDensity(inputFbo->getTexture());
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
void FluidManager::draw(int _mode){
    
    switch(_mode) {
        case DRAW_COMPOSITE: drawComposite(); break;
        case DRAW_PARTICLES: drawParticles(); break;
        case DRAW_FLUID_FIELDS: drawFluidFields(); break;
        case DRAW_FLUID_DENSITY: drawFluidDensity(); break;
//        case DRAW_FLUID_TEMPERATURE: drawFluidTemperature(); break;
//        case DRAW_FLUID_DIVERGENCE: drawFluidDivergence(); break;
//        case DRAW_FLUID_VORTICITY: drawFluidVorticity(); break;
//        case DRAW_FLUID_BUOYANCY: drawFluidBuoyance(); break;
        case DRAW_FLUID_OBSTACLE: drawFluidObstacle(); break;
//        case DRAW_OPTICAL_FLOW: drawOpticalFlow(); break;
        case DRAW_SOURCE: drawSource(); break;
    }

}


//--------------------------------------------------------------
void FluidManager::drawComposite(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    fluidSimulation.draw(_x, _y, _width, _height);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    if (particleFlow.isActive())
        particleFlow.draw(_x, _y, _width, _height);
    
    
    ofPopStyle();
}

//--------------------------------------------------------------
void FluidManager::drawParticles(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    if (particleFlow.isActive())
        particleFlow.draw(_x, _y, _width, _height);
    ofPopStyle();
}

//--------------------------------------------------------------
void FluidManager::drawFluidFields(int _x, int _y, int _width, int _height) {
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
void FluidManager::drawFluidDensity(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    
    fluidSimulation.draw(_x, _y, _width, _height);
    
    ofPopStyle();
}

////--------------------------------------------------------------
//void FluidManager::drawFluidVelocity(int _x, int _y, int _width, int _height) {
//    ofPushStyle();
//    if (showScalar.get()) {
//        ofClear(0,0);
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        //	ofEnableBlendMode(OF_BLENDMODE_DISABLED); // altenate mode
//        displayScalar.setSource(fluidSimulation.getVelocity());
//        displayScalar.draw(_x, _y, _width, _height);
//    }
//    if (showField.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
//        velocityField.setVelocity(fluidSimulation.getVelocity());
//        velocityField.draw(_x, _y, _width, _height);
//    }
//    ofPopStyle();
//}
//
////--------------------------------------------------------------
//void FluidManager::drawFluidPressure(int _x, int _y, int _width, int _height) {
//    ofPushStyle();
//    ofClear(128);
//    if (showScalar.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
//        displayScalar.setSource(fluidSimulation.getPressure());
//        displayScalar.draw(_x, _y, _width, _height);
//    }
//    if (showField.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        pressureField.setPressure(fluidSimulation.getPressure());
//        pressureField.draw(_x, _y, _width, _height);
//    }
//    ofPopStyle();
//}
//
////--------------------------------------------------------------
//void FluidManager::drawFluidTemperature(int _x, int _y, int _width, int _height) {
//    ofPushStyle();
//    if (showScalar.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
//        displayScalar.setSource(fluidSimulation.getTemperature());
//        displayScalar.draw(_x, _y, _width, _height);
//    }
//    if (showField.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
//        temperatureField.setTemperature(fluidSimulation.getTemperature());
//        temperatureField.draw(_x, _y, _width, _height);
//    }
//    ofPopStyle();
//}
//
////--------------------------------------------------------------
//void FluidManager::drawFluidDivergence(int _x, int _y, int _width, int _height) {
//    ofPushStyle();
//    if (showScalar.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
//        displayScalar.setSource(fluidSimulation.getDivergence());
//        displayScalar.draw(_x, _y, _width, _height);
//    }
//    if (showField.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
//        temperatureField.setTemperature(fluidSimulation.getDivergence());
//        temperatureField.draw(_x, _y, _width, _height);
//    }
//    ofPopStyle();
//}
//
////--------------------------------------------------------------
//void FluidManager::drawFluidVorticity(int _x, int _y, int _width, int _height) {
//    ofPushStyle();
//    if (showScalar.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
//        displayScalar.setSource(fluidSimulation.getConfinement());
//        displayScalar.draw(_x, _y, _width, _height);
//    }
//    if (showField.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
//        ofSetColor(255, 255, 255, 255);
//        velocityField.setVelocity(fluidSimulation.getConfinement());
//        velocityField.draw(_x, _y, _width, _height);
//    }
//    ofPopStyle();
//}
//
////--------------------------------------------------------------
//void FluidManager::drawFluidBuoyance(int _x, int _y, int _width, int _height) {
//    ofPushStyle();
//    if (showScalar.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_DISABLED);
//        displayScalar.setSource(fluidSimulation.getSmokeBuoyancy());
//        displayScalar.draw(_x, _y, _width, _height);
//    }
//    if (showField.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
//        velocityField.setVelocity(fluidSimulation.getSmokeBuoyancy());
//        velocityField.draw(_x, _y, _width, _height);
//    }
//    ofPopStyle();
//}

//--------------------------------------------------------------
void FluidManager::drawFluidObstacle(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    fluidSimulation.getObstacle().draw(_x, _y, _width, _height);
    ofPopStyle();
}

//--------------------------------------------------------------
void FluidManager::drawMask(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    velocityMask.draw(_x, _y, _width, _height);
    ofPopStyle();
}

////--------------------------------------------------------------
//void FluidManager::drawOpticalFlow(int _x, int _y, int _width, int _height) {
//    ofPushStyle();
//    if (showScalar.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//        displayScalar.setSource(opticalFlow.getOpticalFlowDecay());
//        displayScalar.draw(0, 0, _width, _height);
//    }
//    if (showField.get()) {
//        ofEnableBlendMode(OF_BLENDMODE_ADD);
//        velocityField.setVelocity(opticalFlow.getOpticalFlowDecay());
//        velocityField.draw(0, 0, _width, _height);
//    }
//    ofPopStyle();
//}

//--------------------------------------------------------------
void FluidManager::drawSource(int _x, int _y, int _width, int _height) {
    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_DISABLED);
    inputFbo->draw(_x, _y, _width, _height);
    ofPopStyle();
}







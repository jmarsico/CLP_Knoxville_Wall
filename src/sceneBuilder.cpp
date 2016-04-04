//
//  sceneBuilder.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "sceneBuilder.h"

SceneBuilder::SceneBuilder(){}

void SceneBuilder::setup(StateManager *_state){
    state = _state;
    
    drawWidth = ofGetWidth();
    drawHeight = ofGetHeight();
    
    particles.setup();
    sweep.setup();
    fluid.init(drawWidth, drawHeight);
    
    parameters.add(fluid.opticalFlow.parameters);
    parameters.add(fluid.velocityMask.parameters);
    parameters.add(fluid.fluidSimulation.parameters);
    parameters.add(fluid.particleFlow.parameters);
    
    parameters.add(sweep.parameters);
    parameters.add(pop.parameters);
//    parameters.add(fleck.parameters);
}



void SceneBuilder::update(){
    
    drawAnimation();
    
    fluid.update(animationFbo);
}


void SceneBuilder::drawAnimation(){
    
}
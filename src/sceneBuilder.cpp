//
//  sceneBuilder.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "sceneBuilder.h"

//--------------------------------------------------------------
SceneBuilder::SceneBuilder(){

    
    drawWidth = ofGetWidth();
    drawHeight = ofGetHeight();
    
    animationFbo.allocate(drawWidth, drawHeight);
    animationFbo.begin();
    ofClear(0);
    animationFbo.end();
    
    compositeFbo.allocate(drawWidth, drawHeight);
    compositeFbo.begin();
    ofClear(0);
    compositeFbo.end();
    
    particles.setup();
    sweep.setup();
    fluid.init(drawWidth, drawHeight);
    
    parameters.setName("Scene Settings");
    parameters.add(drawMode.set("Draw Mode", DRAW_COMPOSITE, DRAW_COMPOSITE, DRAW_SOURCE));
//    ofAddListener(drawMode, this, &SceneBuilder::drawModeSetName);
    parameters.add(sweep.parameters);
    parameters.add(pop.parameters);
    parameters.add(particles.parameters);
    
    fluidParams.add(fluid.opticalFlow.parameters);
    fluidParams.add(fluid.fluidSimulation.parameters);
    fluidParams.add(fluid.particleFlow.parameters);
    fluidParams.add(fluid.velocityMask.parameters);

//    ofAddListener(state->onSceneChange, this, &SceneBuilder::generateSceneSettings);

}
//--------------------------------------------------------------
void SceneBuilder::setup(StateManager *_state){
    state = _state;
    
}


//--------------------------------------------------------------
void SceneBuilder::update(){
    
    updateAnimation();
    drawAnimation();
    fluid.update(animationFbo);
}

void SceneBuilder::updateAnimation(){
    
}

//--------------------------------------------------------------
void SceneBuilder::drawAnimation(){
    
    animationFbo.begin();
    ofClear(255);
    //draw animations based on scene
    particles.draw();
    animationFbo.end();
    
    
}

void SceneBuilder::generateSceneSettings(int &newScene){
    
    //THIS IS WHERE GENERATIVE STUFF HAPPENS
    
    //change settings of different animations
    /*eg: 
    sweepAnimation on/off
     sweepAnimation velocity = ofRandom(1.f);
     popAnimation spawnProb = ofRandom(2.3);
     fluid (random on/off)
     
    */
}



ofPixels SceneBuilder::generateFinalComposite(){
    
    compositeFbo.begin();
    fluid.draw(drawMode);
    compositeFbo.end();
    
    reader.readToPixels(compositeFbo, compositePix);
    
    return compositePix;
    
    
}

void SceneBuilder::draw(){
    compositeFbo.draw(0,0);
}



//--------------------------------------------------------------
void SceneBuilder::drawModeSetName(int &_value) {
    switch(_value) {
        case DRAW_COMPOSITE:		drawName.set("Composite"); break;
        case DRAW_PARTICLES:		drawName.set("Particles"); break;
        case DRAW_FLUID_FIELDS:		drawName.set("Fluid Fields"); break;
        case DRAW_FLUID_DENSITY:    drawName.set("Fluid Density"); break;
        case DRAW_FLUID_OBSTACLE:	drawName.set("Fluid Obstacle"); break;
        case DRAW_SOURCE:			drawName.set("Source"); break;
    }
}


SceneBuilder::~SceneBuilder(){
//    ofRemoveListener(state->onSceneChange, this, &SceneBuilder::generateSceneSettings);
}


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

    

    

//    ofAddListener(state->onSceneChange, this, &SceneBuilder::generateSceneSettings);

}
//--------------------------------------------------------------
void SceneBuilder::setup(StateManager *_state){
    state = _state;
   
    drawWidth = ofGetWidth();
    drawHeight = ofGetHeight();
    
    fluid.init(drawWidth, drawHeight);
    

    
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
    
    
    animParams.setName("Scene Settings");
    animParams.add(drawMode.set("Draw Mode", DRAW_COMPOSITE, DRAW_COMPOSITE, DRAW_SOURCE));
    
    //    ofAddListener(SceneBuilder::drawMode, this, &SceneBuilder::drawModeSetName);
    animParams.add(drawName.set("", ""));
    animParams.add(sweep.parameters);
    animParams.add(pop.parameters);
    animParams.add(particles.parameters);
    
    fluidParams.add(fluid.velocityMask.parameters);
    fluidParams.add(fluid.opticalFlow.parameters);
    fluidParams.add(fluid.fluidSimulation.parameters);
    fluidParams.add(fluid.particleFlow.parameters);
    
    
}

ofParameterGroup SceneBuilder::getFluidParams(){
    return fluidParams;
}

ofParameterGroup SceneBuilder::getAnimationParams(){
    return animParams;
}


//--------------------------------------------------------------
void SceneBuilder::update(){
    
    updateAnimation();
    drawAnimation();
    fluid.update(animationFbo);
    drawModeSetName(drawMode.get());
}

//--------------------------------------------------------------
void SceneBuilder::updateAnimation(){
    
    ofVec2f acc(0.0, 0.0);
    
    if(ofGetFrameNum() % 100 == 0){
        particles.explosion(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), 100);
    }
    particles.update(acc);
}

//--------------------------------------------------------------
void SceneBuilder::drawAnimation(){
    
    animationFbo.begin();
    ofClear(0);
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


//--------------------------------------------------------------
void SceneBuilder::generateFinalComposite(){
    
    compositeFbo.begin();
    ofClear(0);
    fluid.draw(drawMode);
    compositeFbo.end();
    
//    reader.readToPixels(compositeFbo, compositePix);
    
}

//--------------------------------------------------------------
ofPixels SceneBuilder::getPixels(){
    return compositePix;

}


//--------------------------------------------------------------
void SceneBuilder::draw(){
//    compositeFbo.draw(0,0);
//    animationFbo.draw(0,0);
//    compositeFbo.draw(0, 0, ofGetWidth()/2, ofGetHeight()/2);
    fluid.draw(drawMode);
//    animationFbo.draw(0, ofGetHeight()/2, ofGetWidth()/2, ofGetHeight()/2);

}



//--------------------------------------------------------------
void SceneBuilder::drawModeSetName(const int &_value) {
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


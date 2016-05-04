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
    
    
    
    

}
//--------------------------------------------------------------
void SceneBuilder::setup(StateManager *_state, ofVec2f _topLeft, ofVec2f _bottomRight){
    
    //pointer to global state manager
    state = _state;
   
    //set up location parameters
    drawWidth = ofGetWidth();
    drawHeight = ofGetHeight();
    topLeft = _topLeft;
    bottomRight = _bottomRight;
    
    fluid.init(drawWidth, drawHeight);
    
    animationFbo.allocate(drawWidth, drawHeight);
    animationFbo.begin();
    ofClear(0);
    animationFbo.end();
    
    compositeFbo.allocate(drawWidth, drawHeight);
    compositeFbo.begin();
    ofClear(0);
    compositeFbo.end();
    
    //particle managers (we have two, one for generative, one for users)
    generativePM.setup();              //set up the generative particle manager
    userPM.setup();
    
    sweepAnim.setup();                  //set up sweep
    popAnim.setup(&generativePM);
    explodeAnim.setup(&generativePM);      //setup and pass reference to particle manager
    
    //parameters & gui
    animParams.setName("Scene Settings");
    animParams.add(drawMode.set("Draw Mode", DRAW_COMPOSITE, DRAW_COMPOSITE, DRAW_SOURCE));
    animParams.add(drawName.set("", ""));
    animParams.add(particleForceX.set("particle forces X", 0.f, 0.f, 5.f));
    animParams.add(particleForceY.set("particle forces Y", 0.f, 0.f, 5.f));
    animParams.add(sweepAnim.parameters);
    animParams.add(popAnim.parameters);
    animParams.add(explodeAnim.parameters);
    animParams.add(generativePM.parameters);
    animParams.add(userPM.parameters);
    
    fluidParams.add(fluid.velocityMask.parameters);
    fluidParams.add(fluid.opticalFlow.parameters);
    fluidParams.add(fluid.fluidSimulation.parameters);
    fluidParams.add(fluid.particleFlow.parameters);
    
    //set up event handlers
    ofAddListener(OscManager::explosion, this, &SceneBuilder::onExplosionEvent);
    ofAddListener(StateManager::sceneChange, this, &SceneBuilder::onSceneChange);
    ofAddListener(OscManager::sweep, this, &SceneBuilder::onSweepEvent);
    
    
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
    
    if(explodeAnim.brightness > 0) explodeAnim.update();
    generativePM.setForces(ofVec2f(particleForceX, particleForceY));
    userPM.setForces(ofVec2f(particleForceX, particleForceY));
    
    generativePM.update();
    userPM.update();
    
    if(popAnim.brightness > 0) popAnim.update();

}

//--------------------------------------------------------------
void SceneBuilder::drawAnimation(){
    
    animationFbo.begin();
    ofClear(0);
    //draw animations based on scene
    if(explodeAnim.brightness > 0) explodeAnim.draw();
    if(popAnim.brightness > 0) popAnim.draw();
    
    generativePM.draw(1.);
    userPM.draw(1.);
    
    glDisable(GL_BLEND);
    glPopAttrib();
    animationFbo.end();
    
}

//--------------------------------------------------------------
void SceneBuilder::onSceneChange(){
    
    //THIS IS WHERE GENERATIVE changes HAPPEN
    
    ofLogNotice("SceneBuilder") << "scene change";
    
    //change settings of different animations
    /*eg: 
    sweepAnimation on/off
     sweepAnimation velocity = ofRandom(1.f);
     popAnimation spawnProb = ofRandom(2.3);
     fluid (random on/off)
     
     - fluid-particle size
     - fluid-particle twinkle
     - fluid-particle birth chance
     - fluid-particle on/off


     - fluid-velocity strength
     - fluid-optflow strength
     - fluid-optflow offset
     
     - fluid.fluidSimulation.setDissipation(0.0);
     
       - myParticle size
     
     
    */
    
//
    
    
}


//--------------------------------------------------------------
void SceneBuilder::generateFinalComposite(){
    
    compositeFbo.begin();
    ofClear(0);
    fluid.draw(drawMode);
    compositeFbo.end();
    
    reader.readToPixels(compositeFbo, compositePix);
    
}

//--------------------------------------------------------------
ofPixels SceneBuilder::getPixels(){
    return compositePix;

}


//--------------------------------------------------------------
void SceneBuilder::draw(){
    fluid.draw(drawMode);
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

//--------------------------------------------------------------
void SceneBuilder::onExplosionEvent(ExplosionMsg &em){
    
    userPM.explosion(deNormalize(em.loc), ofMap(em.size, 0.f, 100.f, 0.0, 80.));
}

void SceneBuilder::onSweepEvent(SweepMsg &sm){
    userPM.addVehicle(deNormalize(sm.loc), deNormalize(sm.dest));
}

//--------------------------------------------------------------
ofVec2f SceneBuilder::deNormalize(ofVec2f &inputVector){
    ofVec2f output;
    output.x = ofMap(inputVector.x, 0.f, 100.f, topLeft.x, bottomRight.x);
    output.y = ofMap(inputVector.y, 0.f, 100.f, topLeft.y, bottomRight.y);
    
    return output;
}

//--------------------------------------------------------------
SceneBuilder::~SceneBuilder(){
//    ofRemoveListener(state->onSceneChange, this, &SceneBuilder::generateSceneSettings);
    ofRemoveListener(OscManager::explosion, this, &SceneBuilder::onExplosionEvent);
}


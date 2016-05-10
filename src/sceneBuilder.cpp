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
void SceneBuilder::setup(StateManager *_state, ofxGoogleAnalytics *_ga, ofVec2f _topLeft, ofVec2f _bottomRight){
    
    //pointer to global state manager
    state = _state;
    
    //pointer to global logger
    ga = _ga;
   
    //set up location parameters
    drawWidth = ofGetWidth();
    drawHeight = 720;
    topLeft = _topLeft;
    bottomRight = _bottomRight;
    
    ofClear(0);
    
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
    userPM.setup();
    
    sweepAnim.setup();                  //set up sweep
    popAnim.setup();
    explodeAnim.setup();      //setup and pass reference to particle manager
    
    //parameters & gui
    animParams.setName("Scene Settings");
    animParams.add(drawMode.set("Draw Mode", DRAW_COMPOSITE, DRAW_COMPOSITE, DRAW_SOURCE));
    animParams.add(drawName.set("", ""));
    animParams.add(transitionTime.set("tranition time", 0.5, 0.0, 10.0));
    animParams.add(particleForceX.set("particle forces X", 0.f, 0.f, 5.f));
    animParams.add(particleForceY.set("particle forces Y", 0.f, 0.f, 5.f));
    animParams.add(sweepAnim.parameters);
    animParams.add(popAnim.parameters);
    animParams.add(explodeAnim.parameters);
    animParams.add(userPM.parameters);
    
    fluidParams.add(fluid.velocityMask.parameters);
    fluidParams.add(fluid.opticalFlow.parameters);
    fluidParams.add(fluid.fluidSimulation.parameters);
    fluidParams.add(fluid.particleFlow.parameters);
    
    //set up event handlers
    ofAddListener(OscManager::explosion, this, &SceneBuilder::onExplosionEvent);
    ofAddListener(StateManager::sceneChange, this, &SceneBuilder::onSceneChange);
    ofAddListener(OscManager::sweep, this, &SceneBuilder::onSweepEvent);
    
    
    
    //set up starting value for generative parameters
    oldGenParams.fDissipation = fluid.fluidSimulation.getDissipation();
    oldGenParams.fVorticity = fluid.fluidSimulation.getVorticity();
    oldGenParams.fViscosity = fluid.fluidSimulation.getViscosity();
    oldGenParams.fSpeed = fluid.fluidSimulation.getSpeed();
    oldGenParams.fCellSize = fluid.fluidSimulation.getCellSize();
    oldGenParams.fGravityX = fluid.fluidSimulation.getGravity().x;
    oldGenParams.fGravityY = fluid.fluidSimulation.getGravity().y;
    oldGenParams.exlBright = 0;
    oldGenParams.popBright = 0;
    oldGenParams.sweepBright = 0;
    
    onSceneChange();

    
}


//--------------------------------------------------------------
void SceneBuilder::update(){
    updateGenerativeSettings();
    updateAnimation();
    drawAnimation();
    fluid.update(animationFbo);
    drawModeSetName(drawMode.get());
}

void SceneBuilder::updateGenerativeSettings(){
    
    float now = ofGetElapsedTimef();
    endTime = initTime + transitionTime;
    
    explodeAnim.brightness.set(
                               ofxeasing::map_clamp(now,
                                                    initTime,
                                                    endTime,
                                                    oldGenParams.exlBright,
                                                    newGenParams.exlBright,
                                                    &ofxeasing::linear::easeIn)
                               );
    
    
    popAnim.brightness.set(
                               ofxeasing::map_clamp(now,
                                                    initTime,
                                                    endTime,
                                                    oldGenParams.popBright,
                                                    newGenParams.popBright,
                                                    &ofxeasing::linear::easeIn)
                               );
    
    sweepAnim.brightness.set(
                               ofxeasing::map_clamp(now,
                                                    initTime,
                                                    endTime,
                                                    oldGenParams.sweepBright,
                                                    newGenParams.sweepBright,
                                                    &ofxeasing::linear::easeIn)
                               );
    
    fluid.fluidSimulation.setDissipation(
                                         ofxeasing::map_clamp(now,
                                                              initTime,
                                                              endTime,
                                                              oldGenParams.fDissipation,
                                                              newGenParams.fDissipation,
                                                              &ofxeasing::linear::easeIn)
                               );
    
    fluid.fluidSimulation.setVorticity(
                                         ofxeasing::map_clamp(now,
                                                              initTime,
                                                              endTime,
                                                              oldGenParams.fVorticity,
                                                              newGenParams.fVorticity,
                                                              &ofxeasing::linear::easeIn)
                                         );
    
    fluid.fluidSimulation.setViscosity(
                                         ofxeasing::map_clamp(now,
                                                              initTime,
                                                              endTime,
                                                              oldGenParams.fViscosity,
                                                              newGenParams.fViscosity,
                                                              &ofxeasing::linear::easeIn)
                                         );
    
    fluid.fluidSimulation.setSpeed(
                                         ofxeasing::map_clamp(now,
                                                              initTime,
                                                              endTime,
                                                              oldGenParams.fSpeed,
                                                              newGenParams.fSpeed,
                                                              &ofxeasing::linear::easeIn)
                                         );
    
    fluid.fluidSimulation.setCellSize(
                                         ofxeasing::map_clamp(now,
                                                              initTime,
                                                              endTime,
                                                              oldGenParams.fCellSize,
                                                              newGenParams.fCellSize,
                                                              &ofxeasing::linear::easeIn)
                                         );
    
    fluid.fluidSimulation.setGravity(ofVec2f(
                                      ofxeasing::map_clamp(now,
                                                           initTime,
                                                           endTime,
                                                           oldGenParams.fGravityX,
                                                           newGenParams.fGravityX,
                                                           &ofxeasing::linear::easeIn),
                                             ofxeasing::map_clamp(now,
                                                                  initTime,
                                                                  endTime,
                                                                  oldGenParams.fGravityY,
                                                                  newGenParams.fGravityY,
                                                                  &ofxeasing::linear::easeIn)
                                             )
                                      );
    
    
    
}

//--------------------------------------------------------------
void SceneBuilder::updateAnimation(){
    
    if(explodeAnim.brightness > 0) explodeAnim.update();
    userPM.setForces(ofVec2f(particleForceX, particleForceY));
    
    userPM.update();
    
    
    
    
    if(explodeAnim.brightness > 0) explodeAnim.update();
    if(popAnim.brightness > 0) popAnim.update();
    if(sweepAnim.brightness > 0) sweepAnim.update();

}

//--------------------------------------------------------------
void SceneBuilder::drawAnimation(){
    
    
    
    animationFbo.begin();
    ofClear(0);
    //draw animations based on scene
    if(explodeAnim.brightness > 0) explodeAnim.draw();
    if(popAnim.brightness > 0) popAnim.draw();
    if(sweepAnim.brightness > 0) sweepAnim.draw();
    
    userPM.draw(1.);
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
        - myParicle speed
     
     
    */
    
    initTime = ofGetElapsedTimef();
    
    //copy current gen params to holder for old
    oldGenParams = newGenParams;
    
    
    //generate new param targets
    float r0, r1, r2;
    r0 = ofRandom(10);
    r1 = ofRandom(10);
    r2 = ofRandom(10);
    float sum = r0 + r1 + r2;
    r0 = (r0/sum);
    r1 = r1/sum;
    r2 = r2/sum;

    newGenParams.exlBright = r0;
    newGenParams.popBright = r1;
    newGenParams.sweepBright = r2;
    
    
    //generate new fluid param targets
    newGenParams.fDissipation = ofRandom(0.005, 0.008);
    newGenParams.fVorticity = ofRandom(0.1, 0.7);
    newGenParams.fViscosity = ofRandom(0.1, 0.7);
    newGenParams.fSpeed = ofRandom(30, 70);
    newGenParams.fCellSize = ofRandom(0.3, 0.8);
    newGenParams.fGravityX = ofRandom(-0.03, 0.03);
    newGenParams.fGravityY = ofRandom(-0.03, 0.03);
    
    
    
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
    
    userPM.explosion(deNormalize(em.loc), ofMap(em.size, 0.f, 100.f, 0.0, 80.), ofRandom(1.0));
    ga->sendEvent("KeyboardEvent", "pressed7", '7', "someLabel");
}

//--------------------------------------------------------------
void SceneBuilder::onSweepEvent(SweepMsg &sm){
    userPM.addVehicle(deNormalize(sm.loc), deNormalize(sm.dest), ofRandom(100), ofRandom(100));
    ga->sendEvent("KeyboardEvent", "pressed7", '7', "someLabel");
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
    
    //remove all event listeners
    ofRemoveListener(OscManager::explosion, this, &SceneBuilder::onExplosionEvent);
    ofRemoveListener(OscManager::sweep, this, &SceneBuilder::onSweepEvent);
    ofRemoveListener(StateManager::sceneChange, this, &SceneBuilder::onSceneChange);
    
}


//
//  settingsGenerator.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 5/9/16.
//
//

#include "settingsGenerator.h"


SettingsGenerator::SettingsGenerator(){
    generateNewTargets();
}

void SettingsGenerator::update(float time){
    float now = ofGetElapsedTimef();
    
    
//    fDissipation = ofxeasing::map_clamp(now, initTime, endTime, , endPosition, &ofxeasing::linear::easeIn);
}
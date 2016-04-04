//
//  stateManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#include "stateManager.h"

StateManager::StateManager(){
    
    
    bUserInControl = false;
    sceneTimer = (int)ofRandom(5000, 30000);
    currentScene = (int)ofRandom(5);
    
    
}
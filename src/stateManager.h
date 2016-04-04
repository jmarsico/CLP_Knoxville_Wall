//
//  stateManager.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/4/16.
//
//

#ifndef __CLP_Knoxville_Wall__stateManager__
#define __CLP_Knoxville_Wall__stateManager__

#include <stdio.h>
#include "ofMain.h"

class StateManager{
public:
    
    StateManager();
    void setUserInControl(bool bUserControl);
    void setRunningState(bool onOff);
    void setCurrentScene(int scene);
    
    ofEvent<int> onSceneChange;
    ofEvent<bool> onUserInControl;
    ofEvent<bool> onFullUserControl;
    
    
    int getCurrentScene() { return currentScene; };
    bool getRunningState() { return bIsRunning; };
    bool getIsUserInControl() { return bUserInControl; };
    int getSceneTimeRemaining() { return sceneTimer; };
    
private:
    
    bool bUserInControl;
    bool bIsRunning;
    int sceneTimer;
    int currentScene;
    
};

#endif /* defined(__CLP_Knoxville_Wall__stateManager__) */

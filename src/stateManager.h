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
#include "ofxSimpleTimer.h"
#include "oscManager.h"



class StateManager{
public:
    
    StateManager();
    void update();
    void setUserInControl(bool bUserControl);
    void setRunningState(bool onOff);
    void setCurrentScene(int scene);
    
    
    void setTurnOnTime(string _timestamp);
    void setTurnOffTime(string _timestamp);
    void checkTime();
    float getPauseTimeRemaining();
    
    
    int lastTime;
    int currentTime;
    int turnOnTime;
    int turnOffTime;
    
    
    //event handlers
    void onUserInControl(int &seconds);
    void onTimerComplete(string & name);

    //events
    static ofEvent<void> sceneChange;
    static ofEvent<bool> userControl;
    static ofEvent<bool> turnOnOff;
    
    
    int getCurrentScene() { return currentScene; };
    bool getRunningState() { return bIsRunning; };
    bool getIsUserInControl() { return bUserInControl; };
    int getSceneTimeRemaining();
    
    
protected:
    
    bool bUserInControl;
    bool bIsRunning;
    int currentScene;
    
    ofxSimpleTimer *userControlTimer;
    ofxSimpleTimer *sceneTimer;
};

#endif /* defined(__CLP_Knoxville_Wall__stateManager__) */

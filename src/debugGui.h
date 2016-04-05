#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "stateManager.h"
#include "guiElement.h"

//This handles the debug gui—setting run-time controllable information. 
// Objects that inherit from GuiElement and are added to this 
// will present their parameters in the main debug gui.

extern ofEvent<void> onGuiRefresh;

class DebugGui : public GuiElement{
public:
  DebugGui();
  void setup(StateManager *state);
  void update();
  void draw();
  void addParam(GuiElement *p); 
  void toggleVisibility();


  ofParameter<bool> showMouse;
protected:

  bool showDebug;
  void setCursorState(bool &show) {show ? ofShowCursor() : ofHideCursor();};
  void redrawGui();
  StateManager *state;

  // GUI Elements
  ofxPanel gui;
  ofParameter<string> fps;
  vector<GuiElement *> groups;
  vector<GuiElement *>::iterator groupIterator;
    
    ofxPanel			gui;
    ofParameter<float>	guiFPS;
    ofParameter<int>    numCPUParticles;
    ofParameter<string> ipAddress;
    ofParameter<bool>	doFullScreen;
    ofParameter<bool>	toggleGuiDraw;
    ofParameter<bool>   toggleFluidDraw;
    ofParameter<bool>   sendOut;
    ofParameter<int>	drawMode;
    ofParameter<string> drawName;
    
    
 };
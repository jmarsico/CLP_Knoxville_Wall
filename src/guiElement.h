#pragma once

#include "ofxOsc.h"
#include "ofMain.h"

// This is an interface for being included 
// in the auto-updates of the DebugGui.

class GuiElement {
public:
  ofParameterGroup parameters;
  virtual void redrawGui(){};
};
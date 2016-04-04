#include "DebugGui.h"

//---------------------------------------------------------------
DebugGui::DebugGui() {
  showDebug = false;
  showMouse.addListener(this, &DebugGui::setCursorState);
  ofAddListener(onGuiRefresh, this, &DebugGui::redrawGui);
}

//---------------------------------------------------------------
void DebugGui::setup(StateManager *_state){
  state = _state;

}

//---------------------------------------------------------------
void DebugGui::update(){
  fps = ofToString(ofGetFrameRate());
}

//---------------------------------------------------------------
void DebugGui::draw(){
  if (!showDebug) return;
  gui.draw();
  ofSetColor(200);
  }

//---------------------------------------------------------------
void DebugGui::addParam(GuiElement *p) {
  groups.push_back(p);
  redrawGui();
}

//---------------------------------------------------------------
void DebugGui::toggleVisibility() {
  showDebug = !showDebug;
  if (showDebug) redrawGui();
}

//---------------------------------------------------------------
void DebugGui::redrawGui() {
  ofVec2f pos = gui.getPosition();
  showMouse.setName("Show Mouse");
  gui.clear();
  parameters = ofParameterGroup();
  parameters.setName("Settings");

  parameters.add(fps.set("FPS","0"));
  parameters.add(showMouse);

  for(groupIterator = groups.begin(); groupIterator != groups.end(); ++groupIterator) {
    GuiElement *g = *groupIterator;
    g->redrawGui();
    parameters.add(g->parameters);
  }
  gui.setup(parameters);
  gui.setPosition(pos);
  }

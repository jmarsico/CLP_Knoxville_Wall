// =============================================================================
//
// Copyright (C) 2016 Jakob Marsico <http://ultralowres.com>



#include "ofApp.h"


void ofApp::setup()
{
    //keep framerate to 44 because this is framerate of LED drivers
    ofSetFrameRate(44);

    //set up the scene, pass it reference to the state manager, and the corners of the light arrangement/layout
    scene.setup(&state, ofVec2f(0,290), ofVec2f(ofGetWidth(),620));

    //set the turn on and turn-off times of the system
    state.setTurnOnTime("8:00");
    state.setTurnOffTime("23:00");

    //set up the GUI
    setupGui();
    bShowGui = false;

    //load the CSV document that stores light point locations
    csv.loadLightPoints("allPoints.csv");

    //read the light locations from the CSV document and set up lightPoint objects
    for(size_t i = 0; i < csv.getNumLights(); i++){
        LightPoint lp;
        ofVec2f p = csv.getLightLoc(i);
        ofVec2f trans(18, 220);
        p += trans;

        p *= 2.7;
        lp.setup(p);
        lights.push_back(lp);

        //also add an element to the vector we use to send over KiNet
        lightVals.push_back(0);
    }
    ofLogNotice("ofApp::setup") << "number of lights from CSV: " << lights.size();

    //set up the KiNet connections
    kinet.setup(lights.size());

    //initialize the osc manager
    osc.setup();

    //load the logos and text images
    logo.load("textLogo.png");
    teenRoom.load("Teen_Room.png");
    frontWall.load("Front_Wall.png");
    entrance.load("Entrance.png");

    //add listeners for scheduler events and for on/off events from admin webpage
    ofAddListener(StateManager::turnOnOff, this, &ofApp::onSchedulerEvent);
    ofAddListener(OscManager::turnOnOff, this, &ofApp::onOscOnOff);

}

//------------------------------------------------------
void ofApp::update(){
    FPS = ofGetFrameRate();                 //update the framerate variable
    ofSetColor(255);                        //set color to white (standard when working with overlaid FBOs)

    state.update();                         //update the state manager

    //update the osc manager with any pause timing... to be sent to admin webpage
    osc.setPauseTimeRemaining(state.getPauseTimeRemaining());
    osc.update(bSendToLights);              //update the status of the wall for the osc heartbeat


    scene.update();                         //udpate the scene manager
    scene.generateFinalComposite();         //layer the different FBOs to create composit
    compPix = scene.getPixels();            //pull down the composite image from all layers (fluid, etc)


    //if sending to lights, update from animation
    for(size_t i = 0; i < lights.size(); i++){
        ofVec2f loc = lights[i].getLoc();                               //get the lightPoint's location
        int val = compPix.getColor(loc.x, loc.y).getBrightness();       //sample the composite image at the given location
        lights[i].setAvgSamplingSize(avgSampSize);                      //re-adjust the averaging sample size (if changed in GUI)
        lights[i].setCurrentVal(val);                                   //add the current reading to the averaging samples

        //if we are sending to the wall, take light val
        //if not, send zeros
        if(bSendToLights){
            lightVals[i] = lights[i].getAvgVal();                       //copy the average value for this pixel to the KiNet vector
        } else {
            lightVals[i] = 0;                                           //if we aren't sending to the wall, set KiNet pixel to zero
        }
    }


    //
    if(bTestSequence) {
        for(size_t i = 0; i < lightVals.size(); i++){
            if(i == testCurrentLight){
                lightVals[i] = 255;
            } else{
                lightVals[i] = 0;
            }
        }
    }


    kinet.update(lightVals);                //update the kinet manager
    kinet.send();                           //send to the wal
}



//------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);
    ofSetColor(255);

    //draw each of the lightPoints
    for(size_t i = 0; i < lights.size(); i ++){
        lights[i].draw();
    }

    //draw all of the logos and text assets
    ofSetColor(255);
    logo.draw(20,20, logo.getWidth() * 0.20, logo.getHeight() * 0.20  );
    teenRoom.draw(90    ,645, teenRoom.getWidth() * 0.15, teenRoom.getHeight() * 0.15);
    frontWall.draw(800,645, frontWall.getWidth() * 0.15, frontWall.getHeight() * 0.15);
    entrance.draw(1657, 645, entrance.getWidth() * 0.15, entrance.getHeight() * 0.15);

    //draw the final scene (usually fluid)  we are setting color to 50 so the fluid will appear very dim
    ofSetColor(50);
    if(bShowAnim) scene.draw();

    //draw the GUIs
    ofSetColor(255);
    if(bShowGui){
        systemGui.draw();
        animGui.draw();
        fluidGui.draw();
        ofShowCursor();
    } else { ofHideCursor();}


    //sometimes we want to visualize the mouse coordinates (useful for when setting up layout)
    if(mouseLoc){
        ofDrawBitmapStringHighlight(ofToString(mouseX) + "," + ofToString(mouseY), mouseX, mouseY);
    }

    //draw lines showing different sections
    ofSetColor(200);
    ofDrawLine(345, 350, 345, 600);
    ofDrawLine(1547, 350, 1547, 600);
    ofSetColor(255);


 }



//------------------------------------------------------
void ofApp::setupGui(){


    int guiColorSwitch = 0;
    ofColor guiHeaderColor[2];
    guiHeaderColor[0].set(200, 150);
    guiHeaderColor[1].set(150, 150);
    ofColor guiFillColor[2];
    guiFillColor[0].set(200, 150);
    guiFillColor[1].set(200, 150);

    //system gui, for overall settings
    systemGui.setup("system", "systemSettings.xml");
    systemGui.add(FPS.set("framerate", 0, 0, 100));
    systemGui.add(bShowAnim.set("show anim", false));
    systemGui.add(mouseLoc.set("show mouselocation", false));
    systemGui.add(avgSampSize.set("smoothing", 1, 1, 20));
    systemGui.add(bSendToLights.set("lights on/off", true));
    systemGui.add(bTestSequence.set("test light sequence", true));
    systemGui.add(testCurrentLight.set("current test light", 250, 0, 749));
    systemGui.setPosition(ofPoint(10,10));

    //fluid gui, for controlling everything withing ofxFlowTools
    fluidGui.setup("fluid", "settings.xml");
    fluidGui.setDefaultHeaderBackgroundColor(guiHeaderColor[guiColorSwitch]);
    fluidGui.setDefaultFillColor(guiFillColor[guiColorSwitch]);
    guiColorSwitch = 1 - guiColorSwitch;
    fluidGui.add(scene.getFluidParams());

    //add the animation parameters (this will include everything from the scene)
    animGui.setup("animation", "animSettings.xml");
    animGui.add(scene.getAnimationParams());

    // if the settings files are not present the parameters will not be set during this setup
    systemGui.loadFromFile("systemSettings.xml");
    fluidGui.loadFromFile("settings.xml");
    animGui.loadFromFile("animSettings.xml");

    //minimize everything to begin
    fluidGui.minimizeAll();
    animGui.minimizeAll();

    //set the locations of each GUI
    fluidGui.setPosition(ofGetWidth() - fluidGui.getWidth() - 10,10);
    systemGui.setPosition(ofGetWidth() - fluidGui.getWidth() - systemGui.getWidth() - 20, 10);
    animGui.setPosition(systemGui.getPosition().x, 10 + systemGui.getHeight());
}


//------------------------------------------------------
void ofApp::turnOffLights(){

    bSendToLights = false;

    //set everything to zero
    for(size_t i = 0; i < lightVals.size(); i++){
        lightVals[i] = 0;
    }

    //send the zero-filled buffer to KiNet
    kinet.update(lightVals);
    kinet.send();


}

//------------------------------------------------------
void ofApp::turnOnLights(){

    //switch flag so we start updating with animation values
    bSendToLights = true;

}


//event listener from scheduled on/off events
//------------------------------------------------------
void ofApp::onSchedulerEvent(bool &onOff){
    if(onOff == true){
        turnOnLights();
        ofLog() << "TURN ON LIGHTS FROM SCHEDULE";
    } else if(onOff == false){
        turnOffLights();
        ofLog() << "TURN OFF LIGHTS FROM SCHEDULE";
    }
}


//event listener from admin-enabled on/off messages (from Node Server)
//------------------------------------------------------
void ofApp::onOscOnOff(bool &onOff){
    if(onOff == true){
        turnOnLights();
    } else if(onOff == false){
        turnOffLights();
    }
}



void ofApp::exit(){

    // Set the logger back to the default to make sure any
    // remaining messages are logged correctly.
    ofLogToConsole();
    ofClear(0);

    //when exiting, turn all lights to zero and send last packet to KiNet
    turnOffLights();


}

// g key toggles the GUI
//------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == 'g'){
        bShowGui = !bShowGui;
    }
    else if(key == 'n'){
        testCurrentLight ++;
    }
    else if(key == 'b'){
        testCurrentLight --;
    }


}

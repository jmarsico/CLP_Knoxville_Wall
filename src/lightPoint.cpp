//
//  lightPoint.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/8/16.
//
//

#include "lightPoint.h"

void LightPoint::setup(ofVec2f _loc){
    numSamples = 1;
    index = 0;
    loc = _loc;
    
    uint8_t start;
    start = 0;
    samples.push_back(start);
    currentVal = 0;
}


void LightPoint::setAvgSamplingSize(int _numSamples){
    numSamples = _numSamples;
}



void LightPoint::setCurrentVal(int _val){
    index ++;
    if(index >= numSamples) index = 0;
    
    samples[index] = _val;
    
    currentVal = _val;
//    ofLog() << "set: " << currentVal;
    
}

uint8_t LightPoint::getAvgVal(){
    int total = 0;
    
    for(size_t i = 0; i < numSamples; i++){
        total += samples[i];
    }
    
    avgVal = (uint8_t)total/numSamples;
    
    return avgVal;
}


void LightPoint::draw(){
    
//    ofLog() << "draw: " << currentVal;
    ofFill();
    ofSetColor(currentVal);
    ofDrawCircle(loc, 2);
    
    ofNoFill();
    ofSetLineWidth(0.2);
    ofSetColor(200, 100);
    ofDrawCircle(loc, 2);
}


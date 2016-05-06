//
//  kinetManager.h
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/11/16.
//
//

#ifndef __CLP_Knoxville_Wall__kinetManager__
#define __CLP_Knoxville_Wall__kinetManager__

#include <stdio.h>
#include "ofMain.h"
#include "ofxKinet.h"
#include "ofxXmlSettings.h"


class KinetManager{
public:
    KinetManager(){}
    void setup(	int numLights);
    void update(const vector<uint8_t> &lightVals);
    void send();
    
    vector<string> ipAddresses;
    vector<ofxKinet> powerSupplies;
    ofxXmlSettings ipXml;
    
    
};

#endif /* defined(__CLP_Knoxville_Wall__kinetManager__) */

//
//  kinetManager.cpp
//  CLP_Knoxville_Wall
//
//  Created by Jakob Marsico on 4/11/16.
//
//

#include "kinetManager.h"

//---------------------------------------------------------
void KinetManager::setup(int numLights){
    
    ipXml.load("PDUaddresses.xml");
    int numPDUs = ceil((float)numLights/50.f);
    ofLogNotice("KinetManager::setup") << "number of PDUs: " << numPDUs;
    
    ipXml.pushTag("PDU");
    int psPort = 1;
    
    if(numPDUs <= ipXml.getNumTags("IP") * 2){
    
        for(size_t i = 0; i < numPDUs; i ++){
            
            ofLog() << "start: " << psPort;
            ofxKinet k1;
            k1.init(ipXml.getValue("IP", "0", (int)i/2), 6038, psPort);
            powerSupplies.push_back(k1);
            
            if(psPort == 1){
                psPort = 2;
            } else if(psPort == 2){
                psPort = 1;
            }
            
//            powerSupplies[i*2].getPsPort();
            
            ofLogNotice("KinetManager::setup") << "new powerSupply. IP: " << powerSupplies[i].getIP()
            << " psPort: " << powerSupplies[i].getPsPort();
            
           
        }
    } else {
        ofLogNotice("KinetManager::setup") << "Incorrect number of IP addresses in XML";
    }
}


//---------------------------------------------------------
void KinetManager::update(const vector<uint8_t> &lightVals){
    for(size_t i = 0; i < powerSupplies.size(); i++){
        
        int startIndex = i*50;

        for(size_t j = 0; j < 50; j++){
            powerSupplies[i].setValue(j, lightVals[j + startIndex]);
        }
    }
}

//---------------------------------------------------------
void KinetManager::send(){
    
    for(auto& ps : powerSupplies){
        ps.send();
    }
    
}



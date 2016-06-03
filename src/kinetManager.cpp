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
    
    if(numPDUs <= ipXml.getNumTags("IP")){
    
        for(size_t i = 0; i < numPDUs; i ++){
            
            ofLog() << "start: " << psPort;
            ofxKinet k1;
            powerSupplies.push_back(k1);
            string host = ipXml.getValue("IP", "0", i);
            ofLog() << "ip as listing in XML: " << host;
//            k1.init(host.c_str(), 6038, psPort);
            powerSupplies[i].init(host.c_str(), 6038, psPort);
//            powerSupplies.push_back(k1);
            
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



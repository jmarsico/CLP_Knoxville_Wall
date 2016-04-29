# CLP_Knoxville_Wall
Animation engine to drive light wall. Receives OSC messages from node.js server, which receives GET requests from end users.

to compile:
  - clone into of_v_9.3...../apps/myApps/
  - open xcode project

requirements:
- [openframeworks 9.3](http://openframeworks.cc/download/)
- addons (clone each addon into of_v_9.3...../addons/):
- [ofxFlowTools](https://github.com/moostrik/ofxFlowTools)
- [ofxHTTP](https://github.com/bakercp/ofxHTTP)
- [ofxIO](https://github.com/bakercp/ofxIO)
- [ofxJSON](https://github.com/jefftimesten/ofxJSON)
- [ofxJSONRPC](https://github.com/bakercp/ofxJSONRPC)
- [ofxMediaType](https://github.com/bakercp/ofxMediaType)
- [ofxSSLManager](https://github.com/bakercp/ofxSSLManager)
- [ofxTaskQueue](https://github.com/bakercp/ofxTaskQueue)
- [ofxFastFboReader](https://github.com/satoruhiga/ofxFastFboReader)
- ofxKinet (proprietary, ask Jake)
- [ofxSimpleTimer](https://github.com/sfjmt/ofxSimpleTimer)
- [ofxNetworkUtils](https://github.com/bakercp/ofxNetworkUtils)


API development:
- "explode"
    - creates an explosion of "particles"
    - location x
    - location y
    - size
- "sweep"
    - draws a mass of light from one point to another
    - startLocation x
    - startLocation y
    - endLocation x
    - endLocation y
    - size
- "force"
    - changes the direction of wind and gravity in the generative scene
    - wind (x force)
    - gravity (y force)
- "all"
    - (advanced) RESTful way of controlling exact brightness of all pixels
    - 750 args 0-1

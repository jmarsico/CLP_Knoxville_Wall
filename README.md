# CLP_Knoxville_Wall
Animation engine to drive light wall. Receives OSC messages from node.js server, which receives GET requests from end users.

to compile:
  - clone into of_v_9.3...../apps/myApps/
  - open xcode project

requirements:
- [openframeworks 9.3](http://openframeworks.cc/download/)
- addons (clone each addon into of_v_9.3...../addons/):
- [ofxFlowTools](https://github.com/jmarsico/ofxFlowTools)
- [ofxFastFboReader](https://github.com/satoruhiga/ofxFastFboReader)
- ofxKinet (proprietary, ask Jake)
- [ofxSimpleTimer](https://github.com/jmarsico/ofxSimpleTimer.git)
- [ofxEasing](https://github.com/arturoc/ofxEasing.git)
- [ofxGoogleAnalytics](https://github.com/armadillu/ofxGoogleAnalytics.git)
- [ofxSimpleHttp](https://github.com/armadillu/ofxSimpleHttp)

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
    - speed
- "dots"
    - size
    - duration
<!-- - "force"
    - changes the direction of wind and gravity in the generative scene
    - wind (x force)
    - gravity (y force) -->
<!-- - "all"
    - (advanced) RESTful way of controlling exact brightness of all pixels
    - 750 args 0-1 -->

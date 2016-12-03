#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGiantImage.h"

#define __APP_VERSION__ "0.1.0"
#define __APP_DEFAULT_FILENAME "score.jpg"

#define __OSC_IP_INPUT "127.0.0.1"
#define __OSC_PORT_INPUT 4000
#define __OSC_PORT_OUTPUT 4001

#define __OSC_ADDR_CONNECT "/connected"
#define __OSC_ADDR_CLOCK_POS "/midi/clock/position"
#define __OSC_ADDR_CLOCK_START "/midi/clock/start"
#define __OSC_ADDR_CLOCK_STOP "/midi/clock/stop"
#define __OSC_ADDR_TIME "/time"
#define __OSC_ADDR_TEMPO "/tempo"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    ofxOscReceiver input;
    ofxOscSender output;

    ofxGiantImage score;

    float tempo;
    float time;
    float pixelsPerSecond;

    int time_beats;
    int time_sub_beats;

    bool connected;
    bool playing;

    bool showInfo;
    bool showMetrum;
    bool loaded;
};

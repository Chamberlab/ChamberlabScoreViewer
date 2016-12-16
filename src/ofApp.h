#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGiantImage.h"
#include "ofxXmlSettings.h"

#define __APP_VERSION__ "0.1.0"
#define __APP_DEFAULT_FILENAME "score.jpg"
#define __APP_DEFAULT_BPM 120
#define __APP_DEFAULT_PPS 100.0f

#define __APP_DEFAULT_SHOW_INFO true
#define __APP_DEFAULT_SHOW_METRUM true
#define __APP_DEFAULT_SHOW_MENU true

#define __OSC_IP_INPUT "127.0.0.1"
#define __OSC_PORT_INPUT 4000
#define __OSC_PORT_OUTPUT 4001

#define __OSC_ADDR_CONNECT "/connected"
#define __OSC_ADDR_CLOCK_POS "/midi/clock/position"
#define __OSC_ADDR_CLOCK_START "/midi/clock/start"
#define __OSC_ADDR_CLOCK_STOP "/midi/clock/stop"
#define __OSC_ADDR_TIME "/time"
#define __OSC_ADDR_TEMPO "/tempo"

typedef struct score_t {
    ofxGiantImage img;
    bool active = false;
    float pps = __APP_DEFAULT_PPS;
};

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void drawInfo();
    void drawMenu();
    void drawMetrum();

    void setClock(float seconds);

    void keyPressed(int key);
    void keyReleased(int key);

    void exit();

    ofxXmlSettings options;
    ofxXmlSettings keys;

    ofxOscReceiver input;
    ofxOscSender output;
    score_t scores[10];

    float tempo;
    float time;

    uint64_t clock_micros;
    uint64_t clock_micros_ref;

    int32_t time_beats;
    int32_t time_sub_beats;

    uint8_t scoreIndex;

    bool connected;
    bool playing;
};

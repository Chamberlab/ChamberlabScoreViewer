#pragma once

#include "csvDefaults.h"

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGiantImage.h"
#include "ofxXmlSettings.h"

typedef struct {
    ofxGiantImage img;
    bool active = false;
    float pps = __APP_DEFAULT_PPS;
} score_t;

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

    bool connected;
    bool playing;
};

#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGiantImage.h"

#define __CSV_VERSION__ "0.1.0"

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

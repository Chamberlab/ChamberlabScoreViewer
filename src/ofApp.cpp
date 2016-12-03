#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255, 255);
    connected = false;
    playing = false;
    showInfo = false;
    showMetrum = true;
    loaded = false;
    tempo = 120;
    pixelsPerSecond = 20.0;
    input.setup(4001);
    output.setup("127.0.0.1", 4000);
}

//--------------------------------------------------------------
void ofApp::update(){
    while (input.hasWaitingMessages()) {
        ofxOscMessage msg;
        input.getNextMessage(msg);
        connected = true;
        if (msg.getAddress() == "/connected") {
            connected = true;
        } else if (msg.getAddress() == "/midi/clock/position") {
            playing = true;
            time_beats = msg.getArgAsInt32(0);
            time_sub_beats = msg.getArgAsInt32(1);
        } else if (msg.getAddress() == "/midi/clock/start") {
            playing = true;
        } else if (msg.getAddress() == "/midi/clock/stop") {
            playing = false;
        } else if (msg.getAddress() == "/time") {
            time = msg.getArgAsFloat(0);
        } else if (msg.getAddress() == "/tempo") {
            tempo = msg.getArgAsFloat(0);
        } else {
            ofLogNotice() << "Unknown OSC command: " << msg.getAddress();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float minutes = time / tempo;

    if (loaded) {
        ofPushStyle();
        ofSetColor(255, 255, 255, 255);
        int buffer = 250;
        score.draw((int) roundf(pixelsPerSecond * minutes * 60.f),
                0, ofGetWidth(), score.height);
        ofSetColor(255, 0, 0);
        ofDrawRectangle(buffer, 0, 5, ofGetHeight());
        ofPopStyle();
    }

    if (showInfo) {
        ofPushStyle();
        ofSetColor(0, 0, 0, 128);
        ofFill();
        ofDrawRectangle(30, ofGetHeight() - 60, 420, 30);
        ofPopStyle();
        ofSetColor(255, 255, 255, 255);
        ofDrawBitmapString("BPM " + ofToString(tempo, 2, 5, '0'), 40, ofGetHeight() - 40);
        ofDrawBitmapString("SIG 4 / 4", 160, ofGetHeight() - 40);
        ofDrawBitmapString("PPS " + ofToString(pixelsPerSecond, 0), 280, ofGetHeight() - 40);
        ofDrawBitmapString(__CSV_VERSION__, 400, ofGetHeight() - 40);

        ofPushStyle();
        ofSetColor(0, 0, 0, 128);
        ofFill();
        ofDrawRectangle(ofGetWidth() - 300, ofGetHeight() - 60, 80, 30);
        ofPopStyle();

        ofDrawBitmapString(ofToString(floorf(minutes), 0, 2, '0') + ":" +
                ofToString((minutes - floorf(minutes)) * 60.f, 0, 2, '0'), ofGetWidth() - 290, ofGetHeight() - 40);
    }

    if (playing && showMetrum) {
        ofPushStyle();
        ofSetColor(0, 0, 0, 128);
        ofFill();
        ofDrawRectangle(ofGetWidth() - 210, ofGetHeight() - 70, 170, 40);
        ofPopStyle();
        ofPushStyle();
        ofFill();
        ofSetColor(255, 255 - (int)((time_beats / 4.0f) * 255.0f));
        ofDrawRectangle(ofGetWidth() - 200, ofGetHeight() - 60, 20, 20);
        ofDrawRectangle(ofGetWidth() - 200 + 30 + 30 * time_beats, ofGetHeight() - 60, 20, 5);
        ofSetColor(255, 255 - (int)((time_sub_beats / 4.0f) * 255.0f));
        ofDrawRectangle(ofGetWidth() - 200 + 30 + 20 * time_sub_beats, ofGetHeight() - 45, 10, 5);
        ofPopStyle();
    }

    if (!loaded) {
        ofPushStyle();
        ofSetColor(0, 0, 0, 128);
        ofFill();
        ofDrawRectangle(30, ofGetHeight() - 250, 240, 115);
        ofPopStyle();
        ofSetColor(255, 255, 255, 255);
        ofDrawBitmapString("L .... LOAD SCORE", 40, ofGetHeight() - 230);
        ofDrawBitmapString("F .... TOGGLE FULLSCREEN", 40, ofGetHeight() - 190);
        ofDrawBitmapString("I .... TOGGLE INFO", 40, ofGetHeight() - 170);
        ofDrawBitmapString("M .... TOGGLE METRUM", 40, ofGetHeight() - 150);
    }

    if (!connected) {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("DISCONNECTED", ofGetWidth() - 150, 40);
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'i':
            showInfo = !showInfo;
            break;
        case 'm':
            showMetrum = !showMetrum;
            break;
        case 'l':
            score.loadImage("score.jpg");
            loaded = true;
            break;
        case '+':
            pixelsPerSecond += 1;
            break;
        case '-':
            pixelsPerSecond -= 1;
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
        case ' ':
            break;
        default:
            break;
    }
}

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255, 255, 255, 255);

    connected = false;
    playing = false;
    loaded = false;

    showInfo = false;
    showMetrum = true;

    tempo = __APP_DEFAULT_BPM;
    pixelsPerSecond = __APP_DEFAULT_PPS;

    input.setup(__OSC_PORT_OUTPUT);
    output.setup(__OSC_IP_INPUT, __OSC_PORT_INPUT);
}

//--------------------------------------------------------------
void ofApp::update(){
    while (input.hasWaitingMessages()) {
        ofxOscMessage msg;
        input.getNextMessage(msg);

        uint64_t now_micros = ofGetElapsedTimeMicros();
        uint64_t diff_micros = now_micros - clock_micros_ref;
        clock_micros += diff_micros;
        clock_micros_ref = now_micros;

        if (msg.getAddress() == __OSC_ADDR_CONNECT) {
            connected = true;
        } else if (msg.getAddress() == __OSC_ADDR_CLOCK_POS) {
            playing = true;
            time_beats = msg.getArgAsInt32(0);
            time_sub_beats = msg.getArgAsInt32(1);
        } else if (msg.getAddress() == __OSC_ADDR_CLOCK_START) {
            playing = true;
        } else if (msg.getAddress() == __OSC_ADDR_CLOCK_STOP) {
            playing = false;
        } else if (msg.getAddress() == __OSC_ADDR_TIME) {
            time = msg.getArgAsFloat(0);
            if (time * 1000000.f > clock_micros) {
                clock_micros = (uint64_t) (time * 1000000.f);
                clock_micros_ref = ofGetElapsedTimeMicros();
            }
        } else if (msg.getAddress() == __OSC_ADDR_TEMPO) {
            tempo = msg.getArgAsFloat(0);
        } else {
            connected = false;
            ofLogNotice() << "Unknown OSC command: " << msg.getAddress();
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    float minutes = (clock_micros * 0.000001f) / tempo;

    if (loaded) {
        ofPushStyle();

        ofSetColor(255, 255, 255, 255);
        uint32_t buffer = (uint32_t)roundf(ofGetWidth() * 0.3f);
        score.draw((uint32_t) roundf(pixelsPerSecond * minutes * 60.f), 0, ofGetWidth(), score.height);

        ofSetColor(255, 0, 0);
        ofDrawRectangle(buffer, 0, 5, ofGetHeight());
        ofPopStyle();
    }

    if (showInfo) {
        ofPushStyle();

        ofFill();
        ofSetColor(0, 0, 0, 128);
        ofDrawRectangle(30, ofGetHeight() - 60, 420, 30);

        ofSetColor(255, 255, 255, 255);
        ofDrawBitmapString("BPM " + ofToString(tempo, 2, 5, '0'), 40, ofGetHeight() - 40);
        ofDrawBitmapString("SIG 4 / 4", 160, ofGetHeight() - 40);
        ofDrawBitmapString("PPS " + ofToString(pixelsPerSecond, 0), 280, ofGetHeight() - 40);
        ofDrawBitmapString(__APP_VERSION__, 400, ofGetHeight() - 40);

        ofSetColor(0, 0, 0, 128);
        ofDrawRectangle(ofGetWidth() - 300, ofGetHeight() - 60, 80, 30);

        ofSetColor(255, 255, 255, 255);
        ofDrawBitmapString(ofToString(floorf(minutes), 0, 2, '0') + ":" +
                ofToString((minutes - floorf(minutes)) * 60.f, 0, 2, '0'), ofGetWidth() - 290, ofGetHeight() - 40);

        ofPopStyle();
    }

    if (playing && showMetrum) {
        ofPushStyle();

        ofFill();
        ofSetColor(0, 0, 0, 128);
        ofDrawRectangle(ofGetWidth() - 210, ofGetHeight() - 70, 170, 40);

        ofSetColor(255, 255 - (uint8_t)((time_beats / 4.0f) * 255.0f));
        ofDrawRectangle(ofGetWidth() - 200, ofGetHeight() - 60, 20, 20);
        ofDrawRectangle(ofGetWidth() - 200 + 30 + 30 * time_beats, ofGetHeight() - 60, 20, 5);

        ofSetColor(255, 255 - (uint8_t)((time_sub_beats / 4.0f) * 255.0f));
        ofDrawRectangle(ofGetWidth() - 200 + 30 + 20 * time_sub_beats, ofGetHeight() - 45, 10, 5);

        ofPopStyle();
    }

    if (!loaded) {
        ofPushStyle();

        ofFill();
        ofSetColor(0, 0, 0, 128);
        ofDrawRectangle(30, ofGetHeight() - 250, 240, 115);

        ofSetColor(255, 255, 255, 255);
        ofDrawBitmapString("L .... LOAD SCORE", 40, ofGetHeight() - 230);
        ofDrawBitmapString("F .... TOGGLE FULLSCREEN", 40, ofGetHeight() - 190);
        ofDrawBitmapString("I .... TOGGLE INFO", 40, ofGetHeight() - 170);
        ofDrawBitmapString("M .... TOGGLE METRUM", 40, ofGetHeight() - 150);

        ofPopStyle();
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
            score.loadImage(__APP_DEFAULT_FILENAME);
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
            /* play */
            break;
        default:
            break;
    }
}

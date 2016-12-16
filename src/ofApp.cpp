#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
    ofBackground(0, 0, 0, 255);
    ofShowCursor();

    options.load("options.xml");
    keys.load("keys.xml");

    connected = false;
    playing = false;

    char key[6];
    for (uint8_t i = 0; i < 10; i += 1) {
        sprintf(key, "key-%u", i);
        string key_pps = ofToString(key) + "-pps";
        if (i == 0 && (!keys.tagExists(key) || !keys.tagExists(key_pps))) {
            keys.setValue(key, __APP_DEFAULT_FILENAME);
            keys.setValue(key_pps, __APP_DEFAULT_PPS);
        }
        if (keys.tagExists(key) && keys.tagExists(key_pps)) {
            scores[i].img.loadImage(keys.getValue(key, __APP_DEFAULT_FILENAME));
            scores[i].pps = (float) keys.getValue(key_pps, __APP_DEFAULT_PPS);
            scores[i].active = true;
        }
    }

    tempo = __APP_DEFAULT_BPM;

    input.setup(options.getValue("osc-output-port", __OSC_PORT_OUTPUT));
    output.setup(
        options.getValue("osc-input-ip", __OSC_IP_INPUT),
        options.getValue("osc-input-port", __OSC_PORT_INPUT)
    );
}

//--------------------------------------------------------------
void ofApp::update() {
    if (playing) {
        uint64_t now_micros = ofGetElapsedTimeMicros();
        uint64_t diff_micros = now_micros - clock_micros_ref;
        clock_micros += diff_micros;
        clock_micros_ref = now_micros;
    }

    while (input.hasWaitingMessages()) {
        ofxOscMessage msg;
        input.getNextMessage(msg);

        if (msg.getAddress() == __OSC_ADDR_CONNECT) {
            connected = true;
        } else if (msg.getAddress() == __OSC_ADDR_CLOCK_POS) {
            ofHideCursor();
            playing = true;
            time_beats = msg.getArgAsInt32(0);
            time_sub_beats = msg.getArgAsInt32(1);
        } else if (msg.getAddress() == __OSC_ADDR_CLOCK_START) {
            playing = true;
        } else if (msg.getAddress() == __OSC_ADDR_CLOCK_STOP) {
            ofShowCursor();
            playing = false;
        } else if (msg.getAddress() == __OSC_ADDR_TIME) {
            float remote_secs = msg.getArgAsFloat(0);
            if (clock_micros - remote_secs * 1000000.f > 1000000.f) {
                setClock(remote_secs);
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
void ofApp::draw() {
    float minutes = (clock_micros * 0.000001f) / tempo;

    if (scores[options.getValue("score-index", 0)].active) {
        ofPushStyle();

        ofSetColor(255, 255, 255, 255);
        uint32_t buffer = (uint32_t)roundf(ofGetWidth() * 0.3f);
        ofPushMatrix();
        ofTranslate(buffer, 0.0);
        scores[scoreIndex].img.draw(
            (uint32_t) roundf(scores[scoreIndex].pps * minutes * 60.f), 0,
            ofGetWidth() - buffer, scores[scoreIndex].img.height
        );
        ofPopMatrix();

        ofSetColor(255, 0, 0);
        ofDrawRectangle(buffer, 0, 5, ofGetHeight());
        ofPopStyle();
    }

    if (options.getValue("show-info", __APP_DEFAULT_SHOW_INFO)) drawInfo();
    if (playing && connected && options.getValue("show-metrum", __APP_DEFAULT_SHOW_METRUM)) drawMetrum();
    if (options.getValue("show-menu", __APP_DEFAULT_SHOW_MENU)) drawMenu();
}

void ofApp::drawInfo() {
    float minutes = (clock_micros * 0.000001f) / tempo;

    ofPushStyle();

    ofFill();
    ofSetColor(0, 0, 0, 128);
    ofDrawRectangle(30, ofGetHeight() - 60, 680, 30);

    ofSetColor(255, 255, 255, 255);
    ofDrawBitmapString("BPM " + ofToString(tempo, 2, 5, '0'), 40, ofGetHeight() - 40);
    ofDrawBitmapString("SIG 4 / 4", 160, ofGetHeight() - 40);
    ofDrawBitmapString("PPS " + ofToString(scores[scoreIndex].pps, 2), 280, ofGetHeight() - 40);
    ofDrawBitmapString("FPS " + ofToString(ofGetFrameRate(), 2), 400, ofGetHeight() - 40);
    ofDrawBitmapString("SCORE #" + ofToString(options.getValue("score-index", 0)), 520, ofGetHeight() - 40);
    ofDrawBitmapString(__APP_VERSION__, 640, ofGetHeight() - 40);

    ofSetColor(0, 0, 0, 128);
    ofDrawRectangle(ofGetWidth() - 300, ofGetHeight() - 60, 80, 30);

    ofSetColor(255, 255, 255, 255);
    ofDrawBitmapString(ofToString(floorf(minutes), 0, 2, '0') + ":" +
            ofToString((minutes - floorf(minutes)) * 60.f, 0, 2, '0'), ofGetWidth() - 290, ofGetHeight() - 40);

    ofPopStyle();

    if (!connected) {
        ofPushStyle();
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("DISCONNECTED", ofGetWidth() - 150, 40);
        ofPopStyle();
    }
}

void ofApp::drawMenu() {
    ofPushStyle();

    ofFill();
    ofSetColor(0, 0, 0, 128);
    ofDrawRectangle(30, ofGetHeight() - 310, 300, 170);

    ofSetColor(255, 255, 255, 255);
    ofDrawBitmapString("0 - 9 .. SELECT SCORE FROM XML", 40, ofGetHeight() - 290);
    ofDrawBitmapString("SPACE .. MANUAL PLAY & PAUSE", 40, ofGetHeight() - 270);
    ofDrawBitmapString("R ...... MANUAL REWIND", 40, ofGetHeight() - 250);
    ofDrawBitmapString("F ...... TOGGLE FULLSCREEN", 40, ofGetHeight() - 210);
    ofDrawBitmapString("I ...... TOGGLE INFO", 40, ofGetHeight() - 190);
    ofDrawBitmapString("M ...... TOGGLE METRUM", 40, ofGetHeight() - 170);
    ofDrawBitmapString("K ...... TOGGLE THIS MENU", 40, ofGetHeight() - 150);

    ofPopStyle();
}

void ofApp::drawMetrum() {
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

void ofApp::setClock(float seconds) {
    time = seconds;
    clock_micros = (uint64_t) (time * 1000000.f);
    clock_micros_ref = ofGetElapsedTimeMicros();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            break;
        case 'i':
            options.setValue("show-info", !options.getValue("show-info", __APP_DEFAULT_SHOW_INFO));
            break;
        case 'm':
            options.setValue("show-metrum", !options.getValue("show-metrum", __APP_DEFAULT_SHOW_METRUM));
            break;
        case 'k':
            options.setValue("show-menu", !options.getValue("show-menu", __APP_DEFAULT_SHOW_MENU));
            break;
        case 'r':
            setClock(0.0);
            break;
        default:
            char keystr[6];
            sprintf(keystr, "key-%c", (char) key);
            if (keys.tagExists(keystr)) {
                options.setValue("score-index", (uint8_t) ofToInt(ofToString((char) key)));
            }
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    switch (key) {
        case ' ':
            playing = !playing;
            if (playing) {
                ofHideCursor();
                setClock(time);
            } else {
                ofShowCursor();
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    ofShowCursor();
    keys.save("keys.xml");
    options.save("options.xml");
}
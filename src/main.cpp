#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
#ifdef __linux_
    ofSetupOpenGL(1920,1080, OF_GAME_MODE);
    /*
    ofWindowSettings wsettings;
    wsettings.width = 1920;
    wsettings.height = 1080;
	ofGLFWWindowSettings settings(wsettings);
	settings.multiMonitorFullScreen = true;
	settings.windowMode = OF_GAME_MODE;
	auto window = ofCreateWindow(settings);

	ofRunApp(window, std::make_shared<ofApp>());
	ofRunMainLoop();
     */
#else
	ofSetupOpenGL(1280,720,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());
#endif
}

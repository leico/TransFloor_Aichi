#include "ofMain.h"
#include "MainScreen.h"

//========================================================================
int main( ){

//    
//    ofSetupOpenGL(1280,1440, OF_FULLSCREEN);			// <-------- setup the GL context
//    
//    // this kicks off the running of my app
//    // can be OF_WINDOW or OF_FULLSCREEN
//    // pass in width and height too:
//    ofRunApp( new MainScreen());
    
  ofGLFWWindowSettings settings;
  
  settings.width  = 300;
  settings.height = 300;
  settings.setPosition( ofVec2f(20, 20) );
  settings.resizable = true;
  settings.multiMonitorFullScreen = true;

  ofAppGLFWWindow window;
  
  window.setup(settings);
  
  ofSetupOpenGL(&window, 300, 300, OF_WINDOW);
  ofRunApp(new MainScreen);

}

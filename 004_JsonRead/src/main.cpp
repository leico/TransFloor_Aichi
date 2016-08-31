#include "ofMain.h"
#include "MainScreen.h"

//========================================================================
int main( ){

  ofGLFWWindowSettings settings;
  
  settings.width  = 300;
  settings.height = 300;
  settings.setPosition( ofVec2f(20, 20) );
  settings.resizable = true;
  settings.multiMonitorFullScreen = true;

  shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
  shared_ptr<MainScreen> mainApp(new MainScreen);
  
  ofRunApp(window, mainApp);

  ofRunMainLoop();


}

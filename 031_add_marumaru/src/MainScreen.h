#pragma once

#include "TransFloor.h"

class MainScreen : public ofBaseApp{

  ofxOscReceiver receiver;

  const static std :: string jsonfile;
  const static std :: string serialfile;

  const static std :: string kinect1_prefix;
               KinectCV      kinect1;
  const static std :: string kinect2_prefix;
               KinectCV      kinect2;

  ofxSimpleTimer<bool> nohuman;
  void WhiteOut(bool& id);

  ofxSimpleTimer<bool> whiteout;
  void SceneChange(bool& id);

  
  ofxCvGrayscaleImage binaryImage;
  ofxCvContourFinder  contourfinder;

  
        bool b_debug;
  const bool Debug(void);
        void Debug(const bool debug);


  const static int SCENE_NUM = 14;
  int  scene;
  Base *basedraw;
  void DisplaySetup(void);
  
  ofStyle style;

  public:
  void setup();
  void exit();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void mouseMoved(int x, int y);
  void mouseDragged(int x, int y, int button);
  void mousePressed(int x, int y, int button);
  void mouseReleased(int x, int y, int button);
  void windowResized(int w, int h);
  void dragEvent(ofDragInfo dragInfo);
  void gotMessage(ofMessage msg);


};


inline const bool MainScreen :: Debug(void)            { return b_debug;  }
inline       void MainScreen :: Debug(const bool debug){ b_debug = debug; }

inline void MainScreen :: DisplaySetup(void){

  ofSetFrameRate(60);
  ofSetVerticalSync(true);

  ofBackground(0);

  ofSetBackgroundAuto(true);

  ofFill();
  ofSetLineWidth(1);
  ofEnableBlendMode(OF_BLENDMODE_ALPHA);

  ofSetCircleResolution(32);
}


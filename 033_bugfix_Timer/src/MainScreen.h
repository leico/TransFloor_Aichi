#pragma once

#include "TransFloor.h"

class MainScreen : public ofBaseApp{

  static int width;
  static int height;

  ofxOscReceiver receiver;

  const static std :: string jsonfile;
  const static std :: string serialfile;

  const static std :: string kinect1_prefix;
               KinectCV      kinect1;
  const static std :: string kinect2_prefix;
               KinectCV      kinect2;

  ofxSimpleTimer<bool> nohuman;
  void WhiteOut(bool& id);
  const static int NOHUMAN_TIME = 10000;

  ofxSimpleTimer<bool> whiteout;
  void End_WhiteOut(bool& id);
  const static int WHITEOUT_TIME = 5000;

  ofxSimpleTimer<bool> forcechange;
  ofTrueTypeFont font;
  const static int FORCECHAGE_TIME = 600000;

  
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


  void setup_KinectCV(void);
  void setup_Timer   (void);

  const vector<ofxOscMessage> update_KinectCV(void);

  void SceneChange(const int scene);


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

  int ofGetWidth (void);
  int ofGetHeight(void);

};


inline const bool MainScreen :: Debug(void)            { return b_debug;  }
inline       void MainScreen :: Debug(const bool debug){ b_debug = debug; }

inline int MainScreen :: ofGetWidth (void){ return width;  }
inline int MainScreen :: ofGetHeight(void){ return height; }

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


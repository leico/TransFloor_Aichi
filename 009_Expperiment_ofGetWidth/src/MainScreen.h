#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxJSON.h"
#include "KinectCV.h"
#include "Base.h"
#include "tkm001.h"
#include "Blank.h"
#include "RippleScene.h"
#include "Relation.h"
#include "Gravity.h"

class MainScreen : public ofBaseApp{

  ofxOscReceiver receiver;

  const static std :: string kinect1_prefix;
               KinectCV      kinect1;
  const static std :: string kinect2_prefix;
               KinectCV      kinect2;

  bool b_debug;

  const static std :: string jsonfile;

  const bool Debug(void);
        void Debug(const bool debug);

  void DisplaySetup(void);

  Base *basedraw;

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

}


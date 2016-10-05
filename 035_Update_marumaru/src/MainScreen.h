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
  const static int FORCECHANGE_TIME = 600000;

  
  ofxCvGrayscaleImage binaryImage;
  ofxCvContourFinder  contourfinder;

  
        bool b_debug;
  const bool Debug(void);
        void Debug(const bool debug);


  const static int SCENE_NUM = 15;
  int  scene;
  Base *basedraw;
  void DisplaySetup(void);
  
  ofStyle style;


  void setup_KinectCV(void);
  void setup_Timer   (void);

  void update_KinectCV(vector<ofxOscMessage>& humans);

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

/* =================================================================== *
 * void WhiteOut(bool& id)                                             *
 * =================================================================== */
inline void MainScreen :: WhiteOut(bool& id){
  
  nohuman    .Stop();
  forcechange.Stop();
  
  delete basedraw;
  basedraw = new class WhiteOut();
  
  DisplaySetup();
  basedraw -> setup();
  
  style = ofGetStyle();
  
  whiteout.Start(WHITEOUT_TIME, 1);
}

/* =================================================================== *
 * void End_WhiteOut(bool& id)                                         *
 * =================================================================== */
inline void MainScreen :: End_WhiteOut(bool& id){
  
  scene = (scene + 1) % SCENE_NUM;
  
  SceneChange( scene + 1 );
  return;
  
}


/* =================================================================== *
 * void setup_KinectCV(void)                                           *
 * =================================================================== */
inline void MainScreen :: setup_KinectCV(void){
  
  ofxKinect :: listDevices();
  {
    ofxJSON json;
    if( ( json.open(serialfile) ) && ( ! json.isNull() ) ){
      kinect1.setup( json[0].asString() );
      kinect2.setup( json[1].asString() );
    }
    else{
      ofLogWarning() << "json.open: Can't open serial.json file, use default serial" << std :: endl;
      kinect1.setup("A00364800479053A");
      kinect2.setup("A00363A02391053A");
    }
    if( json.open(jsonfile) ){
      ofLogVerbose() << json.getRawString() << endl;
      
      kinect1.SettingData( json );
      kinect2.SettingData( json );
    }
    else{
      ofLogWarning() << "json.open: Can't open serial.json file, use default settings" << std :: endl;
    }
    json.clear();
  }
  
  return;
  
}
/* =================================================================== *
 * void update_KinectCV(vector<ofxOscMessage>& humans)                 *
 * =================================================================== */
inline void MainScreen :: update_KinectCV(vector<ofxOscMessage>& humans){
  
  
  
  ofPixels& binary = binaryImage.getPixels();
  int      size   = kinect1.Size().x * kinect1.Size().y;
  
  {
    const ofxCvGrayscaleImage& image = kinect1.update_dualscreen();
    const ofPixels&            pix   = image.getPixels();
    for(int i = 0 ; i < size ; ++ i)
      binary[i] = pix[i];
  }
  {
    const ofxCvGrayscaleImage& image = kinect2.update_dualscreen();
    const ofPixels&            pix   = image.getPixels();
    
    for(int i = 0 ; i < size ; ++ i)
      binary[size + i] = pix[i];
  }
  
  contourfinder.findContours(binaryImage, kinect1.MinArea(), kinect1.MaxArea(), 200, false);
  
  for(int i = 0, size = contourfinder.blobs.size() ; i < size ; ++ i){
    
    //get contour center position
    ofPoint pos = contourfinder.blobs.at(i).centroid;
    
    //create OSC Message
    ofxOscMessage m;
    m.setAddress("/human");
    m.addIntArg(pos.x);
    m.addIntArg(pos.y);
    m.addIntArg( (pos.y > kinect1.Size().y)  ?
                kinect2.Depth(pos.x, pos.y - kinect1.Size().y) :
                kinect1.Depth(pos.x, pos.y)  );
    
    //store for humans
    humans.push_back(m);
    
    //ofLogWarning() << "nBlobs:" << humans.size();
  }
}

/* =================================================================== *
 * void setup_Timer(void)                                              *
 * =================================================================== */
inline void MainScreen :: setup_Timer(void){
  nohuman    .Setup(true, this, &:: MainScreen :: WhiteOut);
  whiteout   .Setup(true, this, &:: MainScreen :: End_WhiteOut);
  forcechange.Setup(true, this, &:: MainScreen :: WhiteOut);
}

/* =================================================================== *
 * void SceneChage(const int scene)                                    *
 * =================================================================== */
inline void MainScreen :: SceneChange(const int scene){
  
  switch( scene ){
    case  0  : delete basedraw; basedraw = new Blank();       break; //Blank
    case  1  : delete basedraw; basedraw = new tkm001();      break; //track circles
    case  2  : delete basedraw; basedraw = new RippleScene(); break; //Ripples
    case  3  : delete basedraw; basedraw = new Relation();    break; //Relation
    case  4  : delete basedraw; basedraw = new Gravity();     break; //Gravity
    case  5  : delete basedraw; basedraw = new takami();      break; //EscapeParticles
    case  6  : delete basedraw; basedraw = new Gushi01();     break; //prrrrrrrroooo
    case  7  : delete basedraw; basedraw = new tkmOTO();      break; //tkmOTO
    case  8  : delete basedraw; basedraw = new origami();     break; //origami
    case  9  : delete basedraw; basedraw = new lines();       break; //lines
    case 10  : delete basedraw; basedraw = new dot();         break; //tkmOTO
    case 11  : delete basedraw; basedraw = new nununu();      break; //origami
    case 12  : delete basedraw; basedraw = new star();        break; //lines
    case 13  : delete basedraw; basedraw = new Medama();      break; //medama
    case 14  : delete basedraw; basedraw = new marumaru();    break; //marumaru
    case 15  : delete basedraw; basedraw = new sinsin();    break; //marumaru
    default  : return;
  }
  
  DisplaySetup();
  basedraw -> setup();
  
  style = ofGetStyle();
  
  forcechange.Start(FORCECHANGE_TIME, 1);
  
  return;
}

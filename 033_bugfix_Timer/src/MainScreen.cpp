#include "MainScreen.h"

const std :: string MainScreen :: kinect1_prefix("/01");
const std :: string MainScreen :: kinect2_prefix("/02");
const std :: string MainScreen :: jsonfile("settings.json");
const std :: string MainScreen :: serialfile("serial.json");

int MainScreen :: width;
int MainScreen :: height;

//--------------------------------------------------------------
void MainScreen::setup(){
  
  ofSetDataPathRoot("../../../data/");
    
  ofSetLogLevel(OF_LOG_VERBOSE);

  setup_KinectCV();
  setup_Timer();

  width  = ::ofGetWidth ();
  height = ::ofGetHeight();

  binaryImage.allocate( ofGetWidth(), ofGetHeight());

  receiver.setup(12345);

  Debug(false);

  DisplaySetup();

  scene = -1;
  basedraw = new Blank();
  basedraw -> setup();

  basedraw -> resize( ofGetWidth(), ofGetHeight() );
  
  style = ofGetStyle();
 
  if( font.load("font/verdana.ttf", 100) != true){
    ofLogWarning() << "can't load font" << endl;
  }
  forcechange.Start(FORCECHANGE_TIME, 1);
  keyPressed('f');
}

//--------------------------------------------------------------
void MainScreen :: exit(){

  ofxJSON k1( kinect1.SettingData() );
  ofxJSON k2( kinect2.SettingData() );

  ofxJSON :: Merge(k1, k2);

  if( ! k1.save(jsonfile) ){
    ofLogWarning() << "json.save: Can't open file, unsaved settings" << std :: endl;
  }

  nohuman.Clear(this, &:: MainScreen :: End_WhiteOut);

  kinect1.exit();
  kinect2.exit();

  delete basedraw;
}

//--------------------------------------------------------------
void MainScreen::update(){


  vector<ofxOscMessage> humans;
  
  if(ofGetWindowMode() == OF_FULLSCREEN) update_KinectCV(humans);
 
  while(receiver.hasWaitingMessages()){
    ofxOscMessage m;
    receiver.getNextMessage(m);

    //message is Debug
    if(m.getAddress() == "/debug"){

      Debug(m.getArgAsInt32(0) == 1);

      //Display Setting initialize
      DisplaySetup();
      if( ! Debug() ) basedraw -> setup();
      
      style = ofGetStyle();

      m.clear();
      continue;
    }

    //message is DisplayChagne
    if(m.getAddress() == "/scene"){
      
      SceneChange( m.getArgAsInt32(0) );
      continue;
    }

    if(m.getAddress().find( kinect1_prefix ) == 0){
      m.setAddress( m.getAddress().substr(kinect1_prefix.size()) );
      kinect1.osc(m);
      continue;
    }

    if(m.getAddress().find( kinect2_prefix ) == 0){
      m.setAddress( m.getAddress().substr(kinect2_prefix.size()) );
      kinect2.osc(m);
      continue;
    }

  }
  
  basedraw -> osc( humans );
  basedraw -> update();

  if     (whiteout.Status() == ofxSimpleTimer<bool> :: STATUS :: RUN) nohuman.Stop();
  else if(humans  .size  () != 0)                                     nohuman.Stop();
  else if(nohuman .Status() == ofxSimpleTimer<bool> :: STATUS :: RUN);
  else                                                                nohuman.Start(NOHUMAN_TIME, 1);

  nohuman    .Update();
  whiteout   .Update();
}

//--------------------------------------------------------------
void MainScreen::draw(){
  
  ofSetStyle(style);

  if( Debug() ){
    kinect1.draw();
    kinect2.draw(0, kinect1.Size().y);
    return;
  }

  basedraw -> draw();


  if(forcechange.Status() != ofxSimpleTimer<bool> :: STATUS :: STOP){
    float time = forcechange.Update();
    if(time >= FORCECHANGE_TIME - 10000){
      ofColor clr = ofGetBackgroundColor();
      clr.r = 255 - clr.r;
      clr.g = 255 - clr.g;
      clr.b = 255 - clr.b;

      stringstream ss;
      ss << int( (FORCECHANGE_TIME - time) / 1000);
      int width  = font.stringWidth ( ss.str() ) / 2;
      int height = font.stringHeight( ss.str() ) / 2;
      ofSetColor(clr);
      font.drawString(ss.str(), ofGetWidth() / 2 - width, ofGetHeight() / 2 - height);
    }
  }


}

//--------------------------------------------------------------
void MainScreen::keyPressed(int key){

  if(key == 'f'){
    ofToggleFullscreen();
    
    if(ofGetWindowMode() == OF_FULLSCREEN) ofHideCursor();
    else                                   ofShowCursor();
  }
}

//--------------------------------------------------------------
void MainScreen::keyReleased(int key){

}

//--------------------------------------------------------------
void MainScreen::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void MainScreen::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void MainScreen::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void MainScreen::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void MainScreen::windowResized(int w, int h){

  if(basedraw)
    basedraw -> resize(w, h);

  binaryImage  .resize(w, h);

  width  = w;
  height = h;


}

//--------------------------------------------------------------
void MainScreen::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void MainScreen::dragEvent(ofDragInfo dragInfo){ 

}


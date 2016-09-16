#include "MainScreen.h"

const std :: string MainScreen :: kinect1_prefix("/01");
const std :: string MainScreen :: kinect2_prefix("/02");
const std :: string MainScreen :: jsonfile("settings.json");
const std :: string MainScreen :: serialfile("serial.json");

//--------------------------------------------------------------
void MainScreen::setup(){
    
  ofSetLogLevel(OF_LOG_VERBOSE);

  setup_KinectCV();
  setup_Timer();

  binaryImage.allocate(ofGetWidth(), ofGetHeight());

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
  forcechange.Start(FORCECHAGE_TIME, 1);
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
  
  if(ofGetWindowMode() == OF_FULLSCREEN) humans = update_KinectCV();
 
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
  else if(nohuman .Status() == ofxSimpleTimer<bool> :: STATUS :: RUN);
  else if(humans  .size()   == 0)                                     nohuman.Start(NOHUMAN_TIME, 1);

  nohuman    .Update();
  whiteout   .Update();
  forcechange.Update();
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


  float time = forcechange.CurrentTime();
  if(time <= FORCECHAGE_TIME - 10000){
    ofColor clr = ofGetBackgroundColor();
    clr.r = 255 - clr.r;
    clr.g = 255 - clr.g;
    clr.b = 255 - clr.b;
    
    stringstream ss;
    ss << int(time / 1000);
    int width  = font.stringWidth ( ss.str() ) / 2;
    int height = font.stringHeight( ss.str() ) / 2;
    ofSetColor(clr);
    font.drawString(ss.str(), ofGetWidth() / 2 - width, ofGetHeight() / 2 - height);
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


}

//--------------------------------------------------------------
void MainScreen::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void MainScreen::dragEvent(ofDragInfo dragInfo){ 

}

/* =================================================================== *
 * void WhiteOut(bool& id)                                             *
 * =================================================================== */
void MainScreen :: WhiteOut(bool& id){
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
void MainScreen :: End_WhiteOut(bool& id){

  scene = (scene + 1) % SCENE_NUM;
  
  SceneChange( scene + 1 );
  return;

}


/* =================================================================== *
 * void setup_KinectCV(void)                                           *
 * =================================================================== */
void MainScreen :: setup_KinectCV(void){

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
 * const vector<ofxOscMessage> update_KinectCV(void)                   *
 * =================================================================== */
const vector<ofxOscMessage> MainScreen :: update_KinectCV(void){



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

  vector<ofxOscMessage> humans;
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

  return humans;
}

/* =================================================================== *
 * void setup_Timer(void)                                              *
 * =================================================================== */
void MainScreen :: setup_Timer(void){
  nohuman    .Setup(true, this, &:: MainScreen :: WhiteOut);
  whiteout   .Setup(true, this, &:: MainScreen :: End_WhiteOut);
  forcechange.Setup(true, this, &:: MainScreen :: WhiteOut);
}

/* =================================================================== *
 * void SceneChage(const int scene)                                    *
 * =================================================================== */
void MainScreen :: SceneChange(const int scene){
  
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
        default  : return;
      }

      DisplaySetup();
      basedraw -> setup();
      
      style = ofGetStyle();

      return;
}

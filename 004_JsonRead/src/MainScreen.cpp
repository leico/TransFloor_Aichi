#include "MainScreen.h"

const std :: string MainScreen :: prefix("/first");
const std :: string MainScreen :: jsonfile("settings.json");


//--------------------------------------------------------------
void MainScreen::setup(){
    
  ofSetLogLevel(OF_LOG_VERBOSE);

  ofxKinect :: listDevices();
  kinectcv.setup("A00364800479053A");

  ofxJSON json;
  if( json.open(jsonfile) ){
    ofLogVerbose() << "RawString:" << endl << json.getRawString() << endl;
    kinectcv.SettingData( json );
    ofLogVerbose() << "SettingData:" << endl << kinectcv.SettingData() << endl;
  }
  else{
    ofLogWarning() << "json.open: Can't open file, use default settings" << std :: endl;
  }


  receiver.setup(12345);

  Debug(true);

  DisplaySetup();

  basedraw = new Blank();
  basedraw -> setup();
}
//--------------------------------------------------------------
void MainScreen :: exit(){

  ofxJSON json( kinectcv.SettingData() );

  if( ! json.save(jsonfile) ){
    ofLogWarning() << "json.save: Can't open file, unsaved settings" << std :: endl;
  }

  kinectcv.exit();

  delete basedraw;
}

//--------------------------------------------------------------
void MainScreen::update(){

  kinectcv.update();
  
  while(receiver.hasWaitingMessages()){
    ofxOscMessage m;
    receiver.getNextMessage(m);

    //------------------message to me
    m.setAddress( m.getAddress().substr( prefix.size() ) );

   
    //message is Debug
    if(m.getAddress() == "/debug"){

      Debug(m.getArgAsInt32(0) == 1);

      //Display Setting initialize
      DisplaySetup();
      if( ! Debug() ) basedraw -> setup();

      m.clear();
      continue;
    }

    //message is DisplayChagne
    if(m.getAddress() == "/scene"){
      switch( m.getArgAsInt32(0) ){

        case 0  : delete basedraw; basedraw = new Blank ();      break; //Blank
        case 1  : delete basedraw; basedraw = new tkm001();      break; //track circles
        case 2  : delete basedraw; basedraw = new RippleScene(); break; //Ripples
        case 3  : delete basedraw; basedraw = new Relation();    break; //Relation
        case 4  : delete basedraw; basedraw = new Gravity();     break; //Gravity
        default : m.clear();       continue;                     break; //nomatch
      }

      DisplaySetup();
      basedraw -> setup();
    }
    
    kinectcv.osc(m);
  }

  
  vector <ofxOscMessage> humans = kinectcv.Humans();

  basedraw -> osc( humans );
  basedraw -> update();
}

//--------------------------------------------------------------
void MainScreen::draw(){

  if( Debug() ){
    kinectcv.draw();
    return;
  }

  basedraw -> draw();

}

//--------------------------------------------------------------
void MainScreen::keyPressed(int key){

  if(key == 'f') ofToggleFullscreen();

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

}

//--------------------------------------------------------------
void MainScreen::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void MainScreen::dragEvent(ofDragInfo dragInfo){ 

}

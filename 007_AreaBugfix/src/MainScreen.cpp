#include "MainScreen.h"

const std :: string MainScreen :: kinect1_prefix("/01");
const std :: string MainScreen :: kinect2_prefix("/02");
const std :: string MainScreen :: jsonfile("settings.json");


//--------------------------------------------------------------
void MainScreen::setup(){
    
  ofSetLogLevel(OF_LOG_VERBOSE);

  ofxKinect :: listDevices();
  kinect1.setup("A00364800479053A");
  kinect2.setup("A00363A02391053A");

  ofxJSON json;
  if( json.open(jsonfile) ){
    cout << json.getRawString() << endl;

    kinect1.SettingData( json );
    kinect2.SettingData( json );
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

  ofxJSON k1( kinect1.SettingData() );
  ofxJSON k2( kinect2.SettingData() );

  ofxJSON :: Merge(k1, k2);

  if( ! k1.save(jsonfile) ){
    ofLogWarning() << "json.save: Can't open file, unsaved settings" << std :: endl;
  }

  kinect1.exit();
  kinect2.exit();

  delete basedraw;
}

//--------------------------------------------------------------
void MainScreen::update(){

  kinect1.update();
  kinect2.update();
  
  while(receiver.hasWaitingMessages()){
    ofxOscMessage m;
    receiver.getNextMessage(m);

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

  const vector <ofxOscMessage>& k1 = kinect1.Humans();
  const vector <ofxOscMessage>& k2 = kinect2.Humans();
  
  vector <ofxOscMessage> humans(k1.size() + k2.size());
  humans = k1;
  humans.insert(humans.end(), k2.begin(), k2.end());

  basedraw -> osc( humans );
  basedraw -> update();
}

//--------------------------------------------------------------
void MainScreen::draw(){

  if( Debug() ){
    kinect1.draw();
    kinect2.draw(0, kinect1.Size().y);
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

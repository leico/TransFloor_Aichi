#include "MainScreen.h"

const std :: string MainScreen :: kinect1_prefix("/01");
const std :: string MainScreen :: kinect2_prefix("/02");
const std :: string MainScreen :: jsonfile("settings.json");

static int width;
static int height;

//--------------------------------------------------------------
void MainScreen::setup(){
  DisplaySetup();
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
  
  whiteout.Start(5000, 1);
}

/* =================================================================== *
 * void SceneChange(bool& id)                                          *
 * =================================================================== */
void MainScreen :: SceneChange(bool& id){

  scene = (scene + 1) % SCENE_NUM;

  switch( scene ){

    case 0  : delete basedraw; basedraw = new tkm001();      break; //track circles
    case 1  : delete basedraw; basedraw = new RippleScene(); break; //Ripples
    case 2  : delete basedraw; basedraw = new Relation();    break; //Relation
    case 3  : delete basedraw; basedraw = new Gravity();     break; //Gravity
    case 4  : delete basedraw; basedraw = new takami();      break; //EscapeParticles
    case 5  : delete basedraw; basedraw = new Gushi01();     break; //prrrrrrrroooo
    case 6  : delete basedraw; basedraw = new tkmOTO();      break; //tkmOTO
    default : return;                                        break; //nomatch
  }

  DisplaySetup();
  basedraw -> setup();

  style = ofGetStyle();

}

//--------------------------------------------------------------
void MainScreen :: exit(){
}

//--------------------------------------------------------------
void MainScreen::update(){
}

//--------------------------------------------------------------
void MainScreen::draw(){
  
  ofSetColor(255);
  
  for(int x = 0 ; x < width ; x+= 10)
    ofDrawLine(x, 0, x, width);
  for(int y = 0 ; y < height ; y += 10)
    ofDrawLine(0, y, height, y);
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

  width  = w;
  height = h;


}

//--------------------------------------------------------------
void MainScreen::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void MainScreen::dragEvent(ofDragInfo dragInfo){ 

}



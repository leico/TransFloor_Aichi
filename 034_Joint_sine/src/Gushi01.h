//
//  Gushi01.h
//  emptyExample
//
//  Created by LIFE_MAC25  on 2015/12/01.
//
//　　curve draw

#ifndef Gushi01_h
#define Gushi01_h

#define HOST "localhost"
#define PORT 12346

#include "Base.h"

class Gushi01 : public Base{

  vector <ofPoint>       humans; //めっちゃ便利配列
  vector <ofSoundPlayer> curves;

  float volume;

  public:

  void setup (void){
    ofBackground(0);
    ofFill();

    curves.resize(32);
    for(int i = 0 ; i < curves.size() ; ++ i){
      curves[i].load("sound/curve.wav");
      curves[i].setLoop(true);
      curves[i].setVolume(0);
      curves[i].play();
    }

    humans.resize(1024);

    ofSetVerticalSync(true);
    ofSetCircleResolution(32);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
  }
  //-----------------------------------------------------
  void update (void){

  }
  //-----------------------------------------------------
  void osc (vector <ofxOscMessage> &m){

    for(int i = 0 ; i < curves.size() ; ++ i)
      curves[i].setVolume(0);

    volume = 1.0 / float(m.size());

    humans.clear();
    for(int i = 0; i <m.size() ; ++ i){

      if(m[i].getAddress() == "/human"){
        humans.push_back(
          ofPoint( m[i].getArgAsInt32(0)
                 , m[i].getArgAsInt32(1)
                 , m[i].getArgAsInt32(2)
          )
        );

        float width  = ofGetWidth () / 2;
        float height = ofGetHeight() / 2;
        float x      = abs( (humans[i].x - width)  / width );
        float y      = (humans[i].y - height) / height;

        curves[i].setVolume(volume * x);
        curves[i].setSpeed (1.0 * y);
      }
    }


  }
  //------------------------------------------------------
  void draw (void){

    ofPoint center(ofGetWidth() / 2, ofGetHeight() / 2);


    for(int i = 0 ; i < humans.size(); ++ i){
     
      for(int j = 0 ; j < 3 ; ++ j){
        ofSetColor(ofRandom(100, 255), ofRandom(100, 255), ofRandom(100, 255));
        ofDrawBezier(humans[i].x                      , humans[i].y,
                     humans[i].x + ofRandom(-300, 300), humans[i].y + ofRandom(-300, 300),
                     center.x    + ofRandom(-300, 300), center.y    + ofRandom(-300, 300),
                     center.x                         , center.y                         );
      }
    }
  }

};

#endif /* Gushi01_h */

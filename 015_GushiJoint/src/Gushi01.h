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
        float x      = (humans[i].x - width)  / width;
        float y      = (humans[i].y - height) / height;

        curves[i].setVolume(volume * y);
        curves[i].setSpeed (2.0 * x);
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


/*
    ofSetColor(255);

    for(int i = 0 ; i < humans.size() ; ++ i ){
      ofSetColor(ofRandom(100,255),ofRandom(100,255),ofRandom(100,255));


      glLineWidth(ofRandom(6));
      ofDrawLine(humans[i].x+ofRandom(30),humans[i].y+ofRandom(30),
          humans[i+1].x+ofRandom(30),humans[i+1].y+ofRandom(30));

      ofSetColor(ofRandom(100,255),ofRandom(100,255),ofRandom(100,255));
      ofDrawBezier(humans[i+2].x+ofRandom(30),humans[i+2].y+ofRandom(30),
          humans[i+3].x+ofRandom(30),humans[i+3].y+ofRandom(30),
          humans[i].x+ofRandom(30),humans[i].y+ofRandom(30),
          humans[i+1].x+ofRandom(30),humans[i+1].y+ofRandom(30));

      ofSetColor(ofRandom(200,255),ofRandom(200,255),ofRandom(200,255));
      ofDrawBezier(humans[i].x+ofRandom(30),humans[i].y+ofRandom(30),
          humans[i+1].x+ofRandom(30),humans[i+1].y+ofRandom(30),
          humans[i+3].x+ofRandom(30),humans[i+3].y+ofRandom(30),
          humans[i+2].x+ofRandom(30),humans[i+2].y+ofRandom(30));

      if(humans.size()>2)(curve.setVolume(0.5f),
          curve.setSpeed(1.0f * (humans[i].x/humans[i+1].x)));

    }
*/

  }

};

#endif /* Gushi01_h */

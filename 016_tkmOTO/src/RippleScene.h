//
//  Header.h
//  emptyExample
//
//  Created by iamas_retina02 on 2015/12/03.
//
//

#ifndef RippleScene_h
#define RippleScene_h

#include "Base.h"
#include "Ripple.h"

class RippleScene : public Base{

  std :: list < Ripple > ripples;

  float max_radius;
  float resist;

  public:
  /* ============================================================ *
   * setup(void)                                                  *
   * ============================================================ */
  void setup (void){

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
//    ofSetLineWidth(16);
//    ofNoFill();
      ofFill();
      ofBackground(255);

      ofClear(255);

    max_radius = 400;
    resist = 0.01;
  }

  /* ============================================================ *
   * update(void)                                                 *
   * ============================================================ */
  void update(void){
    using namespace std;

    for(list<Ripple> :: iterator it = ripples.begin() ; it != ripples.end() ; ++ it){
      
      if( it -> End() )        it = ripples.erase(it);
      if( it == ripples.end()) break;
      it -> Update();
    }
  }

  /* ============================================================ *
   * update(void)                                                 *
   * ============================================================ */
  void osc(vector<ofxOscMessage> &m){

    for(int i = 0 ; i < m.size() ; ++ i){
      ripples.push_back(
        Ripple(
             ofPoint(
                  m[i].getArgAsInt32(0)
                , m[i].getArgAsInt32(1)
                , m[i].getArgAsInt32(2)
             )
           , ofColor :: fromHsb(ofRandom(0, 255), 255 - m[i].getArgAsInt32(2), 255, 128)
           , max_radius
           , resist
        )
      );
    }
    
  }

  /* ============================================================ *
   * update(void)                                                 *
   * ============================================================ */
  void draw(void){

    for(list<Ripple> :: iterator it = ripples.begin() ; it != ripples.end() ; ++ it){
      it -> Draw();
    }
  }

};


#endif /* RippleScene_h */

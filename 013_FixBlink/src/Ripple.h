//
//  Ripple.h
//  emptyExample
//
//  Created by iamas_retina02 on 2015/12/03.
//
//

#ifndef Ripple_h
#define Ripple_h

#include "ofMain.h"
#include "Change.h"

class Ripple{

  ofPoint pos;

  Change<ofColor> color;
  Change<float>   radius;

  bool end;

  public:
  /* ============================================================= *
   * constructor / destructor                                      *
   * ============================================================= */
  Ripple(void){
    ofColor blk(0, 0, 0, 0);

    color .Setup(blk, blk, 0);
    radius.Setup(0, 0, 0);

    end = false;
    
  }

  ~Ripple(void){}
  /* ============================================================= *
   * Ripple(const ofPoint &_pos,        const ofColor &_color      *
   *      , const float    max_radius, const float     resist)     *
   * ============================================================= */

  Ripple(const ofPoint &_pos,       const ofColor &_color
       , const float    max_radius, const float    resist)
  {
    pos = _pos;
    ofColor base      = _color;
    ofColor endcolor  = _color;
    endcolor.a = 0;

    color .Setup(base, endcolor, resist);
    radius.Setup(0, max_radius, resist);
    
    end = false;
  }
  /* ============================================================ *
   * Setup(const ofPoint &_pos,        const ofColor &_color      *
   *     , const float    max_radius, const float     resist)     *
   * ============================================================ */
  void Setup(const ofPoint &_pos,       const ofColor &_color
           , const float    max_radius, const float    resist)
  {
    pos = _pos;
    ofColor base      = _color;
    ofColor endcolor  = _color;
    endcolor.a = 0;

    color .Setup(base, endcolor, resist);
    radius.Setup(0, max_radius, resist);
    
    end = false;
  }
 
  /* ======================================================================= *
   * Update(void)                                                            *
   * ======================================================================= */
  void Update(void){

    color .Update();
    radius.Update();

    if(color .Current() == color .Target()) end = true;
    if(radius.Current() == radius.Target()) end = true;

    
  }
  /* ======================================================================= *
   * Draw(void)                                                              *
   * ======================================================================= */
  void Draw(void){
    ofSetColor( color.Current() );
    ofDrawCircle( pos, radius.Current() );
  }

  /* ======================================================================= *
   * bool End(void)                                                          *
   * ======================================================================= */
  const bool End(void){
    return end;
  }

};


#endif /* Ripple_h */

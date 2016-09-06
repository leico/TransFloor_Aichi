//
//  Blank.h
//  emptyExample
//
//  Created by iamas_retina02 on 2015/12/03.
//
//

#ifndef Blank_h
#define Blank_h

class Blank : public Base{

  public:
  virtual ~Blank(){}

  void setup (void){}
  void update(void){}
  void osc   (vector< ofxOscMessage > &m){}
  void draw  (void){}
};


#endif /* Blank_h */

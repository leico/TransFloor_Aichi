//
//  Header.h
//  emptyExample
//
//  Created by leico_system on 2015/11/17.
//
//

#ifndef Header_h
#define Header_h

#include "ofMain.h"
#include "ofxOsc.h"

class Base{

  public:
    virtual ~Base(){}
  
    virtual void setup (void)                     = 0;
    virtual void update(void)                     = 0;
    virtual void osc   (vector<ofxOscMessage> &m) = 0;
    virtual void draw  (void)                     = 0;
};


#endif /* Header_h */

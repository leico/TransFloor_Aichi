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

  protected:
    static int width;
    static int height;

  public:
    virtual ~Base(){}
  
    virtual void setup (void)                     = 0;
    virtual void update(void)                     = 0;
    virtual void osc   (vector<ofxOscMessage> &m) = 0;
    virtual void draw  (void)                     = 0;

    int ofGetWidth (void);
    int ofGetHeight(void);

    void resize(const int w, const int h);
};

inline int Base :: ofGetWidth(void) { return width;  }
inline int Base :: ofGetHeight(void){ return height; }

inline void Base :: resize(const int w, const int h){
  width  = w;
  height = h;
}
  


#endif /* Header_h */

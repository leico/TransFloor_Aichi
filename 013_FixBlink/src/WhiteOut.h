//
//  WhiteOut.h
//  emptyExample
//
//  Created by leico_system on 2016/09/07.
//
//

#ifndef WhiteOut_h
#define WhiteOut_h

class WhiteOut : public Base{

  public:
  virtual ~WhiteOut(){}

  void setup (void){ ofBackground(255); }
  void update(void){}
  void osc   (vector< ofxOscMessage > &m){}
  void draw  (void){}
};


#endif /* WhiteOut_h */

//
//  Relation.h
//  emptyExample
//
//  Created by iamas_retina02 on 2015/12/03.
//
//

#ifndef Relation_h
#define Relation_h

class Relation : public Base{

  vector< ofPoint > humans;

  public:
  /* ============================================================ *
   * setup(void)                                                  *
   * ============================================================ */
  void setup(void){

    humans.resize(1024);
    humans.clear();

    ofSetLineWidth(20);
    
  }

  /* ============================================================ *
   * update(void)                                                 *
   * ============================================================ */
  void update(void){
  }

  /* ============================================================ *
   * osc(void)                                                    *
   * ============================================================ */
  void osc(vector<ofxOscMessage> &m){

    humans.clear();

    for(int i = 0 ; i < m.size() ; ++ i){
      if(m[i].getAddress() == "/human"){

        humans.push_back(
          ofPoint(
              m[i].getArgAsInt32(0)
            , m[i].getArgAsInt32(1)
            , m[i].getArgAsInt32(2)
          )
        );
      }
    }
    
  }
  /* ============================================================ *
   * draw(void)                                                   *
   * ============================================================ */
  void draw(void){

    ofSetColor(255);

    for(int i = 0 ; i < humans.size() ; ++ i){
      ofDrawCircle(humans[i], 30);
      
      for(int j = i ; j < humans.size() ; ++ j){
        ofDrawLine(humans[i], humans[j]);
      }
    }

  }

};


#endif /* Relation_h */

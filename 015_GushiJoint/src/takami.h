//
//  takami.h
//  emptyExample
//
//  Created by asamiTakami on 2015/12/01.
//
//

#ifndef emptyExample_takami_h
#define emptyExample_takami_h


#include "Base.h"
#include "Particle.h"

class takami : public Base{

  private:

    vector < ofPoint > humans; //vector 可変長配列　超便利配列！

    vector< Particle > particles ;

    vector< ofColor > col;
    vector< float > kaiten ;
    static const int NUM = 300;


  public:


    void setup(void){

      ofSetFrameRate(60);
      ofSetBackgroundAuto(true);
      ofFill();

      Particle :: resize(ofGetWidth(), ofGetHeight());

      for (int i = 0; i < NUM; i++) {
        ofColor c;
        c.setHsb(ofRandom(255), 180, 255,255);

        col.push_back(c);

        float k = ofRandom(360);
        kaiten.push_back(k);
        

        Particle p;
        p.friction = 0.002;
        p.setup(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), ofVec2f(0, 0));
        particles.push_back(p);
      }


    }


    void osc(vector<ofxOscMessage> &m){

      humans.resize(m.size());// m.size()でvectorの大きさ、resizeでサイズ変更
      int j = 0;
      for(int i = 0 ; i < m.size() ; ++i ){
        if(m[i].getAddress()== "/human"){

          humans[j].x = m[i].getArgAsInt32(0);
          humans[j].y = m[i].getArgAsInt32(1);
          humans[j].z = m[i].getArgAsInt32(2);

          ++j;
        }
      }
    }




    void update(void){

      for (int i = 0; i < particles.size(); i++){
        // パーティクルの数だけ計算
        for (int j = 0; j < humans.size(); j++){
          // 力をリセット
          particles[i].resetForce();
          //引力
          particles[i].addRepulsionForce(humans[j].x, humans[j].y, 300, 0.1);
        }
        // パーティクル更新
        particles[i].update();
        // 画面の端にきたら反対側へ
        particles[i].bounceOffWalls();
      }


    }



    void draw(void){

      for (int i = 0; i < particles.size(); i++) {

        ofSetColor(col[i]);
        ofPushMatrix();

        ofTranslate(particles[i].position.x, particles[i].position.y);
        ofRotateZ(ofGetFrameNum()+kaiten[i]);

        if(i <= particles.size()/3){
          ofDrawRectangle(0, 0, 20, 20);
          ofPopMatrix();
          continue;
        }


        if(i <= particles.size()*2/3){
          ofSetCircleResolution(32);
          ofDrawCircle(0,0,10);
          ofPopMatrix();
          continue;
        }

        ofSetCircleResolution(3);
        ofDrawCircle(0, 0, 16);
        ofPopMatrix();


      }


      for(int j = 0 ; j < humans.size() ; j++){
        ofSetColor(255);
        ofNoFill();
        ofSetCircleResolution(ofRandom(3,10));
        ofDrawCircle(humans[j].x, humans[j].y, 30);

      }

    }

    void resize(const int w, const int h){
      Base :: resize(w, h);
      Particle :: resize(w, h);
      
      for(int i = 0 ; i < particles.size() ; ++ i)
        particles.at(i).setup(ofVec2f(ofRandom(ofGetWidth()), ofRandom(ofGetHeight())), ofVec2f(0, 0));

      
    }





};



#endif

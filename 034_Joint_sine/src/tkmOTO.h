//
//  tkmOTO.h
//  mySketch
//
//  Created by asamiTakami on 2015/11/26.
//
//

#ifndef __mySketch__tkmOTO__
#define __mySketch__tkmOTO__

#include "Base.h"
#include "particle.h"




class tkmOTO :public Base{

  private:
    vector < ofPoint > humans; //vector 可変長配列　超便利配列！
    vector < Particle > particles ;

    vector< ofColor > col;
    vector< float > kaiten ;
    bool atraction;
    static const int NUM = 30;
    ofSoundPlayer ppi,ppi2,ppi3,ppi4;


  public:





    void setup(void){

      ofSetBackgroundAuto(true);
      ofFill();

      ppi.load("sound/b_068.aiff");
      ppi.setVolume(0.75f);
      ppi.setMultiPlay(true);
      ppi2.load("sound/b_068.aiff");
      ppi2.setVolume(0.75f);
      ppi2.setMultiPlay(true);
      ppi2.setSpeed(0.8);
      ppi3.load("sound/b_068.aiff");
      ppi3.setVolume(0.75f);
      ppi3.setMultiPlay(true);
      ppi3.setSpeed(0.5);
      ppi4.load("sound/b_068.aiff");
      ppi4.setVolume(0.75f);
      ppi4.setMultiPlay(true);
      ppi4.setSpeed(1.2);

      humans   .clear();
      particles.clear();
      col      .clear();
      kaiten   .clear();

      Particle :: resize(ofGetWidth(), ofGetHeight());

      for (int i = 0; i < NUM; i++) {
        ofColor c;
        c.setHsb(ofRandom(150), 180, 255,255);

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
      for(int i = 0 ; i < m.size() ; ++i ){
        if(m[i].getAddress()== "/human"){
          humans[i].x = m[i].getArgAsInt32(0);
          humans[i].y = m[i].getArgAsInt32(1);
          humans[i].z = m[i].getArgAsInt32(2);
        }
      }
    }




    void update(void){

      ofSoundUpdate();


      for (int i = 0; i < particles.size(); i++){
        // パーティクルの数だけ計算
        // 力をリセット
        particles[i].resetForce();
        for (int j = 0; j < humans.size(); j++){
          //反発
          particles[i].addRepulsionForce(humans[j].x, humans[j].y, 300, 0.3);

        }

          //particles[i].addAttractionForce(particles[j], 120.0, 0.01);

          // パーティクル更新
          particles[i].update();
          // 画面の端にきたら跳ね返る
          particles[i].bounceOffWalls();
          //画面の端に来たら音がなる
          particles[i].soundOfWalls(ppi,ppi2,ppi3,ppi4);
      }
    }



    void draw(void){

      ofFill();
      if(humans.size() == 0)ofNoFill();
      for (int i = 0; i < particles.size(); i++) {

        ofSetColor(col[i]);
        ofPushMatrix();

          ofTranslate(particles[i].position.x, particles[i].position.y);
          ofRotateZ(ofGetFrameNum()+kaiten[i]);

          if(i <= particles.size() / 3){
            ofDrawRectangle(0, 0, 40, 40);
            ofPopMatrix();
            continue;
          }

          if(i <= particles.size() * 2 / 3){
            ofSetCircleResolution(64);
            ofDrawCircle(0,0,20);
            ofPopMatrix();
            continue;
          }

          ofSetCircleResolution(3);
          ofDrawCircle(0, 0, 32);
          ofPopMatrix();
      }
    }

  
  
  
  
  
  
    void resize(const int w, const int h){
      Base :: resize(w, h);
      Particle :: resize(w, h);

      setup();
      
      
    }





};


#endif /* defined(__mySketch__tkmOTO__) */

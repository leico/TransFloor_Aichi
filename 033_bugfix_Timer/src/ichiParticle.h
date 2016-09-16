//
//  iParticle.h
//  emptyExample
//
//  Created by iamas_retina02 on 2015/12/01.
//
//

#ifndef ichiParticle_h
#define ichiParticle_h

#include "Base.h"
#include "iParticle.h"

class ichiParticle : public Base{
    
    vector< ofPoint > humans;
    vector< ofPoint > preTgt;
    int ctr;
    double pre_x,pre_y;
    uint64_t preEventTimeMemo;
    const uint64_t tactTime = 5000;
    uint64_t gravityResetTime;
    const uint64_t resetTime = 25;
    
    //particleMode currentMode;
    string currentModeStr;
    
    vector <iParticle> p;
    vector <ofPoint> attractPoints;
    vector <ofPoint> attractPointsWithMovement;
    
public:
    void setup (void){
        //ofSetWindowShape(1280, 1440);
        ofBackground(192);
        preTgt.resize(20);
        for(int i = 0; i < preTgt.size(); i++){
            preTgt[i].x=ofRandom(0, ofGetWindowWidth());
            preTgt[i].y=ofRandom(0, ofGetWindowHeight());
        }

        preEventTimeMemo = ofGetElapsedTimeMillis();
        
        ofSetVerticalSync(true);
        
        int num = 100;
        p.assign(num, iParticle());
        resetParticles();
        for(unsigned int i = 0; i < p.size(); i++){
            p[i].resetCollor();
            //p[i].setMode(i%3);
        }
    }
    //--------------------------------------------------------------
    void resetParticles(){
        
        for(unsigned int i = 0; i < p.size(); i++){
            p[i].reset();
        }	
    }
    
    void update(void){
        for(unsigned int i = 0; i < p.size(); i++){
            //p[i].setMode(currentMode);
            p[i].update();
        }
        

    }
    
    void osc   (vector< ofxOscMessage > &m){
        humans.resize( m.size() );
        
        // "/human_x_y_z"
        for(int i = 0, j = 0 ; i < m.size() ; ++ i){
            
            if(m[i].getAddress() == "/human"){
                humans[j].x = m[i].getArgAsInt32(0);
                humans[j].y = m[i].getArgAsInt32(1);
                humans[j].z = m[i].getArgAsInt32(2);
                
                ++ j;
            }
        }
        
    }
    
    void draw  (void){
        
        ////デバッグ用：マウスカーソルで代用の場合以下コメントアウト
        //humans.resize(1);
        //humans[0].x = ofGetMouseX();
        //humans[0].y = ofGetMouseY();
        
        //一人だけを追い続けるための処理
        bool flug = false;//人を検出しているかどうかフラグ
        double tgt_x,tgt_y;//目標座標X,Y
        vector<ofPoint> tgt;
        tgt.resize(preTgt.size());
        for(int i = 0; i < preTgt.size(); i++){
            tgt[i].x=preTgt[i].x;//前回の目標X座標を仮に設定
            tgt[i].y=preTgt[i].y;//前回の目標Y座標を仮に設定
        }

        
        for(int i = 0 ; i < tgt.size() ; i++ ){
            //検出した人数分ループ
            for(int j = 0 ; j < humans.size() ; j++ ){
                flug = true;//ループに入っているなら人を１人以上検出しているのでフラグセット
                if(j==0){//ループ１週目の処理
                    //検出１人目を目標座標に仮設定
                    tgt[i].x = humans[j].x;
                    tgt[i].y = humans[j].y;
                }else{//ループ２周め以降
                    //前回の座標と検出人物座標の距離を比較
                    double length_c,length_p;//現ループの人の距離、前ループまでで一番前回の座標に近い人までの距離
                    //前ループまでで一番前回の座標に近い人までの距離の計算。XY各座標の差をとって２乗する(大きさ比較出来れば良いので平方根とるのは省略)
                    length_p = pow((preTgt[i].x - tgt[i].x),2.0) + pow((preTgt[i].y - tgt[i].y),2.0);
                    //現ループの人の座標と前回の座標に近い人までの距離の計算。XY各座標の差をとって２乗する(大きさ比較出来れば良いので平方根とるのは省略)
                    length_c = pow((preTgt[i].x - humans[j].x),2.0) + pow((preTgt[i].y - humans[j].y),2.0);
                    
                    //距離の大きさ比較
                    if(length_p>length_c){
                        //現ループの人の座標の方が短い場合、目標座標を更新
                        tgt[i].x = humans[j].x;
                        tgt[i].y = humans[j].y;
                    }
                }
            }
        }
        
        //一定時間おきにターゲットを変更する。
        uint64_t currTime;
        currTime = ofGetElapsedTimeMillis();
        if(currTime > preEventTimeMemo + tactTime){

            preEventTimeMemo = currTime;
            for(unsigned int j = 0; j < p.size(); j++){
                p[j].setGravityMode(GRAVITY_MODE_REPEL);
            }
            gravityResetTime=currTime + resetTime;
            //resetParticles();
        }
        if(currTime > gravityResetTime){
            for(int i = 0; i < tgt.size(); i++){
                tgt[i].x=ofRandom(0, ofGetWidth());
                tgt[i].y=ofRandom(0, ofGetHeight());
            }
            
            for(unsigned int j = 0; j < p.size(); j++){
                p[j].setGravityMode(GRAVITY_MODE_ATTRACT);
            }
            gravityResetTime=currTime + (tactTime * 2);
            //resetParticles();
        }
        
        //前回描画座標を更新
        //pre_x = tgt_x;
        //pre_y = tgt_y;
            for(int i = 0; i < preTgt.size(); i++){
                preTgt[i].x = tgt[i].x;
                preTgt[i].x = tgt[i].y;
            }
        
        //ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));
        

        //////////////////////////////////////////////////////////////////
        //人物を検出していた場合
        if(flug){
            for(unsigned int i = 0; i < p.size(); i++){
                p[i].setAttractPoint(ofPoint(tgt[i % (tgt.size())].x,tgt[i % (tgt.size())].y));
                p[i].draw();
            }
        }

        
    }
};
    
    
#endif /* ichiParticle_h */

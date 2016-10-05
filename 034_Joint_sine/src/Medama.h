//
//  ofmyDraw.h
//  emptyExample
//
//  Created by iamas_retina02 on 2015/12/01.
//
//

#ifndef Medama_h
#define Medama_h

#include "Base.h"


class Medama : public Base{
  
  vector< ofPoint > humans;
    int ctr;
    double pre_x,pre_y;
    uint64_t preEventTimeMemo;
    const uint64_t tactTime = 15000;
    
public:
  void setup (void){
      ofSetWindowShape(1280, 1440);
      ofBackground(192);
      pre_x = 0.0;
      pre_y = 0.0;
      preEventTimeMemo = ofGetElapsedTimeMillis();
    
  }
  void update(void){
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
      ofSetCircleResolution(64);
      
      //目玉描画用のパラメータ計算
      float rCentor_y =ofGetWindowHeight()*5/7;//中心X座標右目
      float lCentor_y =ofGetWindowHeight()*2/7;//中心X座標左目
      float rCentor_x =ofGetWindowWidth()/2;//中心Y座標右目
      float lCentor_x =ofGetWindowWidth()/2;//中心Y座標左目
      float eyeSize = ofGetWindowHeight()/6;//目玉サイズ外径
      float eyeSize2 = ofGetWindowHeight()/10;//黒目サイズ
      float lineWidth = ofGetWindowHeight()/40;//描画線太さ
      float eyePosLen =eyeSize-eyeSize2-lineWidth/2;//黒目中心の位置：目の中心からの距離
      
      double direction_rx , direction_ry , direction_lx , direction_ly;//黒目の方向(ベクトル)
      double angle_r , angle_l;//黒目の方向(角度rad)
      
      ////デバッグ用：マウスカーソルで代用の場合以下コメントアウト
      //humans.resize(1);
      //humans[0].x = ofGetMouseX();
      //humans[0].y = ofGetMouseY();

      //一人だけを追い続けるための処理
      bool flug = false;//人を検出しているかどうかフラグ
      double tgt_x,tgt_y;//目標座標X,Y
      tgt_x = pre_x;//前回の目標X座標を仮に設定
      tgt_y = pre_y;//前回の目標Y座標を仮に設定
      //検出した人数分ループ
      for(int i = 0 ; i < humans.size() ; ++ i){
          flug = true;//ループに入っているなら人を１人以上検出しているのでフラグセット
          if(i==0){//ループ１週目の処理
              //検出１人目を目標座標に仮設定
              tgt_x = humans[i].x;
              tgt_y = humans[i].y;
          }else{//ループ２周め以降
              //前回の座標と検出人物座標の距離を比較
              double length_c,length_p;//現ループの人の距離、前ループまでで一番前回の座標に近い人までの距離
              //前ループまでで一番前回の座標に近い人までの距離の計算。XY各座標の差をとって２乗する(大きさ比較出来れば良いので平方根とるのは省略)
              length_p = pow((pre_x - tgt_x),2.0) + pow((pre_y - tgt_y),2.0);
              //現ループの人の座標と前回の座標に近い人までの距離の計算。XY各座標の差をとって２乗する(大きさ比較出来れば良いので平方根とるのは省略)
              length_c = pow((pre_x - humans[i].x),2.0) + pow((pre_y - humans[i].y),2.0);
              
              //距離の大きさ比較
              if(length_p>length_c){
                  //現ループの人の座標の方が短い場合、目標座標を更新
                  tgt_x = humans[i].x;
                  tgt_y = humans[i].y;
              }
          }
      }
      
      //一定時間おきにターゲットを変更する。
      uint64_t currTime;
      currTime = ofGetElapsedTimeMillis();
      if(currTime > preEventTimeMemo + tactTime){
          if(humans.size()>1){
              int temp_index;
              int temp_x,temp_y;
              int counter;
              counter = 0 ;
              do{
                  temp_index=(int)ofRandom(0, humans.size());
                  temp_x = humans[temp_index].x;
                  temp_y = humans[temp_index].y;
                  counter++;
              }while( counter < 10 && temp_x == tgt_x );
              tgt_x = temp_x;
              tgt_y = temp_y;
          }
          preEventTimeMemo = currTime;
      }
      
      //前回描画座標を更新
      pre_x = tgt_x;
      pre_y = tgt_y;

      
      //////////////////////////////////////////////////////////////////
      //人物を検出していた場合
      if(flug){
          bool near_r = false;//目を踏んでるフラグ右
          bool near_l = false;//目を踏んでるフラグ左
          bool center = false;//左右の目の間(眉間)に人がいる場合フラグ
          //////////////////////////////////////////////////////////////////
          //検出人数分ループ
          for(int i = 0  ;i <humans.size(); ++ i){
              double length_e;
              //右目踏んでいるかチェック(右目の中心座標からの距離で判断)
              length_e = sqrt(pow((humans[i].x - rCentor_x),2.0) + pow((humans[i].y - rCentor_y),2.0));
              if(length_e < eyeSize){
                  near_r = true;
              }
              //左目踏んでいるかチェック(左目の中心座標からの距離で判断)
              length_e = sqrt(pow((humans[i].x - lCentor_x),2.0) + pow((humans[i].y - lCentor_y),2.0));
              if(length_e < eyeSize){
                  near_l = true;
              }
          }
          //左右の目の間(眉間)に人がいるかチェック
          if(   lCentor_y + eyeSize < tgt_y
             && tgt_y < rCentor_y - eyeSize
             && rCentor_x - eyeSize < tgt_x
             && tgt_x < rCentor_x + eyeSize
             ){
              center=true;
          }
          //////////////////////////////////////////////////////////////////
          //黒目の方向(ベクトル)計算(目標人物の座標と左右の目の中心座標との差分)
          direction_rx = tgt_x - rCentor_x;
          direction_ry = tgt_y - rCentor_y;
          direction_lx = tgt_x - lCentor_x;
          direction_ly = tgt_y - lCentor_y;
          //////////////////////////////////////////////////////////////////
          //右目の描画
          if(near_r){
              //目を踏んでる場合、目をとじる
              ofSetColor(0,0,0);
              //ofDrawRectangle(rCentor_x-eyeSize, rCentor_y-lineWidth/2, eyeSize*2, lineWidth);
              ofSetLineWidth(lineWidth);
              ofDrawLine(rCentor_x, rCentor_y-eyeSize, rCentor_x            , rCentor_y + eyeSize);
              ofDrawLine(rCentor_x, rCentor_y-eyeSize, rCentor_x - eyeSize/3, rCentor_y + eyeSize);
              ofDrawLine(rCentor_x, rCentor_y-eyeSize, rCentor_x + eyeSize/3, rCentor_y + eyeSize);
              
          }else{
              //目を踏んでない場合、目を描画
              ofSetColor(0,0,0);
              ofFill();
              //目の輪郭線
              ofDrawCircle(rCentor_x, rCentor_y, eyeSize);
              ofSetColor(255,255,255);
              ofFill();
              //白目の部分
              ofDrawCircle(rCentor_x, rCentor_y, eyeSize - lineWidth);
              
              //目標人物の方向に黒目を描画
              angle_r = -(atan2(direction_rx,direction_ry)-pi/2);//黒目を向ける方向(角度)の計算
              ofSetColor(0,0,0);
              ofFill();
              //求めた角度を用いて黒目を描画(求めた角度方向へ距離eyePosLen分ずらして黒丸を描画)
              ofDrawCircle(rCentor_x + cos(angle_r)*eyePosLen , rCentor_y + sin(angle_r)*eyePosLen, eyeSize2);

          }
          //左目の描画
          if(near_l){
              //目を踏んでる場合、目をとじる
              ofSetColor(0,0,0);
              ofSetLineWidth(lineWidth);
              ofDrawLine(lCentor_x            , lCentor_y - eyeSize, lCentor_x, lCentor_y + eyeSize);
              ofDrawLine(lCentor_x - eyeSize/3, lCentor_y - eyeSize, lCentor_x, lCentor_y + eyeSize);
              ofDrawLine(lCentor_x + eyeSize/3, lCentor_y - eyeSize, lCentor_x, lCentor_y + eyeSize);
              
              
          }else{
              //目を踏んでない場合、目を描画
              ofSetColor(0,0,0);
              ofFill();
              //目の輪郭線
              ofDrawCircle(lCentor_x, lCentor_y, eyeSize);
              ofSetColor(255,255,255);
              ofFill();
              //白目の部分
              ofDrawCircle(lCentor_x, lCentor_y, eyeSize - lineWidth);
              
              //目標人物の方向に黒目を描画
              angle_l = -(atan2(direction_lx,direction_ly)-pi/2);//黒目を向ける方向(角度)の計算
              ofSetColor(0,0,0);
              ofFill();
              //求めた角度を用いて黒目を描画(求めた角度方向へ距離eyePosLen分ずらして黒丸を描画)
              ofDrawCircle(lCentor_x + cos(angle_l)*eyePosLen , lCentor_y + sin(angle_l)*eyePosLen, eyeSize2);
              
          }
          
          //眉間に人物が立っていた場合
          if(center){
              ofSetColor(0,0,0);
              ofSetLineWidth(lineWidth);
              //眉間に線を３本引く
              ofDrawLine((ofGetWindowWidth()/2) - ofGetWindowWidth()/20, (ofGetWindowHeight()/2),
                         (ofGetWindowWidth()/2) + ofGetWindowWidth()/20, (ofGetWindowHeight()/2));
              
              ofDrawLine((ofGetWindowWidth()/2)- ofGetWindowWidth()/20, (ofGetWindowHeight()/2)-ofGetWindowHeight()/30,
                         (ofGetWindowWidth()/2)+ ofGetWindowWidth()/20, (ofGetWindowHeight()/2)-ofGetWindowHeight()/30);
              
              ofDrawLine((ofGetWindowWidth()/2)- ofGetWindowWidth()/20, (ofGetWindowHeight()/2)+ofGetWindowHeight()/30,
                         (ofGetWindowWidth()/2)+ ofGetWindowWidth()/20, (ofGetWindowHeight()/2)+ofGetWindowHeight()/30);
              
          }
          
      ////////////////////////////////////////////////////////////////
      //人物を検出していない場合
      }else{
          //両目を閉じる
          ofSetColor(0,0,0);
          //ofDrawRectangle(rCentor_x-eyeSize, rCentor_y-lineWidth/2, eyeSize*2, lineWidth);
          ofSetLineWidth(lineWidth);
          ofDrawLine(rCentor_x, rCentor_y-eyeSize, rCentor_x            , rCentor_y + eyeSize);
          ofDrawLine(rCentor_x, rCentor_y-eyeSize, rCentor_x - eyeSize/3, rCentor_y + eyeSize);
          ofDrawLine(rCentor_x, rCentor_y-eyeSize, rCentor_x + eyeSize/3, rCentor_y + eyeSize);

          ofDrawLine(lCentor_x            , lCentor_y - eyeSize, lCentor_x, lCentor_y + eyeSize);
          ofDrawLine(lCentor_x - eyeSize/3, lCentor_y - eyeSize, lCentor_x, lCentor_y + eyeSize);
          ofDrawLine(lCentor_x + eyeSize/3, lCentor_y - eyeSize, lCentor_x, lCentor_y + eyeSize);

      }
  }
};

#endif /* Medama_h */

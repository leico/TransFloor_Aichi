//
//  Particle.h
//  emptyExample
//
//  Created by asamiTakami on 2015/12/04.
//
//

#ifndef __emptyExample__Particle__
#define __emptyExample__Particle__

#include <stdio.h>

#pragma once
#include "ofMain.h"

class Particle {

  static int width;
  static int height;
    
public:
    //コンストラクタ
    Particle();
    // 初期設定(パーティクルの出現場所)
    void setup(ofVec2f position, ofVec2f velocity);
    void setup(float positionX, float positionY, float velocityX, float velocityY);
    // 力をリセット
    void resetForce();
    // 力を加える
    void addForce(ofVec2f force);
    void addForce(float forceX, float forceY);
    // 力を更新
    void updateForce();
    // 位置の更新
    void updatePos();
    // 更新(位置と力)
    void update();
    // 画面からはみ出たらバウンドさせる
    void bounceOffWalls();
    // 画面からはみ出たら反対側から出現
    void throughOfWalls();
    // 描画
    void draw();

    void soundOfWalls(ofSoundPlayer& ppi1, ofSoundPlayer& ppi2, ofSoundPlayer& ppi3, ofSoundPlayer& ppi4);

    
    // 反発する力
    void addRepulsionForce(float x, float y, float radius, float scale);
    void addRepulsionForce(Particle &p, float radius, float scale);
    
    // 引きつけあう力
    void addAttractionForce(float x, float y, float radius, float scale);
    void addAttractionForce(Particle &p, float radius, float scale);
    
    // 位置ベクトルの配列
    ofVec2f position;
    // 速度ベクトルの配列
    ofVec2f velocity;
    // 力ベクトルの配列
    ofVec2f force;
    // 摩擦係数
    float friction;
    // パーティクルの半径
    float radius;
    // 固定するかどうか
    bool bFixed;
    // パーティクルの質量
    float mass;

    static void resize(const int w, const int h){
      width = w; height = h;
    }

    const int ofGetWidth (void){return width;}
    const int ofGetHeight(void){return height;}
};
    
#endif /* defined(__emptyExample__Particle__) */

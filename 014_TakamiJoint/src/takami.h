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
    
    ofPoint pos[5];
    int rag;
    int hueNum;
    int frameNum;
    int frameNumA;
    vector < ofPoint > humans; //vector 可変長配列　超便利配列！
    
    vector < ofPoint > humansB;
    
    
    vector< Particle > particles ;
    
    
    vector< ofColor > col;
    vector< float > kaiten ;
    // メッシュ
    //ofVboMesh mesh;
    // 引力が働いているか
    bool atraction;
    // パーティクルの数
    static const int NUM = 300;
    
    
public:
    
    
    
    
    
    void setup(void){
        
        rag=0;
        hueNum=0;
        
        ofSetFrameRate(60);
        ofSetBackgroundAuto(true);
        
        
        // メッシュを点で描画
        //mesh.setMode(OF_PRIMITIVE_LINE_STRIP);
        //glPointSize(2.0);
        
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
        
        if (humans.size() >= 1)
        {
            humansB.resize(humans.size());
            for (int j = 0; j < humans.size(); j++){
                
                humansB[j]=humans[j];
            }
            
            
            for (int i = 0; i < particles.size(); i++){
                // パーティクルの数だけ計算
                for (int j = 0; j < humans.size(); j++){
                    
                    
                    // 力をリセット
                    particles[i].resetForce();
                    //引力
                    particles[i].addRepulsionForce(humansB[j].x, humansB[j].y, 300, 0.1);
                    
                    //particles[i].addRepulsionForce(particles[j], 120.0, 0.001);
                    
                    // パーティクル更新
                    particles[i].update();
                    // 画面の端にきたら反対側へ
                    particles[i].bounceOffWalls();
                    
                    
                }
                
                
            }
            
            
            
            
            int waru = frameNum % 6;
            
            if(waru == 0){
                hueNum++;
            }
            if(hueNum >= 255){
                hueNum=0 ;
            }
            frameNum ++;
            frameNumA ++;
            
        }
        
        
    }
    
    
    
    void draw(void){
        
        ofFill();
        //mesh.clear();
        for (int i = 0; i < particles.size(); i++) {
            
            ofSetColor(col[i]);
            ofPushMatrix();
            
            ofTranslate(particles[i].position.x, particles[i].position.y);
            //ofSetColor(col[i]);
            ofRotateZ(ofGetFrameNum()+kaiten[i]);
            
            if(i <= particles.size()/3){
                ofDrawRectangle(0, 0, 20, 20);
                
            }
            
            if(i >= particles.size()/3 && i <= particles.size()*2/3){
                ofSetCircleResolution(64);
                ofDrawCircle(0,0,10);
            }
            
            if(i >= particles.size()*2/3){
                ofSetCircleResolution(3);
                ofDrawCircle(0, 0, 16);
            }
            
            
            //mesh.addVertex(ofVec3f(particles[i].position.x, particles[i].position.y, 0));
            
            ofPopMatrix();
        }
        // mesh.draw();
        
        
        for(int j = 0 ; j < humansB.size() ; j++){
            ofSetColor(255);
            ofNoFill();
            ofSetCircleResolution(ofRandom(3,10));
            ofDrawCircle(humansB[j].x, humansB[j].y, 30);
            
        }
        
        
        
        
        
    }
    
    
    
    
    
    
};



#endif

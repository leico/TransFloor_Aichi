//
//  tkm001.h
//  mySketch
//
//  Created by asamiTakami on 2015/11/26.
//
//

#ifndef __mySketch__tkm001__
#define __mySketch__tkm001__

#include "Base.h"




class tkm001 :public Base{
    
private:
    ofPoint pos[5];
    int rag;
    int hueNum;
    int frameNum;
    int frameNumA;
    vector < ofPoint > humans; //vector 可変長配列　超便利配列！
    
    
    
public:
    
    
    
    
    
    void setup(void){
        
        rag=0;
        hueNum=0;
        ofSetBackgroundAuto(false);
        
        
    }
    
    
    
    
    
    
    
    
    void osc(vector<ofxOscMessage> &m){
        
        /*
         
         int size = (m.size() > 5) ? 5 : m.size();
         
         for(int i = 0 ; i < size ; i++){
         if(m[i].getAddress()=="/human"){
         m[i].getArgAsInt32(0);//X
         m[i].getArgAsInt32(1);//Y
         m[i].getArgAsInt32(2);//Z
         
         pos[i].set(m[i].getArgAsInt32(0),m[i].getArgAsInt32(1),m[i].getArgAsInt32(2));
         
         }*/
        
        
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
    

    
    
    
    
    void draw(void){
        
        
        
        ofColor c;
        c.setHsb(hueNum, 255, 255,200);
        ofSetColor( c );
        
        
        
       for(int i = 0 ;i < humans.size() ;i ++){
           ofPushMatrix();
        
           ofTranslate(humans[i].x,humans[i].y,humans[i].z);
           int z = humans[i].z;
           
           ofFill();
        
           ofDrawCircle(0, 0, z/6);
           ofPopMatrix();

           
        }
        if( frameNum >=6000 ){
        ofSetColor(0,0,0,10);
        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
            
            if(frameNum==6080)frameNum=0;
            
            }
        
    }
   
    









};


#endif /* defined(__mySketch__tkm001__) */

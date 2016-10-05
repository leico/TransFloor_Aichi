//*

#ifndef __nununu__nununu__
#define __nununu__nununu__

#include "Base.h"




class nununu :public Base{
    
private:
    ofPoint mouse;
    ofPoint ranPos;
    ofPoint ranPoss;
    ofPoint ranPosss;
    
    int frame;
    
    vector < ofVec3f > humans; //vector 可変長配列　超便利配列！
    
    
    
    
    
    ofSoundPlayer pura;
    ofSoundPlayer pui;
    ofSoundPlayer paun;
    
public:
    
    
    
    
    
    void setup(void){
        
        int frame;
        
        
        
        pura.load("sound/1pura.wav");
        pui.load("sound/2pui.wav");
        paun.load("sound/3paun.wav");
        pura.setVolume(0.75f);
        pui.setVolume(0.75f);
        paun.setVolume(0.5f);
        pura.setMultiPlay (true);
        pui.setMultiPlay(true);
        paun.setMultiPlay(true);
        
        
        ofSetBackgroundColor(0);
        
        humans.resize(1024);
        humans.clear();
        
        ranPos.set(ofRandom(100,1180),ofRandom(100,1340));
        ranPoss.set(ofRandom(100,1180),ofRandom(100,1340));
        ranPosss.set(ofRandom(100,1180),ofRandom(100,1340));

        
    }
    
    
    
    
    
    
    
    
    void osc(vector<ofxOscMessage> &m){
        
        humans.clear();
        for(int i = 0 ; i < m.size() ; ++ i){
            
            if(m[i].getAddress() == "/human"){
                humans.push_back(
                                 ofVec3f(
                                         m[i].getArgAsInt32(0)
                                         , m[i].getArgAsInt32(1)
                                         ,m[i].getArgAsInt32(2)
                                         )
                                 );
            }
        }
    }
    
    
    
    
    
    void update(void){
        
        for(int i = 0 ;i < humans.size() ;i ++){
            
            if(humans[i].y <= 628 ){
                
                float dis = ofDist(humans[i].x, humans[i].y, 640, 460);
                double rad = atan2(460-humans[i].y, 640-humans[i].x);
                
                float meY = sin(rad)*dis/5;
                float meX = cos(rad)*dis/5;
                
                humans[i].set(humans[i].x+meX,humans[i].y+meY);
                
                
            }
            else if(humans[i].y > 628 || humans[i].y < 812){
                
                float dis = ofDist(humans[i].x, humans[i].y, 640, 460);
                double rad = atan2(460-humans[i].y, 640-humans[i].x);
                
                float meX = cos(rad)*dis/5;
                
                humans[i].set(humans[i].x+meX,humans[i].y);
                
            }
            else if (humans[i].y >= 812 ){
                float dis = ofDist(humans[i].x, humans[i].y, 640, 980);
                double rad = atan2(980-humans[i].y, 640-humans[i].x);
                
                float meY = sin(rad)*dis/5;
                float meX = cos(rad)*dis/5;
                
                humans[i].set(humans[i].x+meX,humans[i].y+meY);
            }
            
        }
        
        
        frame ++;
        


        
    }
    
    
    
    
    
    
    void draw(void){
        for(int i = 0 ;i < humans.size() ;i ++){
            
        
        if(ofDist(humans[i].x, humans[i].y, ranPos.x, ranPos.y)<= 100){
            ranPos.set(ofRandom(100,1180),ofRandom(100,1340));
            pura.play();
        }
        if(ofDist(humans[i].x, humans[i].y, ranPoss.x, ranPoss.y)<= 100){
            ranPoss.set(ofRandom(100,1180),ofRandom(100,1340));
            pui.play();
        }
        if(ofDist(humans[i].x, humans[i].y, ranPosss.x, ranPosss.y)<= 100){
           ranPosss.set(ofRandom(100,1180),ofRandom(100,1340));
            paun.play();
        }
        
        }
        //ranPos.set(ofRandom(ofGetWidth()),ofRandom(ofGetHeight()));
        
        ofPushMatrix();
        ofSetColor(255,255,30);
        ofSetCircleResolution(5);
        ofTranslate(ranPos.x, ranPos.y);
        ofRotate(frame);
        ofDrawCircle(0, 0, 30);
        ofPopMatrix();
        
        
        ofPushMatrix();
        ofSetColor(30,255,255);
        ofSetCircleResolution(4);
        ofTranslate(ranPoss.x, ranPoss.y);
        ofRotate(frame);
        ofDrawCircle(0, 0, 34);
        ofPopMatrix();
        
        
        
        ofPushMatrix();
        ofSetColor(255,100,255);
        ofSetCircleResolution(3);
        ofTranslate(ranPosss.x, ranPosss.y);
        ofRotate(frame);
        ofDrawCircle(0, 0, 34);
        ofPopMatrix();
    }
        
        
    

    
    
    
    
    
    
    
    
    
};
//*/

#endif /* defined(__mySketch__tkm001__) */
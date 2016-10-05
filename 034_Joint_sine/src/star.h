//
//  star.h
//  emptyExample
//
//  Created by asamiTakami on 2016/09/07.
//
//

#ifndef __emptyExample__star__
#define __emptyExample__star__

#include "Base.h"




class star :public Base{
    
private:
    ofVec3f nana[8];
    ofVec3f hokuto[8];
    
    ofPoint hosis[500];
    
    vector < ofPoint > humans; //vector 可変長配列　超便利配列！
    
    
public:
    
    
    
    
    
    void setup(void){
        
        ofSetBackgroundColor(0);
        
        
        
        ofVec2f nana_;
        nana_.set(1280/4, 1440/4);
        
        for(int n_i = 0; n_i < 8 ; n_i ++){
            
            nana_.x += ofRandom(100);
            nana_.y += ofRandom(100);
            
            nana[n_i] = nana_;
            
        }
        for (int hosi = 0; hosi < 500; hosi ++) {
            hosis[hosi].set(ofRandom(1280), ofRandom(1440));
        }
        
        humans.resize(1024);
        humans.clear();
        
    }
    
    
    
    
    
    
    
    
    void osc(vector<ofxOscMessage> &m){
        
        humans.clear();
        for(int i = 0 ; i < m.size() ; ++ i){
            
            if(m[i].getAddress() == "/human"){
                humans.push_back( ofVec3f( m[i].getArgAsInt32(0) , m[i].getArgAsInt32(1) , m[i].getArgAsInt32(2)));
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
        
        
        
        
        for(int i = 0 ;i < humans.size() ;i ++){
            if(ofDist(nana[0].x,nana[0].y ,humans[i].x,humans[i].y)<=60){
                
                for (int n_i = 0; n_i <= 7; n_i++) {
                    nana[n_i] = nana[n_i+1];
                }
                nana[7].x = nana[6].x + ofRandom(-200,200);
                nana[7].y = nana[6].y + ofRandom(-200,200);
                
                while (ofDist(nana[7].x, nana[7].y, nana[6].x, nana[6].y) <= 50
                       || ofDist(nana[7].x, nana[7].y, nana[5].x, nana[5].y) <= 150
                       ||ofDist(nana[7].x, nana[7].y, nana[4].x, nana[4].y) <= 150
                       ||nana[7].x  >= 1180||nana[7].y  >= 1340
                       ||nana[7].x  <= 100
                       ||nana[7].y  <= 100){
                    
                    nana[7].x = nana[6].x + ofRandom(-200,200);
                    nana[7].y = nana[6].y + ofRandom(-200,200);
                }
                
            }
            
            if(ofDist(nana[7].x,nana[7].y ,humans[i].x,humans[i].y)<=60){
                
                
                
                for (int w = 7; w >= 0; w--) {
                    nana[w] = nana[w-1];
                }
                nana[0].x = nana[1].x + ofRandom(-300,300);
                nana[0].y = nana[1].y + ofRandom(-300,300);
                
                while (ofDist(nana[0].x, nana[0].y, nana[1].x, nana[1].y) <= 100
                       || ofDist(nana[0].x, nana[0].y, nana[2].x, nana[2].y) <= 200
                       ||ofDist(nana[0].x, nana[0].y, nana[3].x, nana[3].y) <= 200
                       ||nana[0].x  >= 1180||nana[0].y  >= 1340
                       ||nana[0].x  <= 100
                       ||nana[0].y  <= 100){
                    
                    nana[0].x = nana[1].x + ofRandom(-300,300);
                    nana[0].y = nana[1].y + ofRandom(-300,300);
                }
                
               // if(nana[0].x  <= 0){nana[0].x += 1280;}
                //if(nana[0].y  <= 0){nana[0].y += 1440;}
            }
            
            
            
        }
        
        

        
        
    }
    
    
    
    
    
    
    void draw(void){
        
        ofPath line = ofPath();
        line.setStrokeColor( ofColor(255));
        line.setFilled(false);
        line.setStrokeWidth( 1 );
        line.moveTo( nana[0]);        for (int b = 1 ; b <= 7; b++) {
            line.lineTo( nana[b] );
        }
        line.draw();
        line.close();
        
        
        
        
        //ofDrawCircle(nana[0].x ,nana[0].y,5);
        //ofDrawCircle(nana[7].x ,nana[7].y,5);
        
        
        ofSetCircleResolution(32);
        ofSetColor(255);
        for(int n_i = 1; n_i <= 6 ; n_i ++){
            
            ofDrawCircle(nana[n_i].x ,nana[n_i].y,8);
            
        }
        
        
        
        for (int hosi = 0; hosi < 500; hosi ++) {
            ofDrawCircle(hosis[hosi], ofRandom(1.0f));
        }
        
        
        
        
        
        
        ofSetColor(255);
        ofPushMatrix();
        ofTranslate(nana[0].x, nana[0].y);
        ofRotate(ofGetFrameNum(), 0, 0, 5);
        ofSetCircleResolution(5);
        ofSetColor(0, 250, 220);
        ofDrawCircle(0, 0, 30);
        ofPopMatrix();
        
        
        ofPushMatrix();
        ofTranslate(nana[7].x, nana[7].y);
        ofRotate(ofGetFrameNum(), 0, 0, 5);
        ofSetCircleResolution(5);
        ofSetColor(250, 220, 0);
        ofDrawCircle(0, 0, 30);
        ofPopMatrix();
//        
//         for(int i = 0 ;i < humans.size() ;i ++){
//             ofSetCircleResolution(32);
//             ofSetColor(200, 250, 0);
//             ofDrawCircle(humans[i].x,humans[i].y, 50);
//         }
      
    }
    
    
    
    
    
    
    
    
    
    
    
    
    
};

#endif /* defined(__emptyExample__star__) */

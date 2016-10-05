//
//  marumaru.h
//  emptyExample
//
//  Created by asamiTakami on 2015/01/01.
//
//

#ifndef emptyExample_marumaru_h
#define emptyExample_marumaru_h

#include "Base.h"




class marumaru :public Base{
    
private:
    
    
    vector < ofVec3f > humans; //vector 可変長配列　超便利配列！
    
    
    
    
    
    
public:
    
    
    
    
    //------------------------------------------------------------
    void setup(void){
        
        
        
        ofSetBackgroundColor(0);
        
        humans.resize(1024);
        humans.clear();
        
    }
    
    
    
    
    
    
    //------------------------------------------------------------
    
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
    
    
    //------------------------------------------------------------
    
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
        
        
    }
    
    
    
    
    
    //------------------------------------------------------------
    void draw(void){
        ofEnableBlendMode(OF_BLENDMODE_ADD);
        
         for(int i = 0 ;i < humans.size();i ++){
             
             ofFill();
             ofSetColor ( 250 , 255 ,255 ,100);
             ofDrawCircle(humans[i].x, humans[i].y , 5 );
             ofNoFill();
             ofSetColor ( 250, 255 ,255 ,255);
             ofDrawCircle( humans[i].x, humans[i].y , 5 );
         }
        
        if(humans.size() >= 1){
            for(int i = 0 ;i < humans.size()-1 ;i ++){
                for(int j = i ; j < humans.size();j++){
                    float Ax = humans[i].x;
                    float Ay = humans[i].y;
                    float Bx = humans[j].x;
                    float By = humans[j].y;
                    
                    float Rx = ( Ax + Bx ) / 2;
                    float Ry = ( Ay + By ) / 2;
                    
                    ofFill();
                    ofSetColor ( 0 , 0 ,250 ,100);
                    ofDrawCircle( Rx , Ry , ofDist( Ax , Ay , Rx ,Ry ) );
                    ofNoFill();
                    ofSetColor ( 0 , 0 ,250 ,255);
                    ofDrawCircle( Rx , Ry , ofDist( Ax , Ay , Rx ,Ry ) );
                    
                }
            }
        }
        
       /* if(humans.size() >= 2){
            for(int i = 0 ;i < humans.size()-2 ;i ++){
                for(int j = i+1 ; j < humans.size()-1;j++){
                    for(int s = j+1 ; s < humans.size();s++){
                        
                        float Ax = humans[i].x;
                        float Ay = humans[i].y;
                        float Bx = humans[j].x;
                        float By = humans[j].y;
                        float Cx = humans[s].x;
                        float Cy = humans[s].y;
                        
                        ofVec2f R1;
                        R1.set(( Ax + Bx ) / 2,( Ay + By ) / 2);
                        ofVec2f R2;
                        R2.set(( Cx + Bx ) / 2,( Cy + By ) / 2);
                        
                        double R1rad = atan2(Bx-Ax, By-Ay);
                        double R2rad = atan2(Bx-Cx, By-Cy);
                        
                        double a = cos(R1rad);
                        double A = cos(R2rad);
                        
                        
                        double b = R1.y-a*R1.x;
                        double B = R2.y-A*R2.x;
                        
                        ofVec2f R3;
                        R3.set((B-b)/(a-A),(a*B-A*b)/a-A);
                        
                        
                        ofNoFill();
                        ofSetColor ( 250 , 250 , 0 );
                        ofDrawCircle(R3, ofDist( Ax , Ay , R3.x,R3.y ) );
                        
                        
                    }
                }
                
            }
        }*/
        if(humans.size() >= 2){
            for(int i = 0 ;i < humans.size()-2 ;i ++){
                for(int j = i+1 ; j < humans.size()-1;j++){
                    for(int s = j+1 ; s < humans.size();s++){
     
        
                        float x1 = humans[i].x;
                        float y1 = humans[i].y;
                        float x2 = humans[j].x;
                        float y2 = humans[j].y;
                        float x3 = humans[s].x;
                        float y3 = humans[s].y;
        
        double G,Xc,Yc,Xd,Yd,Xe,Ye;
        
        
        
        
        G=( y2*x1-y1*x2 +y3*x2-y2*x3 +y1*x3-y3*x1 );
        Xc= ((x1*x1+y1*y1)*(y2-y3)+(x2*x2+y2*y2)*(y3-y1)+(x3*x3+y3*y3)*(y1-y2))/(2*G);
        Yc=-((x1*x1+y1*y1)*(x2-x3)+(x2*x2+y2*y2)*(x3-x1)+(x3*x3+y3*y3)*(x1-x2))/(2*G);
        
        Xd=(((x1*x1+y1*y1)-(x2*x2+y2*y2))*(y2-y3)-((x2*x2+y2*y2)-(x3*x3+y3*y3))*(y1-y2))/(2*((x1-x2)*(y2-y3)-(x2-x3)*(y1-y2)));
        Yd=(((y1*y1+x1*x1)-(y2*y2+x2*x2))*(x2-x3)-((y2*y2+x2*x2)-(y3*y3+x3*x3))*(x1-x2))/(2*((y1-y2)*(x2-x3)-(y2-y3)*(x1-x2)));
        
        G=2 * sqrt( (x1 - Xc) * (x1 - Xc) + (y1 - Yc) * (y1 - Yc) );
        
        
        ofFill();
        ofSetCircleResolution(32);
        ofSetColor ( 0 ,250  , 0 ,100);
        ofDrawCircle(Xc,Yc,G/2);
                        ofNoFill();
                        ofSetCircleResolution(32);
                        ofSetColor ( 0 ,250  , 0 ,255);
                        ofDrawCircle(Xc,Yc,G/2);
            
            
                    }}}}
    
    
    
     ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    }
};

#endif

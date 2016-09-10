//
//  dot.h
//  emptyExample
//
//  Created by asamiTakami on 2016/09/07.
//
//

#ifndef emptyExample_dot_h
#define emptyExample_dot_h

#include "Base.h"




class dot :public Base{
    
private:
    vector < ofVec3f > humans; //vector 可変長配列　超便利配列！
    vector <int> col ;
    vector <int> bchange;
    vector <int> bchange_;
    
    int KANKAKU;
    
public:
    
    
    
    
//------------------------------------------------------------
void setup(void){
    
    KANKAKU = 2;
    
    ofSetBackgroundColor(0);
    
    for(int t_i =0; t_i < KANKAKU*KANKAKU*8*9; t_i++){
        col.push_back(0);
        bchange.push_back(0);
        bchange_.push_back(0);
    }
    
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
    
    int yoko = KANKAKU * 8;
    int tate = KANKAKU * 9;
    
    int aidaX = 1280/yoko;
    int aidaY = 1440/tate;
    
    
    for(int t_q = 0 ; t_q < yoko ; t_q++){
        for(int t_w = 0 ; t_w < tate ; t_w++){
            bchange[yoko*t_w+t_q] = 0;
            
            for(int h = 0 ;h < humans.size() ;h ++){
                
                
                if (ofDist(t_q*aidaX + aidaX/2, t_w*aidaY + aidaY/2, humans[h].x, humans[h].y)<=40) bchange[yoko*t_w+t_q] = 1;
                
            }
            
            if (bchange[yoko*t_w+t_q] != bchange_[yoko*t_w+t_q] && bchange[yoko*t_w+t_q] == 1){
                col[yoko*t_w+t_q] = col[yoko*t_w+t_q] + 1;
                if(col[yoko*t_w+t_q]>=4)col[yoko*t_w+t_q]=0;
            }
            ofColor c;
            if(col[yoko*t_w+t_q] ==0)c.setHsb(45,200,0);
            else if(col[yoko*t_w+t_q] ==1)c.setHsb(240,200,250);
            else if(col[yoko*t_w+t_q] ==2)c.setHsb(120,200,200);
            else if(col[yoko*t_w+t_q] ==3)c.setHsb(150,250,200);
            
            ofSetColor(c);
            ofDrawCircle(t_q*aidaX + aidaX/2 ,t_w*aidaY + aidaY/2,30 );
            
            
            bchange_[yoko*t_w+t_q] = bchange[yoko*t_w+t_q];
            
        }
        
    }
    
    
      //  for(int i = 0 ;i < humans.size() ;i ++){}
    
    
    
}
    
    
    
    
    
    
    
    
    
    
    
    
    
};
#endif

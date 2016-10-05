//
//  sinsin.h
//  emptyExample
//
//  Created by IAMAS iMac2015-1 on 2016/09/17.
//
//

#ifndef sinsin_h
#define sinsin_h
class sinsin :public Base{
    
private:
    vector < ofVec3f > humans; //vector 可変長配列　超便利配列！
    vector <ofSoundPlayer> sinW;
    
    float vol;
    
public:
void setup (void){
    
    sinW.resize(32);
    //for(int i = 0 ; i < sinW.size() ; ++ i){
    for(int i = 0 ; i < 8 ; ++ i){   //四人用です
        
        //audioをロード、ループ、ボリューム、再生
        sinW[i].load("sound/440B.wav");
        sinW[i].setMultiPlay(true);
        sinW[i].setLoop(true);
        sinW[i].setVolume(0);
        //sinW[i].setVolume(0.8f);
        sinW[i].play();
        
        
    }
    
    
    humans.resize(1024);
    humans.clear();
    
 
    ofBackground(0);
    ofFill;
    
    //sender.setup(HOST,PORT);
    
    
    
    
    
    ofSetVerticalSync(true);
    ofSetCircleResolution(32);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    

}

//-----------------------------------------------------
void update (void){

    
    ofBackground(0);
    // update the sound playing system:
    
    ofSoundUpdate();
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


    void draw (void){
        ofSetColor(255);
        
        

        
        
        for(int i = 0 ;i < humans.size() ;i ++){
            if(humans.size() < 8){
                float Xvol = ofMap(humans[i].x, 0,  ofGetWidth(), 0.2f, 1.0f);
                float Ypch = 2.0f-ofMap(humans[i].y, 0, ofGetHeight(), 0, 2.0f);
                
                
                sinW[i].setVolume(1.0f * Xvol);
                sinW[i].setSpeed(1.0f * Ypch);
            }
            
            
        }
        for(int i = humans.size() ; i < 8 ; i++){
        sinW[i].setVolume(0.0f);
        
        }
        
        
        
        //  ----------   visual   --------------------------------------------------------
        
        ofBeginShape();
        
        
        
        ofVertex(640,0);
        
        for(int sinCount = 0 ; sinCount < 400 ; sinCount ++){
            
            float rad = 0;
            
            for(int i = 0 ;i < humans.size() ;i ++){
                
                rad +=cos(float(sinCount)/ofMap(humans[i].y,0,ofGetHeight(),5,100) * PI)*ofMap(humans[i].x,0,ofGetWidth(),0.01f,2.0f);
                
            }
            
 
            ofVertex(640 +  rad*50 , 5*sinCount);
            
        }
        ofVertex(640,2000);
        
        ofEndShape();
    }


};


#endif /* sinsin_h */

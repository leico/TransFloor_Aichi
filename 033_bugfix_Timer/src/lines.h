//
//  mydraw.h
//  emptyExample
//
//  Created by LIFE_MAC25  on 2015/12/01.
//
//　　lines

#ifndef lines_h
#define lines_h


#include "Base.h"

class lines : public Base{
    
    vector <ofPoint> humans; //めっちゃ便利配列
    float * fftSmoothed;
    int nBandsToGet;
    
    ofSoundPlayer synth;
    ofSoundPlayer snare;

    
    ofVec2f pos[100][200];
    
    
public:
    
    void setup (void){
        ofBackground(0);
        
        fftSmoothed = new float[8190];
        for(int i = 0; i < 8190; i++){ //8190
            fftSmoothed[i]=0;
        }
        nBandsToGet = 1;
        
        //Audioをロード
        synth.load("sound/4synth_bip.wav");
        synth.setVolume(0.8f);
        synth.setLoop(true);
        synth.play();
        
        snare.load("sound/5snare_bip.wav");
        snare.setVolume(0.8f);
        snare.setLoop(true);
        snare.play();
        
        
        
        for(int x = 0 ; x < 100 ; ++ x ){
            for(int y = 0 ; y < 200 ; ++y){
                pos[x][y].x = x * 101; //円のxの間隔
                pos[x][y].y = y * 100; //円のyの間隔
            }
        }

    }
//-----------------------------------------------------
    void update (void){
        
        ofBackground(0,0,0);
        
        // update the sound playing system:
        ofSoundUpdate();
        
        
        float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
        for (int i = 0; i < nBandsToGet; i++){
            
            // take the max, either the smoothed or the incoming:
            if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
            
            // let the smoothed calue sink to zero:
            fftSmoothed[i] *= 0.5f;
            
        }

    }
//-----------------------------------------------------
    void osc (vector <ofxOscMessage> &m){
        humans.resize( m.size());
        // /human x y z
        
        int j = 0;
        for(int i = 0; i < m.size() ; ++ i){
        
            if(m[i].getAddress() == "/human"){
                humans[j].x = m[i].getArgAsInt32(0);
                humans[j].y = m[i].getArgAsInt32(1);
                humans[j].z = m[i].getArgAsInt32(2);
                
                ++ j;
            }
        }
    
    }
//------------------------------------------------------
    void draw (void){
        
        float vv = fftSmoothed[0];
        cout << vv << endl;
    
          //人が入ってきた時
        for(int i = 0 ; i < humans.size(); ++ i ){


        
        for(int x = 0 ; x < 20 ; x ++ ){
            for(int y = 0 ; y < 20 ; y ++){
                
                ofSetColor(255);
                glLineWidth(1 + vv*300);
                ofDrawLine(pos[x][y].x + ofGetWidth()/2  - 1*humans[i].x,
                           pos[x][y].y + ofGetHeight()/2 - 1*humans[i].y,
                           pos[x][y].x + vv*150,                pos[x][y].y + vv*150);
            
                ofDrawLine(-pos[x][y].x - vv*350 ,         - pos[x][y].y ,
                           -pos[x][y].x + vv*150,          -pos[x][y].y + vv*150);

            }
        }
          
        }
      


}
};

#endif /* mydraw_h */

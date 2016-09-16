//
//  origami.h
//  emptyExample
//
//  Created by LIFE_MAC25  on 2016/09/06.
//
//

#ifndef origami_h
#define origami_h
#include "Base.h"

class origami : public Base{
    
    
    vector< ofPoint > humans;
  
    
public:
  
  const static int XX   = 100;
  const static int YY  =  100;
    ofVec2f oripos[XX][YY];
  
  
    float NGR  = 100;
    float NGB  = 100;
    float NGG  = 100;
    float rrr = 0;
    
    /* ============================================================ *
     * setup(void)                                                  *
     * ============================================================ */
    void setup(void){
        
        humans.resize(1024);
        humans.clear();
        
        
      for(int x = 0 ; x < XX ; ++ x ){
        for(int y = 0 ; y < YY ; ++y){
          oripos[x][y].x = x * 300; //円のxの間隔
          oripos[x][y].y = y * 300; //円のyの間隔
        }
      }
      

    }
  
    /* ============================================================ *
     * update(void)                                                 *
     * ============================================================ */
    void update(void){
    ofSetBackgroundColor(0);
    
    }
    
    /* ============================================================ *
     * osc(void)                                                    *
     * ============================================================ */
    void osc(vector<ofxOscMessage> &m){
        
        humans.clear();
        
        for(int i = 0 ; i < m.size() ; ++ i){
            if(m[i].getAddress() == "/human"){
                
                humans.push_back(
                                 ofPoint(
                                         m[i].getArgAsInt32(0)
                                         , m[i].getArgAsInt32(1)
                                         , m[i].getArgAsInt32(2)
                                         )
                                 );
            }
        }
        
    }
    /* ============================================================ *
     * draw(void)                                                   *
     * ============================================================ */
    void draw(void){
        
        

      ofColor c ;
      c.setHsb(256, 0, 255, 100);
      
      
      ofSetColor(c);

      

        for(int x = 0 ; x < 100 ; x ++ ){
            for(int y = 0 ; y < 100 ; y ++){
                
                
 
                


              for(int i = 0 ; i < humans.size() ; ++ i){
                
                float ori1x = oripos[x][y].x;
                float ori1y = oripos[x][y].y;
                
                float ori2x = oripos[x][y].x + (ofGetWidth()/2  - humans[i].x)/2;
                float ori2y = oripos[x][y].y + (ofGetWidth()/2  - humans[i].y)/2;
                
                float ori3x = oripos[x][y].x + (ofGetWidth()/2  - humans[i+1].x)/2;
                float ori3y = oripos[x][y].y + (ofGetHeight()/2 - humans[i+1].y)/2;
                
                
                
                
                    ofDrawTriangle(ori1x,ori1y,
                                   ori2x,ori2y,
                                   ori3x,ori3y);

                  
                                     
                    }
                }
                
        }
      
            
        }
        


  
  
  
};



#endif /* origami_h */

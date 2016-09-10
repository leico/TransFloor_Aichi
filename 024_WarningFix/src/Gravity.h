//
//  Gravity.h
//  emptyExample
//
//  Created by iamas_retina02 on 2015/12/03.
//
//

#ifndef Gravity_h
#define Gravity_h

class Gravity : public Base{

  const static int WIDTH   = 80;
  const static int HEIGHT  = 100;
  const static int PADDING = 200;

  ofVec2f circles[WIDTH][HEIGHT];

  vector<ofVec2f> humans;

  float power;

  public:

    void setup (void){

      power = 30000;

      humans.resize(1024);
      humans.clear();

    }
    void osc(vector<ofxOscMessage> &m){
      
      humans.clear();
      for(int i = 0 ; i < m.size() ; ++ i){

        if(m[i].getAddress() == "/human"){
          humans.push_back(
            ofVec2f(
                m[i].getArgAsInt32(0)
              , m[i].getArgAsInt32(1)
            )
          );
        }
      }
    }

    void update(void){


      //calicurate gravity field
      int lamdawidth  = (ofGetWidth () + PADDING * 2) / WIDTH;
      int lamdaheight = (ofGetHeight() + PADDING * 2) / HEIGHT;

      for(int y = 0 ; y < HEIGHT ; ++ y){
        for(int x = 0 ; x < WIDTH ; ++ x){

          //set basic position
          circles[x][y] = ofVec2f(-PADDING + lamdawidth * x, -PADDING + lamdaheight * y);

          for(int i = 0 ; i < humans.size() ; ++ i){

            //get distance and calcurate gravity
            float distance = circles[x][y].distance(humans[i]);
            float g        = power / (distance * distance);

            g = (g > 1) ? 1 : g;

            //pull circles
            circles[x][y].x -= (circles[x][y].x - humans[i].x) * g;
            circles[x][y].y -= (circles[x][y].y - humans[i].y) * g;
          }

        }
      }

    }

    void draw  (void){
      ofSetColor(255);
      for(int y = 0 ; y < HEIGHT ; ++ y)
        for(int x = 0 ; x < WIDTH ; ++ x)
          ofDrawCircle(circles[x][y], 3);
    }


};

#endif /* Gravity_h */

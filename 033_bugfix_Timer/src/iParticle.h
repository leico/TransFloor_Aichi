#pragma once
#include "ofMain.h"



//#define	SHAPE_CIRCLE = 0
//#define	SHAPE_TRIANGLE = 1
//#define	SHAPE_SQARE = 2

enum gravityMode{
    GRAVITY_MODE_ATTRACT = 0,
    GRAVITY_MODE_REPEL,
};

class iParticle{

	public:
		iParticle();
		
		//void setShape(int newShape);
        void setGravityMode(gravityMode newMode);
		void setAttractPoint( ofPoint attractPoint );

		void reset();
		void update();
		void draw();
        void resetCollor();
		
		ofPoint pos;
		ofPoint vel;
		ofPoint frc;
        ofPoint atrc;
		
		float drag; 
		float uniqueVal;
		float scale;
        ofColor shapeRGB;
        //int shape;
    
    
		gravityMode gMode;
    
    
    
		//shapeMode shape;
		
		//vector <ofPoint> * attractPoints;
};
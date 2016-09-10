#include "iParticle.h"

//------------------------------------------------------------------
iParticle::iParticle(){
	atrc = ofPoint( ofRandom(0, ofGetWidth()) , ofRandom(0, ofGetHeight() ));
    shapeRGB.r =ofRandom(0, 255);
    shapeRGB.g =ofRandom(0, 255);
    shapeRGB.b =ofRandom(0, 255);
    //shape = ofRandom(0, 3);
}
//------------------------------------------------------------------
void iParticle::resetCollor(){
    shapeRGB.r =ofRandom(0, 255);
    shapeRGB.g =ofRandom(0, 255);
    shapeRGB.b =ofRandom(0, 255);
}
//------------------------------------------------------------------
//void iParticle::setShape(int newShape){
//	shape = newShape;
//}
//------------------------------------------------------------------
void iParticle::setGravityMode(gravityMode newMode){
    gMode=newMode;
}

//------------------------------------------------------------------
void iParticle::setAttractPoint( ofPoint attractPoint ){
	atrc = attractPoint;
}

//------------------------------------------------------------------
void iParticle::reset(){
	//the unique val allows us to set properties slightly differently for each particle
	uniqueVal = ofRandom(-10000, 10000);
	
	pos.x = ofRandomWidth();
	pos.y = ofRandomHeight();
	
	vel.x = ofRandom(-3.9, 3.9);
	vel.y = ofRandom(-3.9, 3.9);
	
	frc   = ofPoint(0,0,0);
	
	scale = ofRandom(0.5, 1.0);
	

    drag  = ofRandom(0.95, 0.998);

}

//------------------------------------------------------------------
void iParticle::update(){


    if( gMode == GRAVITY_MODE_ATTRACT ){
        //ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
        frc = atrc-pos; // we get the attraction force/vector by looking at the mouse pos relative to our pos
        frc.normalize(); //by normalizing we disregard how close the particle is to the attraction point
        
        vel *= drag; //apply drag
        vel += frc * 0.6; //apply force
    }
    else if( gMode == GRAVITY_MODE_REPEL ){
        //ofPoint attractPt(ofGetMouseX(), ofGetMouseY());
        frc = atrc-pos;
        
        //let get the distance and only repel points close to the mouse
        float dist = frc.length();
        frc.normalize();
        
        vel *= drag;
        if( dist < 150 ){
            vel += -frc * 12.6; //notice the frc is negative
        }else{
            //if the particles are not close to us, lets add a little bit of random movement using noise. this is where uniqueVal comes in handy.
            frc.x = ofSignedNoise(uniqueVal, pos.y * 0.01, ofGetElapsedTimef()*0.2);
            frc.y = ofSignedNoise(uniqueVal, pos.x * 0.01, ofGetElapsedTimef()*0.2);
            vel += frc * 8.54;
        }
    }
	
	//2 - UPDATE OUR POSITION
	
	pos += vel; 
	
	
	//3 - (optional) LIMIT THE PARTICLES TO STAY ON SCREEN 
	//we could also pass in bounds to check - or alternatively do this at the ofApp level
	if( pos.x > ofGetWidth() ){
		pos.x = ofGetWidth();
		vel.x *= -1.0;
	}else if( pos.x < 0 ){
		pos.x = 0;
		vel.x *= -1.0;
	}
	if( pos.y > ofGetHeight() ){
		pos.y = ofGetHeight();
		vel.y *= -1.0;
	}
	else if( pos.y < 0 ){
		pos.y = 0;
		vel.y *= -1.0;
	}	
		
}

//------------------------------------------------------------------
void iParticle::draw(){
    ofSetColor(shapeRGB);

			
	ofDrawCircle(pos.x, pos.y, scale * 4.0);
}


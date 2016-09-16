//
//  kinectCV.hpp
//  emptyExample
//
//  Created by leico_system on 2015/11/26.
//
//

#ifndef kinectCV_hpp
#define kinectCV_hpp

#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"
#include "ofxJSON.h"

class KinectCV{

  public:
  enum DISPLAYMODE{
    COLOR = 0,
    GLAY,
    BINARY
  };

  private:

  ofxKinect kinect;

  ofxCvColorImage colorImage;

  ofxCvGrayscaleImage grayImage;
  ofxCvGrayscaleImage binaryImage;
  ofxCvContourFinder contourfinder;

  std :: vector<ofxOscMessage> humans;

  std :: string serial;

  unsigned char min_depth;
  unsigned char max_depth;

  int angle;

  int blur;

  int min_area;
  int max_area;

  ofRectangle cliparea;
  ofVec2f     size;

  bool vmirror;
  bool hmirror;

  DISPLAYMODE displaymode;

  bool secondary;

  public:

   KinectCV(void);
  ~KinectCV(void);

  const unsigned char MinDepth(void);
                 void MinDepth(const unsigned char min);

  const unsigned char MaxDepth(void);
                 void MaxDepth(const unsigned char max);
  
  const int  Angle(void);
        void Angle(const int _angle);

  const int  Blur(void);
        void Blur(const int _blur);

  const int  MinArea(void);
        void MinArea(const int min);

  const int  MaxArea(void);
        void MaxArea(const int max);

  const ofRectangle& ClipArea(void);
        void         ClipArea(const ofRectangle& area);

  const ofVec2f& Size(void);
        void     Size(const ofVec2f& _size);

  const bool VMirror(void);
        void VMirror(const bool mirror);
  
  const bool HMirror(void);
        void HMirror(const bool mirror);

  const DISPLAYMODE DisplayMode(void);
        void        DisplayMode(const DISPLAYMODE _displaymode);

  const bool Secondary(void);
        void Secondary(const bool _secondary);



  const unsigned char Depth(const int x, const int y);

  void setup (const std :: string &serial);
  void exit  (void);

  bool                 update           (void);
  ofxCvGrayscaleImage& update_dualscreen(void);
  
  void draw  (const int x = 0, const int y = 0);



  ofxOscMessage& osc(ofxOscMessage &m);



  const std :: vector<ofxOscMessage>& Humans(void);
  const std :: string SettingData(void);
        void          SettingData(const ofxJSON& data);

  protected:
  void Reconnect(void);
};

/* ========================================================= *
 * constructor / destructor                                  *
 * ========================================================= */
inline KinectCV ::  KinectCV(void){}
inline KinectCV :: ~KinectCV(void){}

/* ========================================================= *
 * void Reconnect                                            *
 * ========================================================= */
inline void KinectCV :: Reconnect(void){
  kinect.close();
  kinect.open(serial);
}

/* ========================================================= *
 * const unsigned char MinDepth(void)                        *
 *                void MinDepth(const unsigned char min)     *
 * ========================================================= */
inline const unsigned char KinectCV :: MinDepth(void)                   { return min_depth; }
inline                void KinectCV :: MinDepth(const unsigned char min){ min_depth = min;  }


/* ========================================================= *
 * const unsigned char MaxDepth(void)                        *
 *                void MaxDepth(const unsigned char max)     *
 * ========================================================= */
inline const unsigned char KinectCV :: MaxDepth(void)                   { return max_depth; }
inline                void KinectCV :: MaxDepth(const unsigned char max){ max_depth = max; }


/* ========================================================= *
 * const int  Angle(void)                                    *
 *       void Angle(const int _angle)                        *
 * ========================================================= */
inline const int  KinectCV :: Angle(void)            { return angle;   }
inline       void KinectCV :: Angle(const int _angle){
  angle = ofClamp(_angle, -30, 30); 
  kinect.setCameraTiltAngle(angle);
}


/* ========================================================= *
 * const int  Blur(void);                                    *
 *       void Blur(const int _blur);                         *
 * ========================================================= */
inline const int  KinectCV :: Blur(void)           { return blur;   }
inline       void KinectCV :: Blur(const int _blur){ blur = _blur;  } 


/* ========================================================= *
 * const int  MinArea(void);                                 *
 *       void MinArea(const int min);                        *
 * ========================================================= */
inline const int  KinectCV :: MinArea(void)         { return min_area; }
inline       void KinectCV :: MinArea(const int min){ 
  //findcontoursの数値は面積
  min_area = min * min * M_PI; 
} 


/* ========================================================= *
 * const int  MaxArea(void);                                 *
 *       void MaxArea(const int max);                        *
 * ========================================================= */
inline const int  KinectCV :: MaxArea(void)         { return max_area; }
inline       void KinectCV :: MaxArea(const int max){
  //findcontoursの数値は面積
  max_area = max * max * M_PI;  
}

/* ========================================================= *
 * const ofRectangle& ClipArea(void);                        *
 *       void         ClipArea(const ofRectangle& area);     *
 * ========================================================= */
inline const ofRectangle& KinectCV :: ClipArea(void)                   { return cliparea; }
inline void               KinectCV :: ClipArea(const ofRectangle& area){ cliparea = area; }

/* ========================================================= *
 * const ofVec2f& Size(void);                                *
 *       void     Size(const ofVec2f& area);                 *
 * ========================================================= */
inline const ofVec2f& KinectCV :: Size(void)                { return size;  }
inline       void     KinectCV :: Size(const ofVec2f& _size){
  size = _size; 

  if( binaryImage.bAllocated )
    binaryImage.resize( Size().x, Size().y );

}

/* ========================================================= *
 * const bool VMirror(void);                                 *
 *       void VMirror(const bool mirror);                    *
 * ========================================================= */
inline const bool KinectCV :: VMirror(void)             { return vmirror;   }
inline       void KinectCV :: VMirror(const bool mirror){ vmirror = mirror; }

/* ========================================================== *
 * const bool HMirror(void);                                  *
 *       void HMirror(const bool mirror);                     *
 * ========================================================== */
inline const bool KinectCV :: HMirror(void)             { return hmirror;   }
inline       void KinectCV :: HMirror(const bool mirror){ hmirror = mirror; }

/* =============================================================== *
 * const DISPLAYMODE DisplayMode(void);                            *
 *       void        DisplayMode(const bool _displaymode);         *
 * =============================================================== */
inline const KinectCV :: DISPLAYMODE KinectCV :: DisplayMode(void)                                      { return displaymode; }
inline       void                    KinectCV :: DisplayMode(const KinectCV :: DISPLAYMODE _displaymode){ displaymode = _displaymode; }

/* =============================================================== *
 * const bool Secondary(void);                                     *
 *       void Secondary(const bool _secondary);                    *
 * =============================================================== */
inline const bool KinectCV :: Secondary(void)                 { return secondary; }
inline       void KinectCV :: Secondary(const bool _secondary){ secondary = _secondary; }


/* =============================================================== *
 * const unsigned char Depth(void);                                *
 * =============================================================== */
inline const unsigned char KinectCV :: Depth(const int x, const int y){
  ofPixels pix = grayImage.getPixels();

  return pix[pix.getPixelIndex(x, y)];
}



/* ========================================================= *
 * void setup(const std :: string &serial)                   *
 * ========================================================= */
inline void KinectCV :: setup (const std :: string &_serial){
  serial = _serial;

  humans.resize(1024);
  humans.clear();

  MinDepth(70);
  MaxDepth(200);

  Angle(0);
  Blur (0);

  ClipArea( ofRectangle(0, 0, kinect.getWidth(), kinect.getHeight() ) );
  Size( ofVec2f(1280, 720) );
  
  MinArea(0);
  MaxArea(100);

  VMirror(false);
  HMirror(false);

  DisplayMode(DISPLAYMODE :: GLAY);
  Secondary(false);

  kinect.init();
  kinect.open(_serial);

  colorImage .allocate( kinect.getWidth(), kinect.getHeight() );
  grayImage  .allocate( kinect.getWidth(), kinect.getHeight() );
  binaryImage.allocate( Size().x, Size().y );


}




/* ========================================================= *
 * bool update(void)                                         *
 * ========================================================= */
inline bool KinectCV :: update(void){

  if( ! kinect.isConnected()){
    kinect.close();
    kinect.init();
    kinect.open(serial);
    return false;
  }
  
  kinect.update();
  
  if(kinect.isFrameNew()){
    
    int width  = kinect.getWidth();
    int height = kinect.getHeight();
    
    if(DisplayMode() == DISPLAYMODE :: COLOR){
      colorImage.setFromPixels( kinect.getPixels() );
      colorImage.setROI(cliparea);
      colorImage.setFromPixels( colorImage.getRoiPixels() );
      
      colorImage.resize(Size().x, Size().y);
      colorImage.mirror( VMirror(), HMirror() );
    }
    
    //get kinect depth data and noise reduction
    grayImage.setFromPixels( kinect.getDepthPixels() );
    grayImage.blur(blur);
    
    //set Rectangle of Interest and clip Rectangle of Interest
    grayImage.setROI(cliparea);
    grayImage.setFromPixels( grayImage.getRoiPixels() );
    
    //resize display size
    grayImage.resize( Size().x, Size().y );
    
    //vertical horizonal mirror
    grayImage.mirror(VMirror(), HMirror());
    
    binaryImage = grayImage;
    
    //binarization
    {
      ofPixels& pixels = binaryImage.getPixels();
      for(int i = 0; i < pixels.size() ; ++ i)
        pixels [i] = (pixels[i] <  MinDepth() || pixels[i] > MaxDepth() ) ? 0 : 255;
    }
    
    //contourfinder
    contourfinder.findContours(binaryImage, MinArea(), MaxArea(), 200, false);
    
    humans.clear();
    
    for(int i = 0, size = contourfinder.blobs.size() ; i < size ; ++ i){
      
      //get contour center position
      ofPoint pos = contourfinder.blobs.at(i).centroid;
      
      ofPixels& pixels = grayImage.getPixels();
      
      //create OSC Message
      ofxOscMessage m;
      m.setAddress("/human");
      m.addIntArg(pos.x);
      m.addIntArg( Secondary() ? (Size().y + Size().y - pos.y) : pos.y );
      m.addIntArg( pixels[ pixels.getPixelIndex(pos.x, pos.y) ] );
      
      //store for humans
      humans.push_back(m);
      
      //ofLogWarning() << "nBlobs:" << humans.size();
      
    }
    return true;
    
  }
  
  return false;
}
/* ========================================================= *
 * ofxCvGrayscaleImage& update_dualscreen(void)              *
 * ========================================================= */
inline ofxCvGrayscaleImage& KinectCV :: update_dualscreen(void){
  
  if( ! kinect.isConnected()){
    kinect.close();
    kinect.init();
    kinect.open(serial);
    return binaryImage;
  }

  kinect.update();
  
  if(kinect.isFrameNew()){
    
    int width  = kinect.getWidth();
    int height = kinect.getHeight();
    
    if(DisplayMode() == DISPLAYMODE :: COLOR){
      colorImage.setFromPixels( kinect.getPixels() );
      colorImage.setROI(cliparea);
      colorImage.setFromPixels( colorImage.getRoiPixels() );
      
      colorImage.resize(Size().x, Size().y);
      colorImage.mirror( VMirror(), HMirror() );
    }
    
    //get kinect depth data and noise reduction
    grayImage.setFromPixels( kinect.getDepthPixels() );
    grayImage.blur(blur);
    
    //set Rectangle of Interest and clip Rectangle of Interest
    grayImage.setROI(cliparea);
    grayImage.setFromPixels( grayImage.getRoiPixels() );
    
    //resize display size
    grayImage.resize( Size().x, Size().y );
    
    //vertical horizonal mirror
    grayImage.mirror(VMirror(), HMirror());
    
    binaryImage = grayImage;
    
    //binarization
    {
      ofPixels& pixels = binaryImage.getPixels();
      for(int i = 0 ; i < pixels.size() ; ++ i)
        pixels [i] = (pixels[i] <  MinDepth() || pixels[i] > MaxDepth() ) ? 0 : 255;
    }
  }
  
  return binaryImage;
  
}







/* ========================================================= *
 * void exit(void)                                           *
 * ========================================================= */
inline void KinectCV :: exit(void){
  grayImage  .clear();
  binaryImage.clear();

  Angle(0);
  kinect.close();
  kinect.clear();
}

/* ========================================================= *
 * void draw(void)                                           *
 * ========================================================= */
inline void KinectCV :: draw(const int x, const int y){

  int width  = Size().x;
  int height = Size().y;
  ofVec2f center(x + width / 2, y + height / 2);

  ofSetColor(255);

  switch( DisplayMode() ){
    case DISPLAYMODE :: COLOR : colorImage .draw(x, y, Size().x, Size().y); break;
    case DISPLAYMODE :: GLAY  : grayImage  .draw(x, y, Size().x, Size().y); break;
    case DISPLAYMODE :: BINARY: binaryImage.draw(x, y, Size().x, Size().y); break;
  }

  contourfinder.draw(x, y, Size().x, Size().y);

  ofSetColor(255);
  ofDrawCircle( center, sqrt(MaxArea() / M_PI) );
  ofSetColor(0);
  ofDrawCircle( center, sqrt(MinArea() / M_PI) );

}

/* ========================================================= *
 * ofxOscMessage& osc(ofxOscMessage &m)                      *
 * ========================================================= */
inline ofxOscMessage& KinectCV :: osc(ofxOscMessage &m){

  
  if(m.getAddress() == "/kinect/mindepth"){
    MinDepth( m.getArgAsInt32(0) );
    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/maxdepth"){
    MaxDepth( m.getArgAsInt32(0) );
    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/angle"){
    Angle( m.getArgAsInt32(0) );
    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/blur"){
    Blur( m.getArgAsInt32(0) );
    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/minarea"){
    MinArea( m.getArgAsInt32(0) );
    m.clear();
    return m;

  }

  if(m.getAddress() == "/kinect/maxarea"){
    MaxArea( m.getArgAsInt32(0) );
    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/cliparea"){
    ClipArea(
      ofRectangle(
          m.getArgAsInt32(0)
        , m.getArgAsInt32(1)
        , m.getArgAsInt32(2)
        , m.getArgAsInt32(3)
      )
    );

    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/resize"){
    Size(
      ofVec2f(
          m.getArgAsInt32(0)
        , m.getArgAsInt32(1)
      )
    );

    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/vmirror"){
    VMirror( m.getArgAsInt32(0) == 1 );
    
    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/hmirror"){
    HMirror( m.getArgAsInt32(0) == 1 );

    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/displaymode"){
    
    DisplayMode( static_cast<DISPLAYMODE>( m.getArgAsInt32(0) ) );
    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/secondary"){
    Secondary(m.getArgAsInt32(0) == 1);
    m.clear();
    return m;
  }

  if(m.getAddress() == "/kinect/reconnect"){
    
    Reconnect();

    m.clear();
    return m;
  }

  return m;
}

/* ========================================================= *
 * const std :: vector<ofxOscMessage>& Humans()              *
 * ========================================================= */
inline const std :: vector<ofxOscMessage>& KinectCV :: Humans(void){
  return humans;
}

/* ========================================================= *
 * const std :: string SettingData()                         *
 * ========================================================= */
inline const std :: string KinectCV :: SettingData(void){
  
  ofxJSON json;

  json[serial]["depth"]["min"]  = MinDepth     ();
  json[serial]["depth"]["max"]  = MaxDepth     ();
  json[serial]["angle"]         = Angle        ();
  json[serial]["blur"]          = Blur         ();
  json[serial]["area"]["min"]   = int( roundf( sqrt( MinArea() / M_PI ) ) );
  json[serial]["area"]["max"]   = int( roundf( sqrt( MaxArea() / M_PI ) ) );
  json[serial]["clip"]          = ofxJSON :: Encode( ClipArea() );
  json[serial]["size"]          = ofxJSON :: Encode( Size() );
  json[serial]["mirror"]["v"]   = VMirror      ();
  json[serial]["mirror"]["h"]   = HMirror      ();
  json[serial]["displaymode"]   = static_cast<int>( DisplayMode() );
  json[serial]["secondary"]     = Secondary    ();

  return json.getRawString();

}

/* ========================================================= *
 * void SettingData(const ofxJSON& data)                     *
 * ========================================================= */
inline void KinectCV :: SettingData(const ofxJSON& data){

  if(data[serial].isNull()) return;
  
  MinDepth     ( static_cast<unsigned char>(data[serial]["depth"]["min"].asUInt()) );
  MaxDepth     ( static_cast<unsigned char>(data[serial]["depth"]["max"].asUInt()) );
  Angle        ( data[serial]["angle"]        .asInt() );
  Blur         ( data[serial]["blur"]         .asInt() );
  MinArea      ( data[serial]["area"]["min"]  .asInt() );
  MaxArea      ( data[serial]["area"]["max"]  .asInt() );
  ClipArea     ( ofxJSON :: Decode<ofRectangle>( data[serial]["clip"] ) );
  Size         ( ofxJSON :: Decode<ofVec2f>    ( data[serial]["size"] ) );
  VMirror      ( data[serial]["mirror"]["v"]  .asBool() );
  HMirror      ( data[serial]["mirror"]["h"]  .asBool() );
  DisplayMode  ( static_cast<DISPLAYMODE>( data[serial]["displaymode"].asInt() ) );
  Secondary    ( data[serial]["secondary"]    .asBool() );


  std :: cout << SettingData() << std :: endl;
  
}



#endif /* kinectCV_hpp */

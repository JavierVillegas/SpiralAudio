#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "TheEllipse.h"
#define MaxEllip 1000
#define Nx 640
#define Ny 480
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    // Ellipses
    void ImageToEllipseList(cv::Mat TheInput,int NPlanes);
    void PlotEllipses(vector<TheEllipse> ElliVec,ofRectangle RectLimits);
    void PlotEllipNoFill(vector<TheEllipse> ElliVec,ofRectangle RectLimits);
    void PlotEllipPolligon(vector<TheEllipse> ElliVec,ofRectangle RectLimits);
    void EllipseAudio(vector<TheEllipse> ElliVec);
    void CoherentEllipses();
    void audioIn(float * input, int bufferSize, int nChannels);
    
    // Spiral
    
    void PlotSpiral();
 
    ofxCvColorImage		colorImg;// Basic Image for reading
        ofVideoGrabber vidGrabber;
    cv::Mat TheInputRGB;
    cv::Mat TheInputGray;
    // List of ellipse Parameters
    vector<TheEllipse> TheTargetsEllipses;
    vector<TheEllipse> TheCoherentEllipses;
    // Vectors of coherent Ellip positions and
    // Velocities
    TheEllipse TheObjectsEllip[MaxEllip];
    TheEllipse TheVelocitiesEllip[MaxEllip];
    // Audio variables
    

    //Audio
    ofSoundStream soundStream;
    float CurrentEnergy;
		
};

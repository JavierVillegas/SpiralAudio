#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(Nx, Ny);
    // Ellipse Initialization
    for (int k =0; k < MaxEllip ; k++){
        TheObjectsEllip[k].set(ofRandom(Nx),ofRandom(Ny),ofRandom(6,Nx/14.0),ofRandom(6,Nx/14.0),ofRandom(180),ofRandom(255));
        TheVelocitiesEllip[k].set(0.0,0.0,0.0,0.0,0.0,0.0);
    }
    int bufferSize = 2048;

    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    bool bNewFrame =false;
    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    if (bNewFrame) {
        colorImg.setFromPixels(vidGrabber.getPixels(),Nx,Ny);
        colorImg.mirror(false, true);
        TheInputRGB = colorImg.getCvImage();
        cv::cvtColor(TheInputRGB, TheInputGray, CV_RGB2GRAY);
        ImageToEllipseList(TheInputGray, 16);
        CoherentEllipses();
        
    }

}

//--------------------------------------------------------------
void ofApp::draw(){
      ofSetHexColor(0xffffff);
      TheEllipse CurrentEllipse(320,10,10,10,0,0);
    EllipseAudio(TheCoherentEllipses);
    PlotSpiral();
    
}

// Audio callback

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	
	
	
	// samples are "interleaved"
	
	float SampleAverage=0;
    float RMSValue = 0;

	for (int i = 0; i < bufferSize; i++){
		SampleAverage = input[i*2]*.5 + input[i*2+1]*0.5;
		RMSValue +=SampleAverage*SampleAverage;
	}
    
	CurrentEnergy = RMSValue/bufferSize;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

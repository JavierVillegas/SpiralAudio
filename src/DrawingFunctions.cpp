//
//  FunctionsForEllipses.cpp
//  IOWA2015
//
//  Created by Javier Villegas on 3/18/15.
//
//

#include "ofApp.h"
void ofApp::PlotEllipses(vector<TheEllipse> ElliVec,ofRectangle RectLimits){
    TheEllipse CurrentEllipse(320,10,10,10,0,0);
    glPushMatrix();
    ofTranslate(RectLimits.getCenter());
    ofScale(RectLimits.width/Nx, RectLimits.height/Ny);
    for (int k=0; k < ElliVec.size();k++){
        CurrentEllipse = ElliVec[k];
        ofSetColor(CurrentEllipse.TheGray,CurrentEllipse.TheGray,CurrentEllipse.TheGray);
        glPushMatrix();
        ofTranslate(CurrentEllipse.x-Nx/2.0, CurrentEllipse.y-Ny/2.0);
        ofRotate(CurrentEllipse.angle);
        ofEllipse(0.0,0.0 , CurrentEllipse.a, CurrentEllipse.b);
        glPopMatrix();
    }
    glPopMatrix();
}
void ofApp::PlotEllipNoFill(vector<TheEllipse> ElliVec,ofRectangle RectLimits){
    TheEllipse CurrentEllipse(320,10,10,10,0,0);
    ofNoFill();
    ofSetLineWidth(1.0);
    glPushMatrix();
    ofTranslate(RectLimits.getCenter());
    ofScale(RectLimits.width/Nx, RectLimits.height/Ny);
    
    for (int k=0; k < ElliVec.size();k++){
        CurrentEllipse = ElliVec[k];
        
        glPushMatrix();
        ofTranslate(CurrentEllipse.x-Nx/2.0, CurrentEllipse.y-Ny/2.0);
        ofRotate(CurrentEllipse.angle);
        ofEllipse(0.0,0.0 , CurrentEllipse.a, CurrentEllipse.b);
        glPopMatrix();
    }
    glPopMatrix();
    ofFill();
}

void ofApp::PlotEllipPolligon(vector<TheEllipse> ElliVec,ofRectangle RectLimits){
    TheEllipse CurrentEllipse(320,10,10,10,0,0);
    glPushMatrix();
    ofTranslate(RectLimits.getCenter());
    ofScale(RectLimits.width/Nx, RectLimits.height/Ny);
    float Slider1 = 64;
    int Nsides = (127-Slider1)*12/127 +4;
    for (int k=0; k < ElliVec.size();k++){
        CurrentEllipse = ElliVec[k];
        ofSetColor(CurrentEllipse.TheGray,CurrentEllipse.TheGray,CurrentEllipse.TheGray);
        glPushMatrix();
        ofTranslate(CurrentEllipse.x-Nx/2.0, CurrentEllipse.y-Ny/2.0);
        ofRotate(CurrentEllipse.angle);
        
        glBegin(GL_POLYGON);
        for (int s =0; s<Nsides; s++) {
            glVertex2f(CurrentEllipse.a/2.0*cos(CV_PI/Nsides+s*2*CV_PI/Nsides),
                       CurrentEllipse.b/2.0*sin(CV_PI/Nsides+s*2*CV_PI/Nsides));
        }
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();
}

void ofApp::EllipseAudio(vector<TheEllipse> ElliVec){
   
    TheEllipse CurrentEllipse(320,10,10,10,0,0);
    ofRectangle RectOut;
    float TheWidth = ofGetWidth();
    float TheHeight = ofGetHeight();
    RectOut = ofRectangle(TheWidth*.05, TheHeight*.05,
                     TheWidth*.9, TheHeight*.9);
    ofRectangle RectLimits(RectOut.x+1.0*RectOut.width/16.0,
                           RectOut.y+RectOut.height/4.0,
                           7.0*RectOut.width/16.0, RectOut.height/2.0);
    glPushMatrix();
    ofTranslate(RectLimits.getCenter());
    ofScale(RectLimits.width/Nx, RectLimits.height/Ny);
    int Nsides = 128;
    for (int k=0; k < ElliVec.size();k++){
        CurrentEllipse = ElliVec[k];
        ofSetColor(CurrentEllipse.TheGray,CurrentEllipse.TheGray,CurrentEllipse.TheGray);
        glPushMatrix();
        ofTranslate(CurrentEllipse.x-Nx/2.0, CurrentEllipse.y-Ny/2.0);
        ofRotate(CurrentEllipse.angle);
        glBegin(GL_POLYGON);
        for (int s =0; s<Nsides; s++) {
            glVertex2f(CurrentEllipse.a/2.0*cos(CV_PI/Nsides+s*2*CV_PI/Nsides)*(1+
                                                                                15*CurrentEnergy*cos(s*2*CV_PI/8.0)),
                       CurrentEllipse.b/2.0*sin(CV_PI/Nsides+s*2*CV_PI/Nsides)*(1+
                                                                                15*CurrentEnergy*cos(s*2*CV_PI/8.0)) );
        }
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();

}

void ofApp::PlotSpiral(){
   
    ofSetColor(0, 0, 0);
    glPushMatrix();
    ofRectangle RectOut;
    float TheWidth = ofGetWidth();
    float TheHeight = ofGetHeight();
    RectOut = ofRectangle(TheWidth*.05, TheHeight*.05,
                          TheWidth*.9, TheHeight*.9);

    ofTranslate(RectOut.getCenter().x + RectOut.width/4.0,
                RectOut.getCenter().y );
    glBegin(GL_LINE_STRIP);
    float TheAng =0;
    float da = .005;
    int cordX,cordY;
    uchar TheValue;
    for (int it=1; it < 70000; it++) {
        da = .005*powf(1.0 - it/70000.0,62.0/128.0);
        TheAng+=da;
        float x = TheAng*cos(TheAng);
        float y = TheAng*sin(TheAng);
        cordX = (int)(TheInputGray.cols/2 + x);
        cordY = (int)(TheInputGray.rows/2 + y);
        if((cordX<0)||(cordX>TheInputGray.cols-1)||
           (cordY<0)||(cordY>TheInputGray.rows-1))
        { TheValue =0;
        }
        else{
            TheValue = 255-TheInputGray.data[cordX + TheInputGray.cols*cordY];
        }
        
        float fun =(2000*powf((float)TheValue/255.0,20.0*46.0/128.0)
                    *powf(it/70000.0,42.0/128.0))*CurrentEnergy*sin(6000*PI*it/70000.0);
        glVertex2f(x+fun*cos(TheAng),y+fun*sin(TheAng));
    }
    
    glEnd();
    glPopMatrix();
    
    
}


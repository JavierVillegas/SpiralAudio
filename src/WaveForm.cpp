//
//  WaveForm.cpp
//  IOWA2015
//
//  Created by Javier Villegas on 3/22/15.
//
//

#include "IOWA.h"

void IOWA::NewWaveSlide(vector<TheEllipse> ElliVec){
TheEllipse CurrentEllipse(320,10,10,10,0,0);
    ofRectangle RectOut;
    RectOut = OneBigRect();
    
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
    
    
    // The Spiral
    ofSetColor(0, 0, 0);
    glPushMatrix();
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





void IOWA::WaveSlide(){
    cv::Mat SmallIma(48,64,CV_8UC1);
    cv::resize(TheInputGray, SmallIma, cv::Size(64,48));
    ofRectangle RectOut;
    RectOut = OneBigRect();
    ofSetColor(0, 0, 0 );
    //    Fuentes[0].drawString("Transcoding",
    //                          RectOut.x,RectOut.y + RectOut.height*.1);
    
    ofRectangle RectLimits;
    RectLimits.x =(RectOut.getCenter()).x - 3*RectOut.width/8.0;
    RectLimits.y=(RectOut.getCenter()).y - 0.8*3*RectOut.height/8.0;
    RectLimits.width=3*RectOut.width/4.0;
    RectLimits.height=3*RectOut.height/4.0;
    
    
    float tempoval;
    glPushMatrix();
    
    ofTranslate(RectLimits.x, RectLimits.y);
    ofScale(RectLimits.width/Nx,RectLimits.height/Ny);
    
    
    int tempindi,cordx,cordy,AudioLine2;
	float TheValue,x,y,dx,dy,cost,sint,x01,y01,slope;
    // ploting the line
	//glColor4f( 0.2, 0.2, 0.2, .4*G_Blend);
	//glColor4f( 0.1, 0.1, 0.1, .4*G_Blend);
    int NumLines = 281;
    int AudioLine =2048;
    float  Lx = 1.2;
    float  Ly = 0.9;
    AudioLine2=8*AudioLine;
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    ofSetColor(0.0, 0.0, 0.0,40);
    float base = 1.02;// + .05*Slider2/127.0;
    
	for(int k=-(NumLines-1)/2;k<(NumLines-1)/2;k+=2){
        
        
        glBegin(GL_LINE_STRIP);
        for (int q=0;q<AudioLine2;q+=8){
            x01 = q/(float)AudioLine2;
			slope = pow((float)base,(float)k)*pow((float)x01,(float)(pow((float)base,(float)k)-1));
			y01 = pow((float)x01,(float)pow(base,(float)k));
            
			cordx =(int)(SmallIma.cols*x01);
			cordy =(int)(SmallIma.rows*y01);
			if ((cordx<0)||(cordx>=SmallIma.cols)||(cordy<0)||(cordy>=SmallIma.rows)){
                TheValue = 0;
			}
			else{
                uchar* TheP = SmallIma.data;
                TheValue = (float)TheP[SmallIma.cols*(SmallIma.rows-cordy)+cordx];
				TheValue = 255*pow((1.0 -TheValue/255.0),2)*Slider1/127.0;
			}
			int esteindi= q%(AudioLine);
			dx = .004*left[esteindi]*TheValue*(-sin(atan(slope)));
			dy = .004*left[esteindi]*TheValue*cos(atan(slope));
			dx = dx*Nx;
			dy = dy*Ny;
            
            //			dx = .001*G_CurrentValue[q]*TheValue*cost;
            //			dy = .001*G_CurrentValue[q]*TheValue*sint;
            
            //			dx = .005*(2*rand()/(float)RAND_MAX-1)*cost;
            //			dy = .005*(2*rand()/(float)RAND_MAX-1)*sint;
            
            x = x01*Nx;
            y = Ny -y01*Ny;
            glVertex2f(x+dx,y+dy);
            //	(0.0008*(TheValue)*G_CurrentValue[q]),-2);
            
        }
		glEnd();
	}
    
    glDisable(GL_BLEND);

    glPopMatrix();
    
}
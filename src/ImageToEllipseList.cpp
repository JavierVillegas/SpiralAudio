//
//  ImageToEllipseList.cpp
//  IOWA2015
//
//  Created by Javier Villegas on 3/18/15.
//
//

#include "ofApp.h"
void ofApp::ImageToEllipseList(cv::Mat TheInput,int PlaneNumber){
    
    priority_queue<TheEllipse, vector<TheEllipse>,less<vector<TheEllipse>::value_type> > EllipQueue;
    // array of contours
    vector<vector<cv::Point> > contours;
    
    
    TheTargetsEllipses.clear();
    cv::Mat Maska;
    
    for (int k=0;k<PlaneNumber;k++){
        cv::inRange(TheInput,cv::Scalar((k-1)*255/(float)PlaneNumber),cv::Scalar(k*255/(float)PlaneNumber),Maska);
        cv::medianBlur(Maska,Maska,3);
        cv::findContours( Maska, contours, CV_RETR_EXTERNAL,
                         CV_CHAIN_APPROX_SIMPLE,
                         cv::Point(0,0));
        for( int conK =0; conK < contours.size(); conK++)
        {
            
            if (contours[conK].size()> 10 ){
                
                
                cv::RotatedRect Ellipdesc;
                
                Ellipdesc = cv::fitEllipse(cv::Mat(contours[conK]));
               
                
                
                EllipQueue.push(TheEllipse(Ellipdesc.center.x,
                                           Ellipdesc.center.y,
                                           Ellipdesc.size.width,
                                           Ellipdesc.size.height,
                                           Ellipdesc.angle,
                                           k*255/PlaneNumber));
                
            } // end of if contour size> 10
            
            
        } // end of for contours
        
        
        
    } // end For the Planes
    while (!EllipQueue.empty()){
        TheTargetsEllipses.push_back(EllipQueue.top());
        EllipQueue.pop();
    }
   
}
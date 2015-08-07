//
//  CoherentEllipses.cpp
//  IOWA2015
//
//  Created by Javier Villegas on 3/18/15.
//
//

#include "ofApp.h"


void ofApp::CoherentEllipses(){
    
    int TargInd[MaxEllip];
    // Fixed parameters by now
    float ThDis =13.4;
    float Ktar = 29.25;
    float Kdam = 1.05;
    float dt = 0.25;
    TheCoherentEllipses.clear();
    
    priority_queue<TheEllipse, vector<TheEllipse>,less<vector<TheEllipse>::value_type> > EllliSorter;
    
    if (!TheTargetsEllipses.empty()){
        
        for(int i =0;i< MaxEllip;i++){
            TargInd[i]=-1;
        }
        
        for (int kt=0; kt<TheTargetsEllipses.size(); kt++) {
            float MinDis =10000;
            int MinIndi =0;
            for (int ko=0; ko<MaxEllip; ko++) {
                
                TheEllipse ErrorVec;
                ErrorVec = TheTargetsEllipses[kt]-TheObjectsEllip[ko];
                float dis = ErrorVec.getLength();
                if ((dis < MinDis)&&(TargInd[ko]==-1)){
                    MinIndi = ko;
                    MinDis = dis;
                }
            }
            TargInd[MinIndi] = kt;
        }
        
        
        for (int ko=0; ko<MaxEllip; ko++) {
            
            float MinHits = 10000;
            TheEllipse UpdateVec;
            float MinDis =10000;
            int MinIndi =0;
            
            if (TargInd[ko]==-1) {
                MinDis =10000;
                for (int kt=0; kt<TheTargetsEllipses.size(); kt++) {
                    TheEllipse ErrorVec;
                    ErrorVec = TheTargetsEllipses[kt]-TheObjectsEllip[ko];
                    float dis = ErrorVec.getLength();
                    if (dis < MinDis){
                        MinDis = dis;
                        MinIndi = kt;
                    }
                    
                }
                TargInd[ko] = MinIndi;
            }
            
            UpdateVec = TheTargetsEllipses[TargInd[ko]]-TheObjectsEllip[ko];
            float newDis = UpdateVec.getLength();
            UpdateVec.normalize();
            
            
            TheEllipse acc;
            if (newDis < ThDis){
                acc = (newDis/10.0)*(Ktar*UpdateVec) - Kdam*TheVelocitiesEllip[ko];
            }
            else{
                acc = (Ktar*UpdateVec) - Kdam*TheVelocitiesEllip[ko];
            }
            TheVelocitiesEllip[ko] = TheVelocitiesEllip[ko] - (-dt)*acc;
            TheObjectsEllip[ko]  =  TheObjectsEllip[ko] - (-dt)*TheVelocitiesEllip[ko];
        }
        
    }// closing the  if from target non empty
    
    
    
    // sorting the results
    
    for (int k=0; k < MaxEllip;k++){
        EllliSorter.push(TheObjectsEllip[k]);
    }
    
    
    while (!EllliSorter.empty()){
        TheCoherentEllipses.push_back(EllliSorter.top());
        EllliSorter.pop();
    }
    
    
    
    
    
}
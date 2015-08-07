//
//  TheEllipse.h
//  IOWA2015
//
//  Created by Javier Villegas on 3/18/15.
//
//

#ifndef __IOWA2015__TheEllipse__
#define __IOWA2015__TheEllipse__

class TheEllipse {
    
public:
    
    float x;
    float y;
    float a;
    float b;
    float angle;
    float TheGray;
    TheEllipse(float,float,float,float,float,float);
    TheEllipse();
    void set(float,float,float,float,float,float);
    void normalize();
    float getWeigthedLength(float, float, float,float, float,float);
    float getLength();
    friend bool operator>(const TheEllipse& Ell1, const TheEllipse& Ell2);
    friend bool operator<(const TheEllipse& Ell1, const TheEllipse& Ell2);
    friend TheEllipse operator-(const TheEllipse& Ell1, const TheEllipse& Ell2);
    friend TheEllipse operator*(const float& K, const TheEllipse& Ell1);
    
};

#endif /* defined(__IOWA2015__TheEllipse__) */

//
//  TheEllipse.cpp
//  IOWA2015
//
//  Created by Javier Villegas on 3/18/15.
//
#include <math.h>
#include "TheEllipse.h"
TheEllipse::TheEllipse(){
    
    x = 0.0;
    y = 0.0;
    a = 0.0;
    b = 0.0;
    angle = 0.0;
    TheGray = 0;
}

TheEllipse::TheEllipse(float ex,float ey,float ea,float eb,float eangle,float eCol){
    
    x = ex;
    y = ey;
    a = ea;
    b = eb;
    angle = eangle;
    TheGray = eCol;
}

void TheEllipse::set(float ex,float ey,float ea,float eb,float eangle,float eCol){
    x = ex;
    y = ey;
    a = ea;
    b = eb;
    angle = eangle;
    TheGray = eCol;
}

float TheEllipse::getLength(){
    float TheOut = sqrtf(x*x + y*y + a*a + b*b + angle*angle + TheGray*TheGray);
    return TheOut;
}

float TheEllipse::getWeigthedLength(float wx, float wy, float wa,float wb, float wangle, float wCol){
    float TheOut = sqrtf(wx*x*x + wy*y*y + wa*a*a + wb*b*b + wangle*angle*angle + wCol*TheGray*TheGray);
    return TheOut;
}

void TheEllipse::normalize(){
    
    float theMag = sqrtf(x*x + y*y + a*a + b*b + angle*angle + TheGray*TheGray);
    if (theMag !=0){
        
        x /= theMag;
        y /= theMag;
        a /= theMag;
        b /= theMag;
        angle /= theMag;
        TheGray /= theMag;
    }
    
}

bool operator> (const TheEllipse &Ellip1, const TheEllipse &Ellip2)
{
    return (Ellip1.a*Ellip1.b) > (Ellip2.b*Ellip2.a);
}
bool operator< (const TheEllipse &Ellip1, const TheEllipse &Ellip2)
{
    return (Ellip1.a*Ellip1.b) < (Ellip2.b*Ellip2.a);
}

TheEllipse operator-(const TheEllipse &Ell1, const TheEllipse &Ell2){
    
    TheEllipse OutElli;
    float angledif;
    OutElli.x = Ell1.x -Ell2.x;
    OutElli.y = Ell1.y -Ell2.y;
    OutElli.a = Ell1.a -Ell2.a;
    OutElli.b = Ell1.b -Ell2.b;
    angledif = Ell1.angle -Ell2.angle;
    while(angledif<-180){angledif+=360;}
    while(angledif>180){angledif-=360;}
    OutElli.angle = angledif;
    OutElli.TheGray = Ell1.TheGray -Ell2.TheGray;
    return OutElli;
}

TheEllipse operator*(const float& K, const TheEllipse& Ell1){
    
    TheEllipse OutElli;
    
    OutElli.x = K*Ell1.x;
    OutElli.y = K*Ell1.y;
    OutElli.a = K*Ell1.a;
    OutElli.b = K*Ell1.b;
    OutElli.angle = K*Ell1.angle;
    OutElli.TheGray = K*Ell1.TheGray;
    
    return OutElli;
}

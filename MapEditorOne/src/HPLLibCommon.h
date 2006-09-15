#pragma once

#include <math.h>

template<class T>
int sgn(T n)
{
    if( n > 0){
        return 1;
    }else if( n < 0){
        return -1;
    }else{
        return 0;
    }
}
bool isPointInRect(double px, double py, 
                          double rx0, double ry0,
                          double rx1, double ry1);

//点が線分に近づいたかどうか判断
bool isNearbyPointToLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1,
                         double distance);

//点から線分への距離＝垂線の長さを求めます
double getPointDistanceFromLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1);

//点と点の距離が所定以内か判定
bool isNearbyPoints(double px0, double py0, 
                         double px1, double py1, double distance);

double radianToDegree(double rad);
double degreeToRadian(double deg);

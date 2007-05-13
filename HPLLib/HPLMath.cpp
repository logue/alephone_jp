#include "HPLMath.h"

#include <cmath>

static double PI = 3.1415926;
const int ROUND_DEGREE = 360;

/**
    点(px,py)から線(lx0,ly0)-(lx1,ly1)への垂線の距離を求める
*/
double hpl::math::getPointDistanceFromLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1)
{
    //start->end
    //linevector
    double lineDeltaX = lx1 - lx0;
    double lineDeltaY = ly1 - ly0;

    //start->point
    //pointvector
    double startToPointDeltaX = px - lx0;
    double startToPointDeltaY = py - ly0;

    double linevectorDistance = getLength(lineDeltaX, lineDeltaY);
    double pointvectorDistance = getLength(startToPointDeltaX, startToPointDeltaY);
    
    //線の長さが0
    if( linevectorDistance == 0){
        //始点＝終点と点の距離でOK
        return pointvectorDistance;
    }

    //始点と点の距離が0
    if(pointvectorDistance == 0){
        //0
        return 0;
    }
    //線が垂直/水平
    if(lineDeltaX == 0){
        //水平距離を取得
        return fabs(startToPointDeltaX);
    }
    if(lineDeltaY == 0){
        //垂直距離を取得
        return fabs(startToPointDeltaY);
    }

    //垂線の距離を得るために角度を計算します
    double costheta = (double)getInnerProduct(lineDeltaX, lineDeltaY, startToPointDeltaX, startToPointDeltaY) /
        (linevectorDistance * pointvectorDistance);

    double distance = ((double)pointvectorDistance * sqrt(1 - costheta * costheta));
    return distance;
}
double hpl::math::getLength(double x, double y)
{
    double length = (double)sqrt((double)(x * x + y * y));
    return length;
}

double hpl::math::getInnerProduct(double x0, double y0, double x1, double y1)
{
    double num = x0 * x1 + y0 * y1;
    return num;
}

/**線と点の近さの閾値*/
const double EPSILON = 0.01;

bool hpl::math::isCrossPointLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1)
{
    double lineDeltaX = lx1 - lx0;
    double lineDeltaY = ly1 - ly0;

    //線が垂直、水平
    if((int)lineDeltaX == 0){
        double top = (ly0 < ly1 ? ly0:ly1);
        double bottom = (ly0 < ly1 ? ly1:ly0);
        if(top <= py && py <= bottom){
            return true;
        }else{
            return false;
        }
    }
    if((int)lineDeltaY == 0){
        double left = (lx0 < lx1 ? lx0:lx1);
        double right = (lx0 < lx1 ? lx1:lx0);
        if(left <= px && px <= right){
            return true;
        }else{
            return false;
        }
    }

    //傾き
    double angleLine = lineDeltaY / lineDeltaX;

    //直行する線の傾き
    double crossAngle = - (1/ angleLine);

    //線分切片
    double sliceLine = ly0 - angleLine * lx0;
    //垂線切片
    double crossSlice = py - crossAngle * px;
    //交点X座標
    double x3 = (crossSlice - sliceLine) / (angleLine - crossAngle);
    //交点
    double crossX = x3;
    double crossY = angleLine * x3 + sliceLine;

    if(hpl::math::isPointInRect(crossX, crossY,
        lx0,ly0, lx1,ly1))
    {
        return true;
    }

    return false;
}


/////////////////////////////////////////////////////////////////////////////
//////////////  Global Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

double hpl::math::getDegreeFromRadian(double rad)
{
    double deg = rad * 180.0 / (2.0 * PI);
    return deg;
}
double hpl::math::getRadianFromDegree(double deg)
{
    double rad = deg * 2.0 * PI / 180.0;
    return rad;
}

double hpl::math::getDegreeFromVector(double dx, double dy)
{
    if(dx == 0){
        if(dy <= 0){
            return 270;
        }else{
            return 90;
        }
    }
    if(dy == 0){
        if(dx >= 0){
            return 0;
        }else{
            return 180;
        }
    }

    double divide = dy / dx;
    double rad = atan(divide);
    if(dx >= 0){
        if(rad < 0){
            rad += 2 * PI;
        }
        return rad;
    }else{
        rad += PI;
        return rad;
    }

}

/////////////////////  Is Point In  /////////////////////////////////////////
bool hpl::math::isLineInRect(int lx0, int ly0, int lx1, int ly1,
                    int rx0, int ry0, int rx1, int ry1)
{
    if(isPointInRect(lx0, ly0, rx0,ry0,rx1,ry1) && isPointInRect(lx1, ly1, rx0,ry0,rx1,ry1)){
        return true;
    }else{
        return false;
    }
}

bool hpl::math::isPolygonInRect(int **points, int point_num,
                    int rx0, int ry0, int rx1, int ry1)
{
    for(int i = 0; i < point_num; i ++){
        if(!isPointInRect(points[i][0], points[i][1],
            rx0,ry0,rx1,ry1))
        {
            return false;
        }
    }
    return true;
}

///////////////////////  Length  ////////////////////////////////////////////
bool hpl::math::isNearbyPointToLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1,
                         double distance)
{
    if(isCrossPointLine(px,py, lx0,ly0,lx1,ly1)){
        //交点が線分上にある
        //垂線が求められる
        double length = getPointDistanceFromLine(px,py, lx0,ly0,lx1,ly1);
        if(length <= distance){
            return true;
        }else{
            return false;
        }
    }
    //垂線が線分上にない
    //端との距離が短い場合も線分に近いとみなす
    if(hpl::math::isNearbyPoints(px,py, lx0,ly0, distance) ||
        hpl::math::isNearbyPoints(px,py, lx1,ly1, distance))
    {
        return true;
    }

    return false;
}

bool hpl::math::isNearbyPoints(double px0, double py0, 
                         double px1, double py1, double distance)
{
    double deltaX = px1 - px0;
    double deltaY = py1 - py0;

    if(deltaX * deltaX + deltaY * deltaY <= distance * distance){
        return true;
    }else{
        return false;
    }
}

//////////////////////////////////////////////////////////////////////
///////////////  Angle   /////////////////////////////////////////////
/**
    二つの線が織り成す角度を求めます。スクリーン座標系より、
    時計回りが正方向となる
    @param pax,y,pbx,y 線分ABの座標
    @param pcx,y,pdx,y 線分CDの座標
*/
double hpl::math::getTwoLinesRadian(double pax, double pay, double pbx, double pby,
                         double pcx, double pcy, double pdx, double pdy)
{
    //cosの定義により角度を求めます
    //A->B >>> [AB]
    double deltaABX = pbx - pax;
    double deltaABY = pby - pay;
    //|AB|
    double lengthAB = getLength(deltaABX, deltaABY);
    //∠BAX
    double radABX = getRadianFromVector(deltaABX, deltaABY);

    //[CD]
    double deltaCDX = pdx - pcx;
    double deltaCDY = pdy - pcy;
    //|CD|
    double lengthCD = getLength(deltaCDX, deltaCDY);
    //∠DCX
    double radCDX = getRadianFromVector(deltaCDX, deltaCDY);

    //ABとCDの成す角
    double radABCD = radCDX - radABX;

    return radABCD;
}
double hpl::math::getTwoLinesDegree(double pax, double pay, double pbx, double pby,
    double pcx, double pcy, double pdx, double pdy)
{
    double rad = hpl::math::getTwoLinesRadian(pax, pay, pbx, pby, pcx, pcy, pdx, pdy);
    double deg = hpl::math::getDegreeFromRadian(rad);
    return deg;
}

/**
    ベクトルの角度を求めます(0 deg = (1,0))
*
double hpl::math::getDegreeFromVector(double x, double y){
    double rad = hpl::math::getRadianFromVector(x,y);
    double deg = hpl::math::getDegreeFromRadian(rad);
    return rad;
}
*/
double hpl::math::getRadianFromVector(double x, double y){
    double deg = hpl::math::getDegreeFromVector(x, y);
    double rad = hpl::math::getRadianFromDegree(deg);
    return rad;
/*    //atanで求める
    //垂直
    if(x == 0){
        if(y > 0){
            //90度
            return PI / 2.f;
        }else if(y < 0){
            //270度
            return PI * 1.5f;
        }else{  //y == 0
            return 0;
        }
    }

    float div = y / x;
    if( x > 0){
        float rad = atan(div);
        if( rad < 0){
            rad += 2 * PI;
        }
        return rad;
    }else{
        float rad = atan(div) + PI;
        return rad;
    }
    */
}

/**
    角度を[0,360)に直します
*/
double hpl::math::optimizeDegree(double deg)
{
    const double MAX_DEGREE = 360;
    const double MIN_DEGREE = 0;
    deg += (deg < MIN_DEGREE ? 1: 0) * MAX_DEGREE * (abs((int)(deg / 360)) + 1) +
        (deg > MAX_DEGREE ? -1: 0) * MAX_DEGREE * (int)(deg / MAX_DEGREE);
    return deg;
}
double hpl::math::optimizeRadian(double rad)
{
    double deg = hpl::math::getDegreeFromRadian(rad);
    double optDeg = hpl::math::optimizeDegree(deg);
    double optRad = hpl::math::getRadianFromDegree(optDeg);
    return optRad;
}

/////////////////////////////////////////////////////
/////////////  cross  ///////////////////////////////
/**
    2つの線分が交差した点を取得します。
    @return 2つの線分が交差していない場合偽
*/
bool hpl::math::getCrossPointOfTwoLines(double line0[2][2],
    double line1[2][2], double dest[2])
{
    //それぞれの線の傾きと切片
    double degree[2] = {0,0};
    double slice[2] = {0,0};

    int lineType0 = hpl::math::getLineAngleAndSlice(line0, &degree[0], &slice[0]);
    int lineType1 = hpl::math::getLineAngleAndSlice(line1, &degree[1], &slice[1]);

    //平行線
    if(degree[0] == degree[1]){
        return false;
    }
    if(lineType0 == hpl::math::LineType::Normal){
        if(lineType1 == hpl::math::LineType::Normal){
            //傾き
            //y=a0x+b0
            //y=a1x+b1
            //x=(b1-b0)/(a1-a0)
            double angle[2];
            for(int i = 0; i < 2; i ++){
                angle[i] = hpl::math::getAngleFromDegree(degree[i]);
            }
            dest[0] = (slice[1] - slice[0]) / (angle[1] - angle[0]);
            dest[1] = dest[0] * angle[0] + slice[0];
        }else if(lineType1 == hpl::math::LineType::Vertical){
            //垂直
            //交点はx=line1[0][0]のもの
            //y=ax+b
            //傾き
            double angle0 = hpl::math::getAngleFromDegree(degree[0]);
            dest[0] = line1[0][0];
            dest[1] = angle0 * dest[0] + slice[0];
        }else{
            //水平
            //交点はy=line1[0][1]のもの
            //x=(y-b)/a
            double angle0 = hpl::math::getAngleFromDegree(degree[0]);
            dest[1] = line1[0][1];
            dest[0] = (dest[1] - slice[0]) / angle0;
        }
    }else if(lineType0 == hpl::math::LineType::Horizontal){
        if(lineType1 == hpl::math::LineType::Normal){
            //交点はy=line0[0][1]
            //x=(y-b)/a
            double angle1 = hpl::math::getAngleFromDegree(degree[1]);
            dest[1] = line0[0][1];
            dest[0] = (dest[1] - slice[1]) / angle1;
        }else if(lineType1 == hpl::math::LineType::Vertical){
            //水平線0 AND 垂直線1
            //交点はx=line1[0][0], y=line0[0][1]
            dest[0] = line1[0][0];
            dest[1] = line0[0][1];
        }else{
            //水平線＊水平線
            return false;
        }
    }else{
        //垂直線0
        if(lineType1 == hpl::math::LineType::Normal){
            //交点はx=line0[0][0]
            //y=ax+b
            double angle1 = hpl::math::getAngleFromDegree(degree[1]);
            dest[0] = line0[0][0];
            dest[1] = angle1 * dest[0] + slice[1];
        }else if(lineType1 == hpl::math::LineType::Vertical){
            //垂直線0 AND 垂直線1
            return false;
        }else{
            //垂直線0＊水平線1
            //交点はx=line0[0][0], y=line1[0][1]
            dest[0] = line0[0][0];
            dest[1] = line1[0][1];
        }
    }


    //範囲チェック
    if(!hpl::math::isPointInRect<double>(dest[0], dest[1],
        line0[0][0], line0[0][1], line0[1][0], line0[1][1]))
    {
        return false;
    }
    if(!hpl::math::isPointInRect<double>(dest[0], dest[1],
        line1[0][0], line1[0][1], line1[1][0], line1[1][1]))
    {
        return false;
    }

    return true;
}

/**
    線分の端点データから、その線の傾きと切片を求めます
    水平線か垂直な線の場合は傾きが反対の軸
    @param line line datas ([0][0],[0][1])-([1][0],[1][1])
    @param 
    @return LineType 
*/
int getLineAngleAndSlice(double line[2][2], double *degree, double *slice)
{
    double lineDeltaX = line[1][0] - line[0][0];
    double lineDeltaY = line[1][1] - line[0][1];

    //線が垂直、水平
    if((int)lineDeltaX == 0){
        //垂直  x0==x1

        if(lineDeltaY > 0){
            //下向き
            *degree = ROUND_DEGREE / 4.0;
        }else{
            //上向き
            *degree = ROUND_DEGREE / 4.0 * 3.0;
        }
        return hpl::math::LineType::Vertical;
    }
    if((int)lineDeltaY == 0){
        //水平  y0==y1
        if(lineDeltaX > 0){
            //右向き
            *degree = 0;
        }else{
            //左向き
            *degree = ROUND_DEGREE / 2.0;
        }
        return hpl::math::LineType::Horizontal;
    }

    //傾き
    double angle = lineDeltaY / lineDeltaX;
    *degree = hpl::math::getDegreeFromVector(lineDeltaX, lineDeltaY);
    
    //切片(x=0)
    //y0=ax0+b  (1)
    //y1=ax1+b  (2)
    //bで代入
    //a=(y2-y1)/(x2-x1)
    //(1)に代入
    //b=y0-ax0
    *slice = line[0][1] - lineDeltaY / lineDeltaX * line[0][0];

    return hpl::math::LineType::Normal;
}

/**
    線の傾きを角度から得ます
*/
double hpl::math::getAngleFromDegree(double degree)
{
    //ラジアンにします
    double rad = hpl::math::getRadianFromDegree(degree);
    double cs = cos(rad);
    if(cs == 0){
        //X軸移動量が0（垂直）ならば
        //0.000001くらいにする
        cs = 0.0000001;
    }
    double angle = sin(rad) / cs;
    return angle;
}

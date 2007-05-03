#include "HPLMath.h"

#include <cmath>

static double PI = 3.1415926;

/////////////////////////////////////////////////////////////////////////////
////////////  Static Methods (Private / Inner Methods)  /////////////////////
////////////  Prototypes  ///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
/**
    �_��������ւ̋����i�����̒����j�����߂܂�
    <en>get 
*/
static double getPointDistanceFromLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1);

/**
    <jp>�O�����̒藝�Œ��������߂�
    <en>get length of (0,0)-(x,y)
*/
static double getLength(double x, double y);

/**
    <jp>���ς����߂܂�
*/
static double getInnerProduct(double x0, double y0, double x1, double y1);

/**
    �_����~�낵�������������ƌ������邩���f
*/
static bool isCrossPointLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1);


/////////////////////////////////////////////////////////////////////////////
//////////////  Static Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
double getPointDistanceFromLine(double px, double py, 
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
    
    //���̒�����0
    if( linevectorDistance == 0){
        //�n�_���I�_�Ɠ_�̋�����OK
        return pointvectorDistance;
    }

    //�n�_�Ɠ_�̋�����0
    if(pointvectorDistance == 0){
        //0
        return 0;
    }
    //��������/����
    if(lineDeltaX == 0){
        //�����������擾
        return fabs(startToPointDeltaX);
    }
    if(lineDeltaY == 0){
        //�����������擾
        return fabs(startToPointDeltaY);
    }

    //�����̋����𓾂邽�߂Ɋp�x���v�Z���܂�
    double costheta = (double)getInnerProduct(lineDeltaX, lineDeltaY, startToPointDeltaX, startToPointDeltaY) /
        (linevectorDistance * pointvectorDistance);

    double distance = ((double)pointvectorDistance * sqrt(1 - costheta * costheta));
    return distance;
}
static double getLength(double x, double y)
{
    double length = (double)sqrt((double)(x * x + y * y));
    return length;
}

static double getInnerProduct(double x0, double y0, double x1, double y1)
{
    double num = x0 * x1 + y0 * y1;
    return num;
}

static bool isCrossPointLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1)
{
    const double EPSILON = 0.00001;
    double lineDeltaX = lx1 - lx0;
    double lineDeltaY = ly1 - ly0;

    //���������A����
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

    //�X��
    double angleLine = lineDeltaY / lineDeltaX;

    //���s������̌X��
    double crossAngle = - (1/ angleLine);

    //�����ؕ�
    double sliceLine = ly0 - angleLine * lx0;
    //�����ؕ�
    double crossSlice = py - crossAngle * px;
    //��_X���W
    double x3 = (crossSlice - sliceLine) / (angleLine - crossAngle);
    //��_
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
        //��_��������ɂ���
        //���������߂���
        double length = getPointDistanceFromLine(px,py, lx0,ly0,lx1,ly1);
        if(length <= distance){
            return true;
        }else{
            return false;
        }
    }
    //������������ɂȂ�
    //�[�Ƃ̋������Z���ꍇ�������ɋ߂��Ƃ݂Ȃ�
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
    ��̐����D�萬���p�x�����߂܂��B�X�N���[�����W�n���A
    ���v��肪�������ƂȂ�
    @param pax,y,pbx,y ����AB�̍��W
    @param pcx,y,pdx,y ����CD�̍��W
*/
double hpl::math::getTwoLinesRadian(double pax, double pay, double pbx, double pby,
                         double pcx, double pcy, double pdx, double pdy)
{
    //cos�̒�`�ɂ��p�x�����߂܂�
    //A->B >>> [AB]
    double deltaABX = pbx - pax;
    double deltaABY = pby - pay;
    //|AB|
    double lengthAB = getLength(deltaABX, deltaABY);
    //��BAX
    double radABX = getRadianFromVector(deltaABX, deltaABY);

    //[CD]
    double deltaCDX = pdx - pcx;
    double deltaCDY = pdy - pcy;
    //|CD|
    double lengthCD = getLength(deltaCDX, deltaCDY);
    //��DCX
    double radCDX = getRadianFromVector(deltaCDX, deltaCDY);

    //AB��CD�̐����p
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
    �x�N�g���̊p�x�����߂܂�(0 deg = (1,0))
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
/*    //atan�ŋ��߂�
    //����
    if(x == 0){
        if(y > 0){
            //90�x
            return PI / 2.f;
        }else if(y < 0){
            //270�x
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
    �p�x��[0,360)�ɒ����܂�
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

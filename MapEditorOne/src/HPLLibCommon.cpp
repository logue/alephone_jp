#include "HPLLibCommon.h"

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

bool isPointInRect(double px, double py, 
                          double rx0, double ry0,
                          double rx1, double ry1)
{
    double left = (rx0<rx1?rx0:rx1);
    double right = (rx0<rx1?rx1:rx0);
    double top = (ry0<ry1?ry0:ry1);
    double bottom = (ry0<ry1?ry1:ry0);

    if( left <= px && px <= right &&
    top <= py && py <= bottom){
        return true;
    }
    return false;
}

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

    double linevectorDistance = getLength(startToPointDeltaX, startToPointDeltaY);
    double pointvectorDistance = getLength(lineDeltaX, lineDeltaY);
    
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

    double costheta = (double)getInnerProduct(lineDeltaX, lineDeltaY, startToPointDeltaX, startToPointDeltaY) /
        (linevectorDistance * pointvectorDistance);

    double distance = ((double)pointvectorDistance * sqrt(1 - costheta * costheta));
    return distance;
}

//�_����~�낵�������������ƌ������邩���f
static bool isCrossPointLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1)
{
    const double EPSILON = 0.00001;
    double lineDeltaX = lx1 - lx0;
    double lineDeltaY = ly1 - ly0;

    //���������A����
    if(lineDeltaX == 0){
        double top = (ly0 < ly1 ? ly0:ly1);
        double bottom = (ly0 < ly1 ? ly1:ly0);
        if(top <= py && py <= bottom){
            return true;
        }else{
            return false;
        }
    }
    if(lineDeltaY == 0){
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

    if(isPointInRect(crossX, crossY,
        lx0,ly0, lx1,ly1))
    {
        return true;
    }

    return false;
}
//�_�������ɋ߂Â������ǂ������f
bool isNearbyPointToLine(double px, double py, 
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
    if(isNearbyPoints(px,py, lx0,ly0, distance) ||
    isNearbyPoints(px,py, lx1,ly1, distance)){
        return true;
    }

    return false;
}

//�_�Ɠ_�̋���������ȓ�������
bool isNearbyPoints(double px0, double py0, 
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

static double PI = 3.1415926;

double radianToDegree(double rad)
{
    double deg = rad * 180.0 / (2.0 * PI);
    return deg;
}
double degreeToRadian(double deg)
{
    double rad = deg * 2.0 * PI / 180.0;
    return rad;
}
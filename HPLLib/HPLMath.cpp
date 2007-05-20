#include "HPLMath.h"

#include <cmath>
#include <float.h>

static double PI = 3.1415926;
const int ROUND_DEGREE = 360;
//�ό`���p�`�쐬�p�̉~�̃T�C�Y(�C��)
const double POLYGON_CIRCLE_RADIUS = 30;
/**
    �_(px,py)�����(lx0,ly0)-(lx1,ly1)�ւ̐����̋��������߂�
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

/**���Ɠ_�̋߂���臒l*/
const double EPSILON = 0.01;

bool hpl::math::isCrossPointLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1)
{
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

double hpl::math::getRadianFromVector(double dx, double dy)
{
    if(dx == 0){
        if(dy <= 0){
            return PI * 3.0 / 2.0;
        }else{
            return PI / 2.0;
        }
    }
    if(dy == 0){
        if(dx >= 0){
            return 0;
        }else{
            return PI;
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
//    double lengthAB = getLength(deltaABX, deltaABY);
    //��BAX
    double radABX = getRadianFromVector(deltaABX, deltaABY);

    //[CD]
    double deltaCDX = pdx - pcx;
    double deltaCDY = pdy - pcy;
    //|CD|
//    double lengthCD = getLength(deltaCDX, deltaCDY);
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
double hpl::math::getDegreeFromVector(double x, double y){
    double rad = hpl::math::getRadianFromVector(x, y);
    double deg = hpl::math::getDegreeFromRadian(rad);
    return deg;
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

/////////////////////////////////////////////////////
/////////////  cross  ///////////////////////////////
/**
    2�̐��������������_���擾���܂��B
    @return 2�̐������������Ă��Ȃ��ꍇ�U
*/
bool hpl::math::getCrossPointOfTwoLines(double line0[2][2],
    double line1[2][2], double dest[2])
{
    //���ꂼ��̐��̌X���Ɛؕ�
    double degree[2] = {0,0};
    double slice[2] = {0,0};

    int lineType0 = hpl::math::getLineAngleAndSlice(line0, &degree[0], &slice[0]);
    int lineType1 = hpl::math::getLineAngleAndSlice(line1, &degree[1], &slice[1]);

    //���s��
    if(degree[0] == degree[1]){
        return false;
    }
    if(lineType0 == hpl::math::LineType::Normal){
        if(lineType1 == hpl::math::LineType::Normal){
            //�X��
            //y=a0x+b0
            //y=a1x+b1
            //x=(b1-b0)/(a1-a0)
            double angle[2];
            for(int i = 0; i < 2; i ++){
                angle[i] = hpl::math::getAngleFromDegree(degree[i]);
            }
            dest[0] = -(slice[1] - slice[0]) / (angle[1] - angle[0]);
            dest[1] = dest[0] * angle[0] + slice[0];
        }else if(lineType1 == hpl::math::LineType::Vertical){
            //����
            //��_��x=line1[0][0]�̂���
            //y=ax+b
            //�X��
            double angle0 = hpl::math::getAngleFromDegree(degree[0]);
            dest[0] = line1[0][0];
            dest[1] = angle0 * dest[0] + slice[0];
        }else{
            //����
            //��_��y=line1[0][1]�̂���
            //x=(y-b)/a
            double angle0 = hpl::math::getAngleFromDegree(degree[0]);
            dest[1] = line1[0][1];
            dest[0] = (dest[1] - slice[0]) / angle0;
        }
    }else if(lineType0 == hpl::math::LineType::Horizontal){
        if(lineType1 == hpl::math::LineType::Normal){
            //��_��y=line0[0][1]
            //x=(y-b)/a
            double angle1 = hpl::math::getAngleFromDegree(degree[1]);
            dest[1] = line0[0][1];
            dest[0] = (dest[1] - slice[1]) / angle1;
        }else if(lineType1 == hpl::math::LineType::Vertical){
            //������0 AND ������1
            //��_��x=line1[0][0], y=line0[0][1]
            dest[0] = line1[0][0];
            dest[1] = line0[0][1];
        }else{
            //��������������
            return false;
        }
    }else{
        //������0
        if(lineType1 == hpl::math::LineType::Normal){
            //��_��x=line0[0][0]
            //y=ax+b
            double angle1 = hpl::math::getAngleFromDegree(degree[1]);
            dest[0] = line0[0][0];
            dest[1] = angle1 * dest[0] + slice[1];
        }else if(lineType1 == hpl::math::LineType::Vertical){
            //������0 AND ������1
            return false;
        }else{
            //������0��������1
            //��_��x=line0[0][0], y=line1[0][1]
            dest[0] = line0[0][0];
            dest[1] = line1[0][1];
        }
    }


    //�͈̓`�F�b�N
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
    �����̒[�_�f�[�^����A���̐��̌X���ƐؕЂ����߂܂�
    �������������Ȑ��̏ꍇ�͌X�������΂̎�
    @param line line datas ([0][0],[0][1])-([1][0],[1][1])
    @param 
    @return LineType 
*/
int hpl::math::getLineAngleAndSlice(double line[2][2], double *degree, double *slice)
{
    double lineDeltaX = line[1][0] - line[0][0];
    double lineDeltaY = line[1][1] - line[0][1];

    *slice = 0;
    //���������A����
    if((int)lineDeltaX == 0){
        //����  x0==x1

        if(lineDeltaY > 0){
            //������
            *degree = ROUND_DEGREE / 4.0;
        }else{
            //�����
            *degree = ROUND_DEGREE / 4.0 * 3.0;
        }
        return hpl::math::LineType::Vertical;
    }
    if((int)lineDeltaY == 0){
        *slice = line[0][1];
        //����  y0==y1
        if(lineDeltaX > 0){
            //�E����
            *degree = 0;
        }else{
            //������
            *degree = ROUND_DEGREE / 2.0;
        }
        return hpl::math::LineType::Horizontal;
    }

    //�X��
    double angle = lineDeltaY / lineDeltaX;
    *degree = hpl::math::getDegreeFromVector(lineDeltaX, lineDeltaY);
    
    //�ؕ�(x=0)
    //y0=ax0+b  (1)
    //y1=ax1+b  (2)
    //b�ő��
    //a=(y1-y0)/(x1-x0)
    //(1)�ɑ��
    //b=y0-ax0
    *slice = line[0][1] - lineDeltaY / lineDeltaX * line[0][0];

    return hpl::math::LineType::Normal;
}

/**
    ���̌X�����p�x���瓾�܂�
*/
double hpl::math::getAngleFromDegree(double degree)
{
    //���W�A���ɂ��܂�
    double rad = hpl::math::getRadianFromDegree(degree);
    double cs = cos(rad);
    if(cs == 0.000000){
        //X���ړ��ʂ�0�i�����j�Ȃ��
        //0.000001���炢�ɂ���
        cs = 0.0000001;
    }
    double angle = sin(rad) / cs;
    return angle;
}

/**
    �w�肵���͈͂Ɏ��܂�n�p�`�𐶐����܂��B
    ������
    @param (x0,y0)-(x1,y1) range of rectangle. the polygon you want will be create fitting with this.
    @param points destraction of this function. you can add points and lines and polygon
*/
bool hpl::math::getRectangleScaledPreparedPolygon(double x0, double y0, double x1, double y1, int n, 
                                                  double points[8][2])
{
    if(n < 3){
        return false;
    }

    //���S���W
    double center[2];
    hpl::math::getCenterOfRectangle(x0,y0,x1,y1,center);

    //���_�𒆐S�Ƃ������aPOLYGON_CIRCLE_RADIUS(�Ă��Ɓ[)�̉~��z�肵�A
    double r = POLYGON_CIRCLE_RADIUS;
    //���̉~����ɐ�n�p�`���쐬
    double circulatePoints[8][2];
    hpl::math::getCirculatePolygonPoints(0,0, r, n,
        circulatePoints);

    //��n�p�`�ɊO�ڂ��钷���`���쐬
    //�ŏ��l�ƍő�l�����ꂼ��top/left��right/bottom�ɂ���
    double top = DBL_MAX;
    double left = DBL_MAX;
    double right = DBL_MIN;
    double bottom = DBL_MIN;
    for(int i = 0; i < n; i ++){
        double x = circulatePoints[i][0];
        double y = circulatePoints[i][1];
        if(x < left){
            left = x;
        }
        if(x > right){
            right = x;
        }
        if(y < top){
            top = y;
        }
        if(y > bottom){
            bottom = y;
        }
    }
    double rect[2][2] = {{left, top}, {right, bottom}};
    double rectCenter[2];
    hpl::math::getCenterOfRectangle(left,top,right,bottom,rectCenter);

    double inputWidth = fabs(x1 - x0);
    double inputHeight = fabs(y1-y0);
    double rectWidth = right - left;
    double rectHeight = bottom - top;
    //�ʒu���g��k���Œ���
    double xZoom = 0;
    if( rectWidth != 0) xZoom = inputWidth / rectWidth;
    double yZoom = 0;
    if(rectHeight != 0) yZoom = inputHeight / rectHeight;

    for(int i = 0; i < n; i ++){
        points[i][0] = (circulatePoints[i][0] - rectCenter[0]) * xZoom + center[0];
        points[i][1] = (circulatePoints[i][1] - rectCenter[1]) * yZoom + center[1];
    }
    if(points[0][1] != points[1][1] && points[0][1] != points[2][1])
    {
        //�E���A������1�s�N�Z���I�[�o�[����̂Œ�������
        //                    0,1,2,3,4,5,6,7,8
        int leftMaxTable[] = {0,0,0,2,2,4,4,4,4};
        for(int i = 0; i < leftMaxTable[n]; i ++){
            points[i][0] -= 1.0;
        }
        const int BOTTOM_INDEX_MAX = 10;
        int upMaxTable[][BOTTOM_INDEX_MAX] ={
            {-1},{-1},{-1},
            {1,2,-1},
            {1,2,-1},
            {1,2,3,4,-1},
            {1,2,3,4,5,-1},
            {1,2,3,4,5,6,-1},
            {1,2,3,4,5,6,-1}
        };
        for(int i = 0; upMaxTable[n][i] >= 0; i ++){
            points[upMaxTable[n][i]][1] -= 1.0;
        }
    }
/*
    //����CP�Ƌ�`�̌�_�����߂܂�
    //��ӁE�E�ӁE���ӁE����
    for(int p = 0; p < n; p ++){
        double rectangleLinePoint[4][2][2] = {
            {{x0,y0},{x1,y0}},{{x1,y0},{x1,y1}}, {{x0,y1},{x1,y1}}, {{x0,y0},{x0,y1}}};
        bool result = false;
        for(int i = 0 ; i < 4; i ++){
            double circulateLine[2][2] = {{center[0],center[1]}, {circulatePoints[p][0],circulatePoints[p][1]}};
            result = hpl::math::getCrossPointOfTwoLines(rectangleLinePoint[i], circulateLine, points[p]);
            if(result){
                break;
            }
        }
        if(!result){
            return false;
        }
    }
    */
    return true;
}

/**
    ��`�̒��S�ʒu�𓾂܂�
*/
void hpl::math::getCenterOfRectangle(double x0, double y0, double x1, double y1, double center[2])
{
    //�͈͎w�������E�E���ɂ���
    if(x0 > x1){
        hpl::math::exchange<double>(&x0, &x1);
    }
    if(y0 > y1){
        hpl::math::exchange<double>(&y0, &y1);
    }
    
    //���S���W
    center[0] = (x1 - x0) / 2.0 + x0;
    center[1] = (y1 - y0) / 2.0 + y0;
}

/**
    �~���ɉ�������n�p�`�̓_�𓾂܂�
*/
void hpl::math::getCirculatePolygonPoints(double centerx, double centery, double radius,
                                          int n, double dest[][2])
{
    //�~����̈ʒu�����߂܂�
    double intervalDeg = (double)ROUND_DEGREE / n / 2;

    double startDeg = - (double)ROUND_DEGREE / 8.0;
    if(n == 4){
        startDeg = - (double)ROUND_DEGREE / 8.0 + (double)ROUND_DEGREE / 16.0;
    }
    if(n == 8){
        startDeg = - (double)ROUND_DEGREE / 8.0 + (double)ROUND_DEGREE / 32.0;
    }
    for(int i = 0; i < n; i ++){
        double deg = startDeg + intervalDeg * i;//
        double rad = hpl::math::getRadianFromDegree(deg);
        dest[i][0] = cos(rad) * radius + centerx;
        dest[i][1] = sin(rad) * radius + centery;
    }
    if(n != 6){
        //���ɗ���2�_�������̂ŁA���������ɂ���
        //             0,1,2,3,4,5,6,7,8
        int table[] = {0,0,0,1,1,2,0,3,3};
        int t = table[n];
        dest[t][1] = dest[t + 1][1];
    }
}

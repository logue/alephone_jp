#pragma once

#include <math.h>
#include "AlephOne/map.h"

//////////////////////////////////////////////////////////
// structures
struct SelPoint{
    int index;
    int offset[2];
};
struct SelLine{
    int index;
    int offsets[2][2];
};
struct SelPolygon{
    int index;
    int num;
    int offsets[8][2];
};
struct SelObject{
    int index;
    int offset[2];
};
struct selectInformation{
    bool isSelected(){
        return isSelected_;
    }
    void setSelected(bool sel){
        isSelected_ = sel;
    }
    void clear(){
        points.clear();
        lines.clear();
        polygons.clear();
        selObjects.clear();
        setSelected(false);
    }
    //�_�̃��X�g
    vector<SelPoint> points;

    //���̃��X�g
    vector<SelLine> lines;

    //�|���S���̃��X�g
    vector<SelPolygon> polygons;

    //�I�u�W�F�N�g���X�g
    vector<SelObject> selObjects;
private:
    bool isSelected_;

};

/////////////////////////////////////////////////
// functions prototypes
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
template<class T>
bool isPointInRect(T px, T py, 
                          T rx0, T ry0,
                          T rx1, T ry1)
{
    T left = (rx0<rx1?rx0:rx1);
    T right = (rx0<rx1?rx1:rx0);
    T top = (ry0<ry1?ry0:ry1);
    T bottom = (ry0<ry1?ry1:ry0);

    if( left <= px && px <= right &&
    top <= py && py <= bottom){
        return true;
    }
    return false;
}

//�_�������ɋ߂Â������ǂ������f
bool isNearbyPointToLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1,
                         double distance);

//�_��������ւ̋����������̒��������߂܂�
double getPointDistanceFromLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1);

//�_�Ɠ_�̋���������ȓ�������
bool isNearbyPoints(double px0, double py0, 
                         double px1, double py1, double distance);

double radianToDegree(double rad);
double degreeToRadian(double deg);

/**������`�����`�F�b�N**/
bool isLineInRect(int lx0, int ly0, int lx1, int ly1,
                    int rx0, int ry0,
                    int rx1, int ry1);

/**�|���S������`�����`�F�b�N*/
bool isPolygonInRect(int **points, int point_num,
                    int rx0, int ry0,
                    int rx1, int ry1);

/**
    is view-point near world-point?
    @param viewPX   point(mouse/view)
    @param worldPX  point(world)
    @param offsetViewX offset of view
    @param offsetWorldX offset of world
    @param distance check distance
*/
bool isSelectPoint(int viewPX, int viewPY, 
                   int worldPX, int worldPY,
                   int offsetViewX, int offsetViewY,
                   int offsetWorldX, int offsetWorldY,
                   int div,
                   int distance);
/**
    is view-point near world-line?
    @param viewPX   point(mouse/view)
    @param worldPX0 line's point(world)
    @param offsetViewX offset of view
    @param offsetWorldX offset of world
    @param distance check distance
*/
bool isSelectLine(int viewPX, int viewPY,
                   int worldPX0, int worldPY0,
                   int worldPX1, int worldPY1,
                   int offsetViewX, int offsetViewY,
                   int offsetWorldX, int offsetWorldY,
                   int div,
                   int distance);

/**
    is point in select groups?
    @param px point locatin(view)
    @param offsetViewX offset(view)
    @param offsetWorldX offset(world)
    @param pointDistance distance as nearby point
    @param lineDistance distance as nearby line
    @param objectDistance distance as nearby object
    @param selectInfo select group for check
*/
bool isPointInSelection(int px, int py,
                        int offsetViewX, int offsetViewY,
                        int offsetWorldX, int offsetWorldY,
                        int pointDistance,
                        int lineDistance,
                        int objectDistance,
                        struct selectInformation* selectInfo,
                        int heightMax, int heightMin, int div);

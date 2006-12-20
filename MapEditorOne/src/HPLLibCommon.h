#pragma once

#include <math.h>
#include <vector>
#include "AlephOne/map.h"
#include "AlephOne/wad.h"

using namespace std;

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
        sideIndex = NONE;
    }
    bool isSelectOneObject(){
        if(isSelected() && points.size() == 0 && lines.size() == 0 && polygons.size() == 0 &&
            selObjects.size() == 1)
        {
            return true;
        }else
        {
            return false;
        }
    }
    bool isSelectOnePoint(){
        if(isSelected() && points.size() == 1 && lines.size() == 0 && polygons.size() == 0 &&
            selObjects.size() == 0)
        {
            return true;
        }else
        {
            return false;
        }
    }
    bool isSelectOneLine(){
        if(isSelected() && points.size() == 0 && lines.size() == 1 && polygons.size() == 0 &&
            selObjects.size() == 0)
        {
            return true;
        }else
        {
            return false;
        }
    }
    bool isSelectOnePolygon(){
        if(isSelected() && points.size() == 0 && lines.size() == 0 && polygons.size() == 1 &&
            selObjects.size() == 0)
        {
            return true;
        }else
        {
            return false;
        }
    }
    //点のリスト
    vector<SelPoint> points;

    //線のリスト
    vector<SelLine> lines;

    //ポリゴンのリスト
    vector<SelPolygon> polygons;

    //オブジェクトリスト
    vector<SelObject> selObjects;

    int sideIndex;
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

/**線が矩形内かチェック**/
bool isLineInRect(int lx0, int ly0, int lx1, int ly1,
                    int rx0, int ry0,
                    int rx1, int ry1);

/**ポリゴンが矩形内かチェック*/
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
bool isSelectPoint(world_point2d &point0, world_point2d &point1,
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
bool isSelectLine(world_point2d &point,
                  world_point2d &linePoint0, world_point2d &linePoint1,
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

//calcurate degree from vector
double getDegreeFromVector(double dx, double dy);

/**
    sort order from index to height
    @param type LINE_TAG, ENDPOINT_TAG ...
    @param 
*/
void sortOrderToHeight(int max, int type, int *sortedOne, bool isFloor);

void quickSort(int *indexes, int max);

/**
	文字列の分割
*/
vector<string> Split( string src, const char* key);

/**
    calculate degree between two connected lines
*/
double getDegreeBetweenTwoLines(int lineIndex0, int lineIndex1);

/**
    check is polygon valid
*/
bool isPolygonValid(int polygonIndex);

//SDL
/**
    get pixel data 
    !!! must lock screen before using !!!
*/
Uint32 getpixel(SDL_Surface *surface, int x, int y);
Uint32 getpixel(Uint8* pixels, int pitch, int bpp,  int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void addAnnotationText(world_point2d& point, string text);

//get polygon index which include the point
//return NONE when not found
int getPolygonIdPointIn(world_point2d& point);

//bool isPolygonValid(world_point2d& point, 

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

    double costheta = (double)getInnerProduct(lineDeltaX, lineDeltaY, startToPointDeltaX, startToPointDeltaY) /
        (linevectorDistance * pointvectorDistance);

    double distance = ((double)pointvectorDistance * sqrt(1 - costheta * costheta));
    return distance;
}

//点から降ろした垂線が線分と交差するか判断
static bool isCrossPointLine(double px, double py, 
                         double lx0, double ly0, double lx1, double ly1)
{
    const double EPSILON = 0.00001;
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

    if(isPointInRect(crossX, crossY,
        lx0,ly0, lx1,ly1))
    {
        return true;
    }

    return false;
}
//点が線分に近づいたかどうか判断
bool isNearbyPointToLine(double px, double py, 
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
    if(isNearbyPoints(px,py, lx0,ly0, distance) ||
    isNearbyPoints(px,py, lx1,ly1, distance)){
        return true;
    }

    return false;
}

//点と点の距離が所定以内か判定
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

/**線が矩形内かチェック**/
bool isLineInRect(int lx0, int ly0, int lx1, int ly1,
                    int rx0, int ry0,
                    int rx1, int ry1)
{
    if(isPointInRect(lx0, ly0, rx0,ry0,rx1,ry1) && isPointInRect(lx1, ly1, rx0,ry0,rx1,ry1)){
        return true;
    }else{
        return false;
    }
}

/**ポリゴンが矩形内かチェック*/
bool isPolygonInRect(int **points, int point_num,
                    int rx0, int ry0,
                    int rx1, int ry1)
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

/**is selecting point?
    @param viewPX   point(mouse/view)
    @param worldPX  point(world)
    @param offsetViewX offset of view
    @param offsetWorldX offset of world
    @param div divergence of 2 * world per view
    @param distance check distance
*/
bool isSelectPoint(int viewPX, int viewPY, 
                   int worldPX, int worldPY,
                   int offsetViewX, int offsetViewY,
                   int offsetWorldX, int offsetWorldY,
                   int div,
                   int distance)
{
    int worldViewX = (worldPX + offsetWorldX)/div + offsetViewX;
    int worldViewY = (worldPY + offsetWorldY)/div + offsetViewY;
    //check
    bool isSelect = isNearbyPoints(
        viewPX,viewPY, worldViewX, worldViewY,
        distance);
    return isSelect;
}

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
                   int distance)
{
    int x0 = (worldPX0 + offsetWorldX) / div + offsetViewX;
    int y0 = (worldPY0 + offsetWorldY) / div + offsetViewY;
    int x1 = (worldPX1 + offsetWorldX) / div + offsetViewX;
    int y1 = (worldPY1 + offsetWorldY) / div + offsetViewY;

    bool isSelect = isNearbyPointToLine(viewPX, viewPY, x0, y0, x1, y1, distance);
    return isSelect;
}

/**
    is point in select groups?
    @param px point locatin(view)
    @param offsetViewX offset(view)
    @param offsetWorldX offset(world)
    @param pointDistance distance as nearby
    @param lineDistance distance as nearby
    @param selectInfo select group for check
*/
bool isPointInSelection(int px, int py,
                        int offsetViewX, int offsetViewY,
                        int offsetWorldX, int offsetWorldY,
                        int pointDistance,
                        int lineDistance,
                        int objectDistance,
                        struct selectInformation* selectInfo,
                        int heightMax, int heightMin, int div)
{
    //objects
    for(int i = 0; i < (int)selectInfo->selObjects.size(); i ++){
        map_object* obj = &(SavedObjectList[selectInfo->selObjects[i].index]);
        int type = obj->type;
        int facing = obj->facing;
        int x = obj->location.x;
        int y = obj->location.y;
        int z = obj->location.z;
        if(z > heightMax || z < heightMin){
            continue;
        }
        if(isSelectPoint(px, py,
            x, y, offsetViewX, offsetViewY,
            offsetWorldX, offsetWorldY, div, objectDistance))
        {
            return true;
        }
    }
    //points
    for(int i = 0; i < (int)selectInfo->points.size(); i ++){
        endpoint_data* ep = &EndpointList[selectInfo->points[i].index];
        int x = ep->vertex.x;
        int y = ep->vertex.y;
        int drawX = (x + offsetWorldX)/div + offsetViewX;
        int drawY = (y + offsetWorldY)/div + offsetViewY;
        if(isSelectPoint(px, py,
            x, y, offsetViewX, offsetViewY,
            offsetWorldX, offsetWorldY, div, objectDistance))
        {
            return true;
        }
    }

    //lines
    for(int i = 0; i < (int)selectInfo->lines.size(); i ++){
        line_data* line = &LineList[selectInfo->lines[i].index];
        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
        if(isSelectLine(px, py, begin->vertex.x, begin->vertex.y,
            end->vertex.x, end->vertex.y, offsetViewX, offsetViewY,
            offsetWorldX, offsetWorldY, div, lineDistance))
        {
            return true;
        }
    }
    //polygons
    for(int i = 0; i < (int)selectInfo->polygons.size(); i ++){
        struct world_point2d world_point;
        world_point.x = (world_distance)((px - offsetViewX) * div - offsetWorldX);
        world_point.y = (world_distance)((py - offsetViewY) * div - offsetWorldY);

        if(point_in_polygon(selectInfo->polygons[i].index, &world_point)){
            return true;
        }
    }

    //no selection
    return false;
}
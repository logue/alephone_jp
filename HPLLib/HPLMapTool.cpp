#include "HPLMapTool.h"
#include "HPLMath.h"

static double getLengthDouble(double x, double y)
{
    double length = (double)sqrt((double)(x * x + y * y));
    return length;
}

///////////////////////  Points  ////////////////////////////////////////////
bool hpl::aleph::map::isSelectPoint(int viewPX, int viewPY, 
                   int worldPX, int worldPY,
                   int offsetViewX, int offsetViewY,
                   int offsetWorldX, int offsetWorldY,
                   int div,
                   int distance)
{
    int worldViewX = (worldPX + offsetWorldX)/div + offsetViewX;
    int worldViewY = (worldPY + offsetWorldY)/div + offsetViewY;
    //check
    bool isSelect = hpl::math::isNearbyPoints(
        viewPX,viewPY, worldViewX, worldViewY,
        distance);
    return isSelect;
}

bool hpl::aleph::map::isSelectPoint(world_point2d &point0, world_point2d &point1,
                   int distance)
{
    //check
    bool isSelect = hpl::math::isNearbyPoints(
        point0.x,point0.y, point1.x, point1.y,
        distance);
    return isSelect;
}

//convert view <-> world point
world_point2d hpl::aleph::map::getWorldPoint2DFromViewPoint(int viewPX, int viewPY,
	int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety)
{
    world_point2d point;
    point.x = (world_distance)((viewPX - offsetx) *
        zoomDivision - offsetXWorld);
    point.y = (world_distance)((viewPY - offsety) *
        zoomDivision - offsetYWorld);
    return point;
}
void hpl::aleph::map::getViewPointFromWorldPoint2D(world_point2d& point, int *dest,
	int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety)
{
    dest[0] = (point.x + offsetXWorld)/zoomDivision + offsetx;
    dest[1] = (point.y + offsetYWorld)/zoomDivision + offsety;
}

///////////////////////  Lines  ////////////////////////////////////////////

bool hpl::aleph::map::isSelectLine(int viewPX, int viewPY,
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

    bool isSelect = hpl::math::isNearbyPointToLine(viewPX, viewPY, x0, y0, x1, y1, distance);
    return isSelect;
}
bool hpl::aleph::map::isSelectLine(world_point2d &point,
                  world_point2d &linePoint0, world_point2d &linePoint1,
                  int distance)
{
    bool isSelect = hpl::math::isNearbyPointToLine(point.x, point.y,
        linePoint0.x, linePoint0.y, linePoint1.x, linePoint1.y, distance);
    return isSelect;
}
double hpl::aleph::map::getLineLength(int index)
{
    line_data* l = get_line_data(index);
    endpoint_data* start = get_endpoint_data(l->endpoint_indexes[0]);
    endpoint_data* end = get_endpoint_data(l->endpoint_indexes[1]);
    double length = hpl::aleph::map::getPointsDistance(start->vertex, end->vertex);
    return length;
}

/**
*/
double hpl::aleph::map::getPointsDistance(world_point2d& pointA, world_point2d& pointB)
{
    double length = getLengthDouble((double)pointA.x - pointB.x,(double) pointA.y - pointB.y);
    return length;
}

/**
    <jp>�������X�V����
    <en>Fix line_data up
    @param isDeleteOldSide descide which deletes or not �g���Ă��Ȃ��Ǐ����폜���邩
*/
void hpl::aleph::map::fixLine(int index, bool isDeleteOldSide)
{
    if(index < 0 || index >= (int)LineList.size()){
        return;
    }

    line_data* line = get_line_data(index);

    //left poly
    int leftPolyIndex = line->counterclockwise_polygon_owner;
    int rightPolyIndex = line->clockwise_polygon_owner;
    //	theMapLevel.theSides.SetupSide(leftPoly, rightPoly, &theLine->leftSide, index, deleteOldSides);
/*    hpl::aleph::map::setupSide(leftPolyIndex, rightPolyIndex,
        line->left_side, index, isDeleteOldSide);
    hpl::aleph::map::setupSide(rightPolyIndex, leftPolyIndex,
        line->right_side, index, isDeleteOldSide);
*/    if(leftPolyIndex != NONE){
        polygon_data* leftPoly = get_polygon_data(leftPolyIndex);
        if(rightPolyIndex != NONE){
            polygon_data* rightPoly = get_polygon_data(rightPolyIndex);
            if(line->highest_adjacent_floor < rightPoly->floor_height){
                line->highest_adjacent_floor = rightPoly->floor_height;
            }
            if(line->lowest_adjacent_ceiling < rightPoly->ceiling_height){
                line->lowest_adjacent_ceiling = rightPoly->ceiling_height;
            }
        }else{
            line->highest_adjacent_floor = leftPoly->floor_height;
            line->lowest_adjacent_ceiling = leftPoly->ceiling_height;
        }
    }else if(rightPolyIndex != NONE){
        polygon_data* rightPoly = get_polygon_data(rightPolyIndex);
        line->highest_adjacent_floor = rightPoly->floor_height;
        line->lowest_adjacent_ceiling = rightPoly->ceiling_height;
    }
    if(leftPolyIndex == NONE && rightPolyIndex != NONE){
        //reverse
        int temp;
        temp = line->endpoint_indexes[0];
        line->endpoint_indexes[0] = line->endpoint_indexes[1];
        line->endpoint_indexes[1] = temp;
        hpl::math::exchange<int16>(&line->counterclockwise_polygon_side_index, &line->clockwise_polygon_side_index);
        hpl::math::exchange<int16>(&line->counterclockwise_polygon_owner, &line->clockwise_polygon_owner);
    }

    double length = hpl::aleph::map::getLineLength(index);
    line->length = static_cast<int>(length);
}

///////////////////////  Sides  ////////////////////////////////////////////
void hpl::aleph::map::fixSide(int leftPolyIndex, int rightPolyIndex, int sideIndex,
        int lineIndex, bool isDeleteOldSide)
{

}

///////////////////////  Groups  ////////////////////////////////////////////
bool hpl::aleph::map::isPointInSelection(int px, int py,
                        int offsetViewX, int offsetViewY,
                        int offsetWorldX, int offsetWorldY,
                        int pointDistance,
                        int lineDistance,
                        int objectDistance,
                        hpl::aleph::map::HPLSelectData* selectInfo,
                        int heightMax, int heightMin, int div)
{
    //objects
    std::vector<struct hpl::aleph::map::SelObject>* selobjects = 
        selectInfo->getSelObjects();
    for(int i = 0; i < (int)selobjects->size(); i ++){
        map_object* obj = &(SavedObjectList[selobjects->at(i).index]);
        int type = obj->type;
        int facing = obj->facing;
        int x = obj->location.x;
        int y = obj->location.y;
        int z = obj->location.z;
        if(z > heightMax || z < heightMin){
            continue;
        }
        if(hpl::aleph::map::isSelectPoint(px, py,
            x, y, offsetViewX, offsetViewY,
            offsetWorldX, offsetWorldY, div, objectDistance))
        {
            return true;
        }
    }
    //points
    std::vector<struct hpl::aleph::map::SelPoint>* selpoints = 
        selectInfo->getSelPoints();
    for(int i = 0; i < (int)selpoints->size(); i ++){
        endpoint_data* ep = &EndpointList[selobjects->at(i).index];
        int x = ep->vertex.x;
        int y = ep->vertex.y;
        int drawX = (x + offsetWorldX)/div + offsetViewX;
        int drawY = (y + offsetWorldY)/div + offsetViewY;
        if(hpl::aleph::map::isSelectPoint(px, py,
            x, y, offsetViewX, offsetViewY,
            offsetWorldX, offsetWorldY, div, objectDistance))
        {
            return true;
        }
    }

    //lines
    std::vector<struct hpl::aleph::map::SelLine>* sellines = 
        selectInfo->getSelLines();
    for(int i = 0; i < (int)sellines->size(); i ++){
        line_data* line = &LineList[selobjects->at(i).index];
        endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
        endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
        if(hpl::aleph::map::isSelectLine(px, py, begin->vertex.x, begin->vertex.y,
            end->vertex.x, end->vertex.y, offsetViewX, offsetViewY,
            offsetWorldX, offsetWorldY, div, lineDistance))
        {
            return true;
        }
    }
    //polygons
    std::vector<struct hpl::aleph::map::SelPolygon>* selpolygons = 
        selectInfo->getSelPolygons();
    for(int i = 0; i < (int)selpolygons->size(); i ++){
        struct world_point2d world_point;
        world_point.x = (world_distance)((px - offsetViewX) * div - offsetWorldX);
        world_point.y = (world_distance)((py - offsetViewY) * div - offsetWorldY);

        if(point_in_polygon(selobjects->at(i).index, &world_point)){
            return true;
        }
    }

    //no selection
    return false;
}

//���̉��������v��肩�A�����v��肩
typename PolygonRotation{
    enum RotationType{
        Clockwise,
        Counterclockwise,

        MAX_POLYGON_ROTATION_TYPES
    };
};

/**
    �|���S�������݂Ƃ��Đ��������ǂ����𔻒肵�܂�
    @param index index of polygon which is checked �����Ώۂ̃|���S���C���f�b�N�X
*/
bool hpl::aleph::map::isValidPolygon(int index)
{
    //TODO
    //�|���S�������擾���܂�
    polygon_data *polygon = get_polygon_data(index);

    //�|���S����񂪖���
    if(polygon == null){
        return false;
    }

    //�|���S���ɏ�����������擾���܂�
    int vertexCount = polygon->vertex_count;
    int startPointIndex = polygon->endpoint_indexes[0];
    int pointA, pointB, pointC;
    
    //���v��肩�A�����v��肩
    PolygonRotation::RotationType polygonRotationType = PolygonRotation::Clockwise;

    //�_i�Ɠ_i+1���܂ސ���AB, �_i+1�Ɠ_i+2���܂ސ���BC�Ƃ���B
    //�ŏ��̐�[�_0,�_1]�Ɛ�[�_1,�_2]�̊p�x����A���v��肩�A�����v��肩�𔻒肷��
    pointA = startPointIndex;
    pointB = polygon->endpoint_indexes[1];
    pointC = polygon->endpoint_indexes[2];
    
    return false;
}

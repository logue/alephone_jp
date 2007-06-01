#include "HPLMapTool.h"
#include "HPLMath.h"
#include <limits.h>
#include "HPLQuickSort.h"

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
/**
    指定した座標では線を選択できたか？
    @param point 指定ポイント
    @param linePoint0 線の端点0
    @param linePoint1 線の端点1
    @param distance 閾値
    @return 選択できるなら真
*/
bool hpl::aleph::map::isSelectLine(world_point2d &point,
                  world_point2d &linePoint0, world_point2d &linePoint1,
                  int distance)
{
    bool isSelect = hpl::math::isNearbyPointToLine(point.x, point.y,
        linePoint0.x, linePoint0.y, linePoint1.x, linePoint1.y, distance);
    return isSelect;
}

/**
    線の長さを求めます
    @param index 線インデックス
*/
double hpl::aleph::map::getLineLength(int index)
{
    line_data* l = get_line_data(index);
    endpoint_data* start = get_endpoint_data(l->endpoint_indexes[0]);
    endpoint_data* end = get_endpoint_data(l->endpoint_indexes[1]);
    double length = hpl::aleph::map::getPointsDistance(start->vertex, end->vertex);
    return length;
}

/**
    2点の距離を求めます
*/
double hpl::aleph::map::getPointsDistance(world_point2d& pointA, world_point2d& pointB)
{
    double length = getLengthDouble((double)pointA.x - pointB.x,(double) pointA.y - pointB.y);
    return length;
}

/**
    <jp>線情報を更新する
    <en>Fix line_data up
    @param isDeleteOldSide descide which deletes or not 使われていない壁情報を削除するか
*/
void hpl::aleph::map::fixLine(int index, bool isDeleteOldSide)
{
    //TODO
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

/**
    線情報を線を構成する点によって取得します
    get line index with two point indexes
    @return 線が存在しない場合NONE
*/
int hpl::aleph::map::getLineIndexFromTwoLPoints(int pindex0, int pindex1)
{
    for(int i = 0; i < (int)LineList.size(); i ++){
        line_data* line = get_line_data(i);
        int ep0 = line->endpoint_indexes[0];
        int ep1 = line->endpoint_indexes[1];

        if((ep0 == pindex0 && ep1 == pindex1) ||
            (ep1 == pindex0 && ep0 == pindex1))
        {
            //双方が一致した場合のみ返す
            return i;
        }
    }
    return NONE;
}

///////////////////////  Sides  ////////////////////////////////////////////
void hpl::aleph::map::fixSide(int sideIndex)
{
    //TODO
}

///////////////////////  Groups  ////////////////////////////////////////////
/**
	マウスが既に選択されているアイテムをクリックしているか確かめます
	<en>is point in select groups?
	@param px point locatin(view)				マウス位置（ビュー座標）
	@param offsetViewX offset(view)				ビュー座標ズレ
	@param offsetWorldX offset(world)			実座標
	@param pointDistance distance as nearby		点用閾値
	@param lineDistance distance as nearby		線用閾値
	@param selectInfo select group for check	グループクラス
*/
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
    {
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
    }

    //points
    {
        std::vector<struct hpl::aleph::map::SelPoint>* selpoints = 
            selectInfo->getSelPoints();
        for(int i = 0; i < (int)selpoints->size(); i ++){
            endpoint_data* ep = &EndpointList[selpoints->at(i).index];
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
    }

    //lines
    {
        std::vector<struct hpl::aleph::map::SelLine>* sellines = 
            selectInfo->getSelLines();
        for(int i = 0; i < (int)sellines->size(); i ++){
            line_data* line = &LineList[sellines->at(i).index];
            endpoint_data* begin = &EndpointList[line->endpoint_indexes[0]];
            endpoint_data* end = &EndpointList[line->endpoint_indexes[1]];
            if(hpl::aleph::map::isSelectLine(px, py, begin->vertex.x, begin->vertex.y,
                end->vertex.x, end->vertex.y, offsetViewX, offsetViewY,
                offsetWorldX, offsetWorldY, div, lineDistance))
            {
                return true;
            }
        }
    }
    //polygons
    {
        std::vector<struct hpl::aleph::map::SelPolygon>* selpolygons = 
            selectInfo->getSelPolygons();
        for(int i = 0; i < (int)selpolygons->size(); i ++){
            struct world_point2d world_point;
            world_point.x = (world_distance)((px - offsetViewX) * div - offsetWorldX);
            world_point.y = (world_distance)((py - offsetViewY) * div - offsetWorldY);

            if(point_in_polygon(selpolygons->at(i).index, &world_point)){
                return true;
            }
        }
    }

    //no selection
    return false;
}


/**
    ポリゴンが存在として正しいかどうかを判定します
    @param index index of polygon which is checked 検査対象のポリゴンインデックス
*/
bool hpl::aleph::map::isValidPolygon(int index)
{
    //TODO
    //ポリゴン情報を取得します
    polygon_data *polygon = get_polygon_data(index);

    //ポリゴン情報が無い
    if(polygon == NULL){
        return false;
    }

    //線の並びが正しいかチェック
    int vertexCount = polygon->vertex_count;
    for(int i = 0; i < vertexCount - 1; i ++){
        int a = polygon->endpoint_indexes[i];
        int next = i + 1;
        if(i == vertexCount - 2){
            next = 0;
        }
        int b = polygon->endpoint_indexes[next];
        int lineIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(a, b);
        if(lineIndex == NONE){
            return false;
        }

    }
    double points[MAX_VERTEX_PER_POLYGON][2];
    bool isValid = hpl::math::isValidPolygon(points, vertexCount);

    int startPointIndex = polygon->endpoint_indexes[0];
    int pointA, pointB, pointC;
    
    
    //時計回りか、反時計回りか
    int polygonRotationType = RotationType::Clockwise;
    bool isFirstLoop = true;

    for(int i = 0; i < vertexCount - 2; i ++){
        //点iと点i+1を含む線をAB, 点i+1と点i+2を含む線をBCとする。
        //最初の線[点0,点1]と線[点1,点2]の角度から、時計回りか、反時計回りかを判定する
        pointA = polygon->endpoint_indexes[i];
        pointB = polygon->endpoint_indexes[i + 1];
        pointC = polygon->endpoint_indexes[i + 2];
        
        //二つの線AB,BCが織り成す角度を求める
        double firstDegree = hpl::aleph::map::getTwoLinesDegree(pointA, pointB, pointB, pointC);
        int lineABIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(pointA, pointB);
        int lineBCIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(pointB, pointC);
        if(lineABIndex == NONE || lineBCIndex == NONE){
            //線の並び順が正しくない
            return false;
        }
        //line_indexesのならびに対応しているかどうか
        if(polygon->line_indexes[i] != lineABIndex ||
            polygon->line_indexes[i + 1] != lineBCIndex){
            return false;
        }
        //optimize degree to [0,360)
        double optDeg = hpl::math::optimizeDegree(firstDegree);

        if(isFirstLoop){
            //もし角度が[0,180)ならば、右回りである
            //それ以外（[180,360)）ならば、左回りである
            if(optDeg >= 180.0){
                polygonRotationType = Counterclockwise;
            }
            isFirstLoop = false;
        }else{
            //ポリゴンが逆鋭角（切り込んでる）状態ならば異常であるとする
            if((polygonRotationType == RotationType::Clockwise && optDeg >= 180) ||
                (polygonRotationType == RotationType::Counterclockwise && optDeg < 180)){
                return false;
            }
        }
    }
    return true;
}

/**
    座標を取り囲むポリゴンのうち、ポリゴンとして成立しているものをさがします
    すでにポリゴンが存在している場合は無視します
    @param wpoint 探索基点。ここを囲むポリゴンを探す
    @return ポリゴンの実データ候補。これを元に生成すると良い。データはcreatePolygonで生成すべし
*/
std::vector<polygon_data> hpl::aleph::map::searchValidPolygon(world_point2d wpoint)
{
    std::vector<polygon_data> polyDatas;

    int max = (int)LineList.size();
    //線への垂線の距離順で整列する
    //全部の線への垂線を求める
    struct hpl::math::qsort::Pair<double>* pairs = new struct hpl::math::qsort::Pair<double>[max];
    for(int i = 0; i < max; i ++){
        line_data* line = get_line_data(i);
        endpoint_data* epStart = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* epEnd = get_endpoint_data(line->endpoint_indexes[1]);
        pairs[i].data = hpl::math::getPointDistanceFromLine(wpoint.x, wpoint.y, 
            epStart->vertex.x, epStart->vertex.y, epEnd->vertex.x, epEnd->vertex.y);
    }
    hpl::math::qsort::quickSort<double>(pairs, max);

    //近くにある線から見ていく
    for(int i = 0; i < max; i ++){
        line_data* startLine = get_line_data(pairs[i].index);
        //線の左右どちらの側に点があるかをチェックします
        RotationType rot = Clockwise;
        //
    }
    
    //解放
    delete pairs;
    return polyDatas;
}

/**
    世界座標からポリゴンデータを作ります
    TODO 整合性
    @param points 世界座標
    @param ep 生成された点データ
    @param ld 生成された線データ
    @param n n角形
*/
polygon_data hpl::aleph::map::createPolygon(world_point2d points[],
                                            endpoint_data epd[], line_data ld[],
        int n)
{
    //点生成
    for(int i = 0; i < n; i ++){
        epd[i].flags = 0;
        epd[i].highest_adjacent_floor_height = 0;
        epd[i].lowest_adjacent_ceiling_height = WORLD_ONE;
        epd[i].vertex.x = points[i].x;
        epd[i].vertex.y = points[i].y;

        epd[i].supporting_polygon_index = 0;
    }

    //線
    for(int i = 0; i < n ; i ++){
        ld[i].endpoint_indexes[0] = i;
        ld[i].endpoint_indexes[1] = i + 1;
        if(i == n - 1){
            ld[i].endpoint_indexes[0] = i;
            ld[i].endpoint_indexes[1] = 0;
        }
        ld[i].flags = SOLID_LINE_BIT | ELEVATION_LINE_BIT;

        ld[i].highest_adjacent_floor = 0;
        ld[i].lowest_adjacent_ceiling = WORLD_ONE;
	    ld[i].clockwise_polygon_side_index = NONE;
        ld[i].counterclockwise_polygon_side_index = NONE;
    	
	    ld[i].clockwise_polygon_owner = 0;
        ld[i].counterclockwise_polygon_owner = NONE;

        ld[i].length = hpl::aleph::map::getPointsDistance(
            epd[ld[i].endpoint_indexes[0]].vertex, epd[ld[i].endpoint_indexes[1]].vertex);
    }

    //ポリゴン
    polygon_data pdata;
	pdata.type = _polygon_is_normal;
	pdata.flags = 0;
	pdata.permutation = 0;

	pdata.vertex_count = n;
    for(int i = 0; i < n; i ++){
        pdata.endpoint_indexes[i] = i; /* clockwise */
        pdata.line_indexes[i] = i;
    }
	
	pdata.floor_texture = NONE;
    pdata.ceiling_texture = NONE;
	pdata.floor_height = 0;
    pdata.ceiling_height = WORLD_ONE;
	pdata.floor_lightsource_index = NONE;
    pdata.ceiling_lightsource_index = NONE;
	
//	pdata.area; /* in world_distance^2 units */
	
	pdata.first_object = NONE;
	
//	pdata.first_exclusion_zone_index;
//	pdata.line_exclusion_zone_count;
//	pdata.point_exclusion_zone_count;

	pdata.floor_transfer_mode = 0;
	pdata.ceiling_transfer_mode = 0;
	
//	pdata.adjacent_polygon_indexes[MAXIMUM_VERTICES_PER_POLYGON];
	
	pdata.first_neighbor_index = NONE;
	pdata.neighbor_count = 0;
	
    //
//    pdata.center;
	
//	pdata.side_indexes[MAXIMUM_VERTICES_PER_POLYGON];
	
//	pdata.floor_origin;
//  pdata.ceiling_origin;
	
	pdata.media_index = NONE;
	pdata.media_lightsource_index = NONE;
	
	pdata.sound_source_indexes = NONE;
	
	pdata.ambient_sound_image_index = NONE;
	pdata.random_sound_image_index = NONE;
	
    return pdata;
}
/**
    独立したポリゴンデータを追加します
*/
void hpl::aleph::map::addNewPolygon(polygon_data& pdata, endpoint_data epd[],
                                    line_data ld[], int n)
{
    //点
    std::map<int,int> epIndexTable;
    std::string str;
    for(int i = 0; i < n; i ++){
        EndpointList.push_back(epd[i]);
        dynamic_world->endpoint_count ++;
        int newIndex = EndpointList.size() - 1;
        epIndexTable[i] = newIndex;

/*        char buf[256];
        sprintf(buf, "%d,", newIndex);
        str += std::string(buf);
        const char *bauf = str.c_str();
        const char *baauf = str.c_str();*/
    }
//    const char *buf = str.c_str();

    std::map<int,int> lIndexTable;
    for(int i = 0; i < n; i ++){
        //修正
        for(int j = 0; j < 2; j ++){
            ld[i].endpoint_indexes[j] = epIndexTable[ld[i].endpoint_indexes[j]];
        }

        LineList.push_back(ld[i]);
        dynamic_world->line_count ++;
        int newIndex = LineList.size() - 1;
        lIndexTable[i] = newIndex;
    }
    
    //ポリゴン
    for(int i = 0; i < n; i ++){
        pdata.endpoint_indexes[i] = epIndexTable[pdata.endpoint_indexes[i]];
    }
    for(int i = 0; i < n - 1; i ++){
        pdata.line_indexes[i] = lIndexTable[pdata.line_indexes[i]];
    }
    PolygonList.push_back(pdata);
    dynamic_world->polygon_count ++;

    int newPolygonIndex = PolygonList.size() - 1;
    for(int i = 0; i < n; i ++){
        int newIndex = epIndexTable[i];
        endpoint_data* ep = &(EndpointList[newIndex]);//get_endpoint_data(newIndex);
        ep->supporting_polygon_index = newPolygonIndex;
    }
    for(int i = 0; i < n - 1; i ++){
        int newIndex = lIndexTable[i];
        line_data* l = &(LineList[newIndex]);
        l->clockwise_polygon_owner = newPolygonIndex;
    }
   
}
void hpl::aleph::map::addNewPolygon(world_distance points[][2], int n)
{
    world_point2d pt[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < n; i ++){
        pt[i].x = points[i][0];
        pt[i].y = points[i][1];
    }
    hpl::aleph::map::addNewPolygon(pt, n);
}
void hpl::aleph::map::addNewPolygon(world_point2d points[], int n)
{
    endpoint_data epd[MAXIMUM_VERTICES_PER_POLYGON];
    line_data ld[8];
    polygon_data pdata = hpl::aleph::map::createPolygon(points, epd, ld, n);
    hpl::aleph::map::addNewPolygon(pdata, epd, ld, n);
}

/**
    二つの線が織り成す角度を求めます
    @param pIndexA1,2 線分A1-A2の点インデックス
    @param pIndexB1,2 線分B1-B2の点インデックス
*/
double hpl::aleph::map::getTwoLinesDegree(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2)
{
    //degreeにします
    double rad = hpl::aleph::map::getTwoLinesRadian(pIndexA1, pIndexA2, pIndexB1, pIndexB2);
    double deg = hpl::math::getDegreeFromRadian(rad);
    return deg;
}
double hpl::aleph::map::getTwoLinesRadian(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2)
{
    //radianで求めます
    endpoint_data *a1 = get_endpoint_data(pIndexA1);
    endpoint_data *a2 = get_endpoint_data(pIndexA2);
    endpoint_data *b1 = get_endpoint_data(pIndexB1);
    endpoint_data *b2 = get_endpoint_data(pIndexB2);
    double rad = hpl::math::getTwoLinesRadian(a1->vertex.x, a1->vertex.y,
        a2->vertex.x, a2->vertex.y,
        b1->vertex.x, b1->vertex.y,
        b2->vertex.x, b2->vertex.y);
    return rad;
}

/**
    指定した点がポリゴンの中に存在するかどうかを確かめます
    @
*/
bool hpl::aleph::map::isPointInPolygon(int viewPX, int viewPY, int polygonIndex,
                                       int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety)
{
    //ワールド座標に変換します
    world_point2d wpoint = hpl::aleph::map::getWorldPoint2DFromViewPoint(viewPX, viewPY, 
        offsetXWorld, offsetYWorld, zoomDivision, offsetx, offsety);
    double points[MAXIMUM_VERTICES_PER_POLYGON][2];
    //ポリゴン情報を得ます
    polygon_data* poly = get_polygon_data(polygonIndex);
    int n = poly->vertex_count;
    for(int i = 0; i < n; i ++){
        endpoint_data* ep = get_endpoint_data(poly->endpoint_indexes[i]);
        points[i][0] = ep->vertex.x;
        points[i][1] = ep->vertex.y;
    }
    //位置検査します
    bool isPointIn = hpl::math::isPointInPolygon(wpoint.x, wpoint.y, points, n);
    return isPointIn;
}


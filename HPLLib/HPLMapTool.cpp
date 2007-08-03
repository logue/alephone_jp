﻿#include "HPLMapTool.h"
#include "HPLMath.h"
#include <limits.h>
#include "HPLQuickSort.h"
#include <fstream>
#include <set>
#include "HPLError.h"
#include "HPLStringModifier.h"
#include "HPLStockManager.h"

#include "platforms.h"

//文字列仮読み込みのサイズ
//<en>size for buffering string
const int BUF_MAX = 1024;

//色情報の区切り文字
static char* COLOR_ITEM_SEPARATER = ",";
//色情報の次元
const int COL_NUM = 3;

int getKeyByValue(std::map<int, int>& indexMap, int targetValue)
{
	for(std::map<int, int>::iterator it = indexMap.begin(); it != indexMap.end(); it ++){
		if(it->second == targetValue){
			return it->first;
		}
	}
	hpl::error::halt("index not found");
	return 0;
}


/**
    直線距離を求めます
*/
static double getLengthDouble(double x, double y)
{
    double length = (double)sqrt((double)(x * x + y * y));
    return length;
}

/**
*/
void hpl::aleph::loadInformation(const char* filePath, int maxLines, hpl::aleph::Information infos[])
{
    std::ifstream ifs(filePath);
    if(!ifs.is_open()){
#ifdef __WXDEBUG__
        wxASSERT(ifs.is_open());
#else
        hpl::error::halt("Fail to open tag file:%s", filePath);
#endif
    }
    int lineCounter = 0;
    char buf[BUF_MAX];
    while((ifs.getline(buf, BUF_MAX)) != NULL){
        if(strcmp(buf, "") == 0){
            continue;
        }
        //stringにする
        infos[lineCounter].jname = std::string(buf);
        lineCounter ++;
        if(lineCounter >= maxLines){
            break;
        }
    }
    ifs.close();
}

/**
	バインド型の文字列だけをファイルから読み込みます。
	割り当て番号は設定されません
*/
void hpl::aleph::loadInformation(const char* filePath, int maxLines, hpl::aleph::InformationBinded infos[])
{
    std::ifstream ifs(filePath);
    if(!ifs.is_open()){
#ifdef __WXDEBUG__
        wxASSERT(ifs.is_open());
#else
        hpl::error::halt("Fail to open tag file:%s", filePath);
#endif
    }
    int lineCounter = 0;
    char buf[BUF_MAX];
    while((ifs.getline(buf, BUF_MAX)) != NULL){
        if(strcmp(buf, "") == 0){
            continue;
        }
        //stringにする
        infos[lineCounter].jname = std::string(buf);
        lineCounter ++;
        if(lineCounter >= maxLines){
            break;
        }
    }
    ifs.close();
}

/**
	指定した値に相当するインデックス値を取得します
	存在しないなどの理由により失敗した場合は、負数が返されます
*/
int hpl::aleph::getIndexFromInformationBinded(int value, hpl::aleph::InformationBinded infos[], int max)
{
	for(int i = 0; i < max; i ++){
		if(infos[i].bind == value){
			return i;
		}
	}
	return -1;
}

/**
    カラーデータをファイルから読み込みます
    @return 失敗時に偽
*/
bool hpl::aleph::loadColorSetting(const char* filePath, int colors[][3], int max)
{
    const char* fname = filePath;
    std::ifstream ifs(fname);
    if(!ifs.is_open()){
        hpl::error::halt("Couldn't open Color setting[%s]", fname);
    }
    char buf[BUF_MAX];
    int count = 0;
    while(ifs.getline(buf, BUF_MAX)){
        std::string line = std::string(buf);
        if(line.compare("") == 0){
            continue;
        }
        std::vector<std::string> sp = hpl::string::Split(line, COLOR_ITEM_SEPARATER);
        if(sp.size() < COL_NUM){
            hpl::error::halt("Color setting format is invalid:%s", line.c_str());
        }
        for(int i = 0; i < COL_NUM; i ++){
            colors[count][i] = atoi(sp[i].c_str());
        }
        count ++;
        if(count >= max){
            break;
        }
    }
    ifs.close();
    return true;
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
/**
    指定した場所に点があるかどうかを得ます
    @return その場所に点があればそのインデックスがかえります。
        なければNONE
*/
int hpl::aleph::map::getSelectPointIndex(world_point2d& wpoint,
                                         int threshold, int zMin, int zMax, int div,
                                         hpl::aleph::HPLStockManager* smgr)
{
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* ep = get_endpoint_data(i);
        //高さチェック
        if(!hpl::aleph::map::isValidHeight(ep->highest_adjacent_floor_height, ep->lowest_adjacent_ceiling_height,  zMin, zMax)){
            continue;
        }
        //削除チェック
        if(smgr->isDeletePoint(i)){
            continue;
        }
        if(hpl::aleph::map::isSelectPoint(wpoint, ep->vertex, threshold * div)){
            return i;
        }
    }
    return NONE;
}
int hpl::aleph::map::getSelectPointIndex(int viewX, int viewY, int threshold, int zMin, int zMax,
        int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
        hpl::aleph::HPLStockManager* smgr)
{
    world_point2d wpoint = hpl::aleph::map::getWorldPoint2DFromViewPoint(viewX, viewY, offsetXW, offsetYW, div,
        voffsetX, voffsetY);
    int index = hpl::aleph::map::getSelectPointIndex(wpoint, threshold, zMin, zMax, div, smgr);
    return index;
}

/**
    ある高さが規定範囲内にあるかを確かめます
    @return ある高度の範囲が規定範囲と共有する部分を持たない場合負
*/
bool hpl::aleph::map::isValidHeight(int checkMin, int checkMax, int validMin, int validMax)
{
    if(checkMin > checkMax || checkMin > validMax || checkMax < validMin){
        //・高さ指定が逆
        //・床が許容範囲より上にある
        //・天井が許容範囲より下にある
        //→以上の場合規定範囲外（不正）とみなす
        return false;
    }else{
        return true;
    }
}
/**
    指定した点が線を踏んでいる場合、その点
*/
int hpl::aleph::map::getSelectLineIndex(world_point2d& wpoint,
                                        int threshold, int zMin, int zMax, int div,
                                        hpl::aleph::HPLStockManager* smgr)
{
    for(int i = 0; i < (int)LineList.size(); i ++){
        line_data* line = get_line_data(i);
        //高さチェック
        if(!hpl::aleph::map::isValidHeight(line->highest_adjacent_floor, line->lowest_adjacent_ceiling,
            zMin, zMax))
        {
            continue;
        }
        if(smgr->isDeleteLine(i)){
            continue;
        }
        int *a = NULL;
        endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
        if(!begin)delete a;
        endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
        if(!end)delete a;

        //選択しているか判定
        if(hpl::aleph::map::isSelectLine(wpoint, begin->vertex, end->vertex, 
            threshold, div)){
            //選択できている（online）
            return i;
        }
    }
    return NONE;
}
int hpl::aleph::map::getSelectLineIndex(int viewX, int viewY, int threshold, int zMin, int zMax,
        int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
        hpl::aleph::HPLStockManager* smgr)
{
    world_point2d wpoint = hpl::aleph::map::getWorldPoint2DFromViewPoint(viewX, viewY, offsetXW, offsetYW, div,
        voffsetX, voffsetY);
    int index = hpl::aleph::map::getSelectLineIndex(wpoint,
        threshold , zMin, zMax, div, smgr);
    return index;
}

/**
	指定した点がポリゴンを踏んでいる場合、そのポリゴンを返します
*/
int hpl::aleph::map::getSelectPolygonIndex(int viewX, int viewY, int zMin, int zMax,
	int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
	hpl::aleph::HPLStockManager* smgr)
{
	for(int i = 0; i < (int)PolygonList.size(); i ++){
		polygon_data* poly = get_polygon_data(i);
		//削除チェック
		if(smgr->isDeletePolygon(i)){
			continue;
		}
		//高さチェック
		if(!hpl::aleph::map::isValidHeight(poly->floor_height, poly->ceiling_height,
            zMin, zMax))
        {
			continue;
		}
		//選択出来ているか判定
		if(hpl::aleph::map::isPointInPolygon(viewX, viewY,
            i, offsetXW, offsetYW, div,
            voffsetX, voffsetY))
		{
			return i;
		}
	}
	return NONE;
}
int hpl::aleph::map::getSelectAnnotationIndex(int viewX, int viewY, int threshold, int zMin, int zMax,
        int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
                                        hpl::aleph::HPLStockManager* smgr)
{
	for(int i = 0; i < (int)MapAnnotationList.size(); i ++){
		map_annotation* annotation = &MapAnnotationList[i];
		//選択出来ているか判定
		if(hpl::aleph::map::isSelectPoint(viewX, viewY,
            annotation->location.x, annotation->location.y, voffsetX, voffsetY,
			offsetXW, offsetYW, div, threshold))
		{
			return i;
		}
	}
	return NONE;
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
    //ビュー座標に変換
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
                  int distance, int div)
{
    bool isSelect = hpl::math::isNearbyPointToLine(point.x, point.y,
        linePoint0.x, linePoint0.y, linePoint1.x, linePoint1.y, distance * div);
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
		ポリゴンやSideの修正は別でやること。
		スタックオーバーフローの温床
    <en>Fix line_data up
//    @param isDeleteOldSide descide which deletes or not 使われていない壁情報を削除するか
*/
void hpl::aleph::map::fixLine(int index,// bool isDeleteOldSide,
							  hpl::aleph::HPLStockManager* smgr)
{
    line_data* line = get_line_data(index);
#ifdef __WXDEBUG__
	wxASSERT(line);
#endif


	//endpoint_indexes
	//flags
	//length
	line->length = hpl::aleph::map::getLineLength(index);
	//ポリゴン・Sideの整合性調整
	{
		//削除されていたらNONEにする
		//clockwise
		if(hpl::aleph::map::isValidIndex(line->clockwise_polygon_owner, PolygonList.size()) &&
			smgr->isDeletePolygon(line->clockwise_polygon_owner))
		{
			line->clockwise_polygon_owner = NONE;
		}
		if(!hpl::aleph::map::isValidIndex(line->clockwise_polygon_owner, PolygonList.size()))
		{
			//ポリゴンが存在しないのでSideも消す
			if(hpl::aleph::map::isValidIndex(line->clockwise_polygon_side_index,
				SideList.size()))
			{
				smgr->deleteSide(line->clockwise_polygon_side_index);
				line->clockwise_polygon_side_index = NONE;
			}
		}
		//counter-clockwise
		if(hpl::aleph::map::isValidIndex(line->counterclockwise_polygon_owner, PolygonList.size()) &&
			smgr->isDeletePolygon(line->counterclockwise_polygon_owner))
		{
			line->counterclockwise_polygon_owner = NONE;
		}
		if(!hpl::aleph::map::isValidIndex(line->counterclockwise_polygon_owner,
			PolygonList.size()))
		{
			//ポリゴンは存在しないので消す
			if(hpl::aleph::map::isValidIndex(line->counterclockwise_polygon_side_index,
				PolygonList.size()))
			{
				smgr->deleteSide(line->counterclockwise_polygon_side_index);
				line->counterclockwise_polygon_side_index = NONE;
			}
		}
	}
	//height
    //	theMapLevel.theSides.SetupSide(leftPoly, rightPoly, &theLine->leftSide, index, deleteOldSides);
/*    hpl::aleph::map::setupSide(leftPolyIndex, rightPolyIndex,
        line->left_side, index, isDeleteOldSide);
    hpl::aleph::map::setupSide(rightPolyIndex, leftPolyIndex,
        line->right_side, index, isDeleteOldSide);
*/
    polygon_data* counterClockPoly = get_polygon_data(line->counterclockwise_polygon_owner);
    polygon_data* clockPoly = get_polygon_data(line->clockwise_polygon_owner);
	if(counterClockPoly && clockPoly){
		//両側にポリゴンがある
		//高いほう・低いほうを高さとする。
		line->highest_adjacent_floor = MAX(
			counterClockPoly->floor_height,
			clockPoly->floor_height);
		line->lowest_adjacent_ceiling = MIN(
			counterClockPoly->ceiling_height,
			clockPoly->ceiling_height);
	}else if(counterClockPoly && !clockPoly){
		//左にあって右に無い
        line->highest_adjacent_floor = counterClockPoly->floor_height;
        line->lowest_adjacent_ceiling = counterClockPoly->ceiling_height;
	}else if(!counterClockPoly && clockPoly){
		//右にあって左に無い
        line->highest_adjacent_floor = clockPoly->floor_height;
        line->lowest_adjacent_ceiling = clockPoly->ceiling_height;
    }else{
		//両方無い
        line->highest_adjacent_floor = 0;
        line->lowest_adjacent_ceiling = 0;
    }

/*
	TODO 真相解明
	if(counterClockPolyIndex == NONE && clockPolyIndex != NONE){
		//片方がある場合はかならず左側にポリゴンが来るようにするの？
        //reverse
        int temp;
        temp = line->endpoint_indexes[0];
        line->endpoint_indexes[0] = line->endpoint_indexes[1];
        line->endpoint_indexes[1] = temp;
        hpl::math::exchange<int16>(&line->counterclockwise_polygon_side_index, &line->clockwise_polygon_side_index);
        hpl::math::exchange<int16>(&line->counterclockwise_polygon_owner, &line->clockwise_polygon_owner);
    }*/

}

/**
    ポリゴン情報を修正します
*/
void hpl::aleph::map::fixPolygon(int pindex,
	hpl::aleph::HPLStockManager* smgr)
{
	polygon_data* poly = get_polygon_data(pindex);
#ifdef __WXDEBUG__
	wxASSERT(poly);
#endif
	//types
	//flags
	//TODO permutation
	//vertex_count
	int num = poly->vertex_count;
	//endpoint_indexes
	//line_indexes
	//floor_texture,ceiling_texture
	//floor_height,ceiling_height
	//TODO 無かったらNONE floor_lightsource_index,ceiling_lightsource_index
	//area
	double points[MAXIMUM_VERTICES_PER_POLYGON][2];
	for(int i = 0; i < num; i ++){
		endpoint_data* ep = get_endpoint_data(poly->endpoint_indexes[i]);
#ifdef __WXDEBUG__
		wxASSERT(ep);
#endif
		points[i][0] = ep->vertex.x;
		points[i][1] = ep->vertex.y;
	}
	double area = hpl::math::getPolygonArea(points, num);
	poly->area = area;

	//first_object
	if(hpl::aleph::map::isValidIndex(poly->first_object, SavedObjectList.size())){
		//オブジェクトが存在する
		if(smgr->isDeleteObject(poly->first_object)){
			//対象が消えていた
			//ほかのオブジェクトを探す
			bool found = false;
			for(int i = 0; i < (int)SavedObjectList.size(); i ++){
				if(smgr->isDeleteObject(i)){
					continue;
				}
				map_object* obj = &SavedObjectList[i];
				if(obj->polygon_index == pindex){
					found = true;
					//見つかった
					//そのオブジェクトを指定する
					poly->first_object = i;
					break;
				}
			}
			if(found){
				
			}else{
				//見つからない
				//NONEとする
				poly->first_object = NONE;
			}
		}
	}

	/*
	TODO ???
	int16 first_exclusion_zone_index;
	int16 line_exclusion_zone_count;
	int16 point_exclusion_zone_count;
	int16 floor_transfer_mode;
	int16 ceiling_transfer_mode;
	*/

	//隣接関係
	//for adjacents
	int neighbourCount = 0;
	int firstNeighbour = NONE;
	bool isFirst = true;
	for(int i = 0; i < num; i ++){
		line_data* line = get_line_data(poly->line_indexes[i]);
#ifdef __WXDEBUG__
		wxASSERT(line);
#endif
		//線の時計回りが隣接する他のポリゴンである場合真
		bool isClockwiseNeighbour = true;
		int adjacentPolyIndex = line->clockwise_polygon_owner;
		if(adjacentPolyIndex == pindex){
			//それ自分方向だよ
			adjacentPolyIndex = line->counterclockwise_polygon_owner;
			isClockwiseNeighbour = false;
		}
		if(hpl::aleph::map::isValidIndex(adjacentPolyIndex, PolygonList.size())){
			//その番号は存在する
			if(smgr->isDeletePolygon(adjacentPolyIndex)){
				//削除されている
				adjacentPolyIndex = NONE;
				if(isClockwiseNeighbour){
					if(line->clockwise_polygon_side_index != NONE){
						//Sideも消す
						smgr->deleteSide(line->clockwise_polygon_side_index);
						line->clockwise_polygon_side_index = NONE;
					}
				}else{
					if(line->counterclockwise_polygon_side_index != NONE){
						//Sideも消す
						smgr->deleteSide(line->counterclockwise_polygon_side_index);
						line->counterclockwise_polygon_side_index = NONE;
					}
				}
			}
		}else{
			//NONEとする
			if(isClockwiseNeighbour){
				line->clockwise_polygon_side_index = NONE;
				line->clockwise_polygon_owner = NONE;
			}else{
				line->counterclockwise_polygon_side_index = NONE;
				line->counterclockwise_polygon_owner = NONE;
			}
		}
		if(hpl::aleph::map::isValidIndex(adjacentPolyIndex, PolygonList.size())){
			neighbourCount ++;
			if(isFirst){
				isFirst = false;
				firstNeighbour = adjacentPolyIndex;
			}
		}
		poly->adjacent_polygon_indexes[i] = adjacentPolyIndex;

		//自分方向のSideもチェック
		if(isClockwiseNeighbour){
			if(hpl::aleph::map::isValidIndex(line->counterclockwise_polygon_side_index,
				SideList.size()) &&
				smgr->isDeleteSide(line->counterclockwise_polygon_side_index))
			{
				//もともと存在してる＆消されている
				//NONEとする
				line->counterclockwise_polygon_side_index = NONE;
			}
			poly->side_indexes[i] = line->counterclockwise_polygon_side_index;
		}else{
			if(hpl::aleph::map::isValidIndex(line->clockwise_polygon_side_index,
				SideList.size()) &&
				smgr->isDeleteSide(line->clockwise_polygon_side_index))
			{
				line->clockwise_polygon_side_index = NONE;
			}
			poly->side_indexes[i] = line->clockwise_polygon_side_index;
		}
	}
	poly->neighbor_count = neighbourCount;
	poly->first_neighbor_index = firstNeighbour;

	//center
	double center[2];
	hpl::math::getPolygonCentroid(points, num, center);
	poly->center.x = (int)center[0];
	poly->center.y = (int)center[1];

	//TODO floor_origin, ceiling_origin
	/*
	TODO 存在しなかったらNONE
	int16 media_index;
	int16 media_lightsource_index;
	
	int16 sound_source_indexes;
	
	// either can be NONE
	int16 ambient_sound_image_index;
	int16 random_sound_image_index;
	*/
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

/**
	点を共有する線インデックスのリストを取得します
*/
std::vector<int> hpl::aleph::map::getLineIndexesIncludePoint(int endpointIndex)
{
	std::vector<int> lineIndexes;
	for(int i = 0; i < (int)LineList.size(); i ++){
		line_data* line = get_line_data(i);
		if(line->endpoint_indexes[0] == endpointIndex ||
			line->endpoint_indexes[1] == endpointIndex)
		{
			lineIndexes.push_back(i);
		}
	}
	return lineIndexes;
}

/**
	線を共有するポリゴンのリストを取得します
*
std::vector<int> hpl::aleph::map::getPolygonIndexesIncludeLine(int lineIndex)
{
	std::vector<int> polygonIndexes;
	for(int i = 0; i < (int)LineList.size(); i ++){
		polygon_data* polygon = get_polygon_data(i);
		//頂点の数
		int n = polygon->vertex_count;

		for(int i = 0; i < n; i ++){
			if(polygon->line_indexes[i] == lineIndex)
			{
				polygonIndexes.push_back(i);
				break;
			}
		}
	}
	return polygonIndexes;
}
*/
/**
	点を共有するポリゴンのリストを取得します
*/
std::vector<int> hpl::aleph::map::getPolygonIndexesIncludePoint(int endpointIndex)
{
	std::vector<int> polygonIndexes;
	for(int i = 0; i < (int)PolygonList.size(); i ++){
		polygon_data* polygon = get_polygon_data(i);
		//頂点の数
		int n = polygon->vertex_count;

		for(int i = 0; i < n; i ++){
			if(polygon->endpoint_indexes[i] == endpointIndex)
			{
				polygonIndexes.push_back(i);
				break;
			}
		}
	}
	return polygonIndexes;
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
            line_data* line = get_line_data(sellines->at(i).index);
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

			if(hpl::aleph::map::isPointInPolygon(px, py, selpolygons->at(i).index,
				offsetWorldX, offsetWorldY, div, offsetViewX, offsetViewY))
			{
				//point_in_polygon(selpolygons->at(i).index, &world_point)){
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
	if(!hpl::aleph::map::isValidIndex(index, PolygonList.size())){
		return false;
	}
    //TODO
    //ポリゴン情報を取得します
    polygon_data *polygon = get_polygon_data(index);

    //線の並びが正しいかチェック
    int vertexCount = polygon->vertex_count;
    double points[MAXIMUM_VERTICES_PER_POLYGON][2];
    for(int i = 0; i < vertexCount; i ++){
		endpoint_data* ep = get_endpoint_data(polygon->endpoint_indexes[i]);
		points[i][0] = ep->vertex.x;
		points[i][1] = ep->vertex.y;
    }
    bool isValid = hpl::math::isValidPolygon(points, vertexCount);
	return isValid;
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
	bool isPointIn = hpl::aleph::map::isPointInPolygon(wpoint, polygonIndex);
	return isPointIn;
}

bool hpl::aleph::map::isPointInPolygon(world_point2d& wpoint, int polygonIndex)
{
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


/**
    簡略バージョン
*/
void hpl::aleph::map::createPoint(world_point2d& wpoint, endpoint_data* ep)
{
    //TODO
    ep->flags = 1;
    ep->vertex.x = wpoint.x;
    ep->vertex.y = wpoint.y;
    
    ep->highest_adjacent_floor_height = 0;
    ep->lowest_adjacent_ceiling_height = WORLD_ONE;
    ep->supporting_polygon_index = NONE;
}
/**
    @param polyIndex 載せるポリゴンのインデックス
*/
void hpl::aleph::map::createObject(world_point2d& wpoint, int polyIndex, map_object* obj,
                                   int flags, int type, int index)
{
    //TODO
    obj->polygon_index = polyIndex;
    obj->location.x = wpoint.x;
    obj->location.y = wpoint.y;
    polygon_data* poly = get_polygon_data(polyIndex);
#ifdef __WXDEBUG__
    wxASSERT(poly);
#else
    if(poly == NULL){
        hpl::error::halt("poly[%d] doesn't exist", polyIndex);
    }
#endif
    //TODO flag?
    if(flags & _map_object_hanging_from_ceiling){
        obj->location.z = poly->ceiling_height;
    }else{
        obj->location.z = poly->floor_height;
    }
    obj->flags = flags;
}

void hpl::aleph::map::createLine(int beginPointIndex, int endPointIndex, line_data* line)
{
    endpoint_data* begin = get_endpoint_data(beginPointIndex);
    endpoint_data* end = get_endpoint_data(endPointIndex);
    if(begin == NULL || end == NULL){
        hpl::error::halt("begin / end endpoint doesn't exist");
    }
    line->clockwise_polygon_owner = NONE;
    line->clockwise_polygon_side_index = NONE;
    line->counterclockwise_polygon_owner = NONE;
    line->counterclockwise_polygon_side_index = NONE;
    line->endpoint_indexes[0] = beginPointIndex;
    line->endpoint_indexes[1] = endPointIndex;
    line->flags = SOLID_LINE_BIT;
    //TODO 点のうち高い方のフロア高度
    line->highest_adjacent_floor = MIN(begin->highest_adjacent_floor_height,
        end->highest_adjacent_floor_height);
    line->lowest_adjacent_ceiling = MAX(begin->lowest_adjacent_ceiling_height,
        end->lowest_adjacent_ceiling_height);
}

void hpl::aleph::map::createPolygon(int pointIndexes[], int n, polygon_data* poly)
{
    endpoint_data* ep[MAXIMUM_VERTICES_PER_POLYGON];

    //点の登録
    for(int i = 0; i < n; i ++){
        ep[i] = get_endpoint_data(pointIndexes[i]);
#ifdef __WXDEBUG__
        wxASSERT(ep[i]);
#else
        if(ep[i] == NULL){
            hpl::error::halt("endpoint[%d] doesn't exist", pointIndexes[i]);
        }
#endif
        poly->endpoint_indexes[i] = pointIndexes[i];
    }
    for(int i = 0; i < n; i ++){
        int next = i + 1;
        if(i == n - 1){
            next = 0;
        }
        int lIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(pointIndexes[i], pointIndexes[next]);
#ifdef __WXDEBUG__
        wxASSERT(hpl::aleph::map::isValidIndex(lIndex, LineList.size()));
#else
        if(!hpl::aleph::map::isValidIndex(lIndex, LineList.size())){
            hpl::error::halt("endpoint[%d] doesn't exist", pointIndexes[i]);
        }
#endif
        poly->line_indexes[i] = lIndex;
        poly->side_indexes[i] = NONE;
    }
    //TODO
    //poly->adjacent_polygon_indexes = NONE;
    poly->ambient_sound_image_index = NONE;
    //TODO area?
    poly->area = 0;
    //TODO 点のうち一番高い高度
    poly->ceiling_height = WORLD_ONE;
    poly->floor_height = 0;
    poly->ceiling_lightsource_index = NONE;
    //TODO ?
    poly->ceiling_origin.x = 0;
    poly->ceiling_origin.y = 0;
    poly->ceiling_texture = NONE;
    //TODO ?
    poly->ceiling_transfer_mode = 0;
    //TODO center?
    poly->center.x = 0;
    poly->center.y = 0;
    //TODO ZONE?
    poly->first_exclusion_zone_index = NONE;
    poly->line_exclusion_zone_count = 0;
    poly->point_exclusion_zone_count = 0;
    //TODO ?
    poly->first_neighbor_index = NONE;
    poly->first_object = NONE;
    //TODO flags?
    poly->flags = 0;
    poly->media_index = NONE;
    poly->media_lightsource_index = NONE;
    //TODO count 線の反対側の
    poly->neighbor_count = 0;
    //TODO ?
    poly->permutation = 0;
    poly->random_sound_image_index = NONE;
    //poly->side_indexes[0] = NONE;
    //poly->sound_source_indexes;
    poly->type = _polygon_is_normal;
    poly->vertex_count = n;
}

/**
    選択データにオフセットを設定します。
    @param mx, my マウス座標
    @param sel 選択データ
*/
void hpl::aleph::map::setupSelectDataGroupOffsets(int mx, int my, 
    hpl::aleph::map::HPLSelectData* sel, 
    int voffsetX, int voffsetY, int woffsetX, int woffsetY, int div)
{
    //点 <en> points
    for(int i = 0; i < (int)sel->getSelPoints()->size(); i ++){
        endpoint_data* ep = get_endpoint_data(sel->getSelPoints()->at(i).index);
        //ビュー座標に変換
        int vpoint[2];
        hpl::aleph::map::getViewPointFromWorldPoint2D(ep->vertex, vpoint,
            woffsetX, woffsetY, div, voffsetX, voffsetY);

        //引き算
        sel->getSelPoints()->at(i).offset[0] = vpoint[0] - mx;
        sel->getSelPoints()->at(i).offset[1] = vpoint[1] - my;
    }

    //線 <en> lines
    for(int i = 0; i < (int)sel->getSelLines()->size(); i ++){
        line_data* line = get_line_data(sel->getSelLines()->at(i).index);
        endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);
        int vpointStart[2];
        int vpointEnd[2];
        hpl::aleph::map::getViewPointFromWorldPoint2D(begin->vertex, vpointStart,
            woffsetX, woffsetY, div, voffsetX, voffsetY);
        hpl::aleph::map::getViewPointFromWorldPoint2D(end->vertex, vpointEnd,
            woffsetX, woffsetY, div, voffsetX, voffsetY);

        //オフセット設定
        sel->getSelLines()->at(i).offset[0][0] = vpointStart[0] - mx;
        sel->getSelLines()->at(i).offset[0][1] = vpointStart[1] - my;
        sel->getSelLines()->at(i).offset[1][0] = vpointEnd[0] - mx;
        sel->getSelLines()->at(i).offset[1][1] = vpointEnd[1] - my;
    }

    //ポリゴン
    for(int i = 0; i < (int)sel->getSelPolygons()->size(); i ++){
        hpl::aleph::map::SelPolygon* selpoly = &sel->getSelPolygons()->at(i);
        polygon_data* poly = get_polygon_data(selpoly->index);
#ifdef __WXDEBUG__
        wxASSERT(poly);
#else
#endif
        int n = poly->vertex_count;
        selpoly->num = n;
        for(int j = 0; j < n; j ++){
            int vpoint[2];
            endpoint_data* ep = get_endpoint_data(poly->endpoint_indexes[j]);
#ifdef __WXDEBUG__
            wxASSERT(ep);
#else
#endif
            hpl::aleph::map::getViewPointFromWorldPoint2D(ep->vertex, vpoint,
                woffsetX, woffsetY, div, voffsetX, voffsetY);

            //オフセット
            selpoly->offset[j][0] = vpoint[0] - mx;
            selpoly->offset[j][1] = vpoint[1] - my;
        }
    }

    //オブジェクト
    for(int i = 0; i < (int)sel->getSelObjects()->size(); i ++){
        map_object* obj = &SavedObjectList[sel->getSelObjects()->at(i).index];
        //ビュー座標に変換
        int vpoint[2];
        world_point2d worldP = {obj->location.x, obj->location.y};
        hpl::aleph::map::getViewPointFromWorldPoint2D(worldP, vpoint,
            woffsetX, woffsetY, div, voffsetX, voffsetY);

        //引き算
        sel->getSelObjects()->at(i).offset[0] = vpoint[0] - mx;
        sel->getSelObjects()->at(i).offset[1] = vpoint[1] - my;
    }
}

////////////////////////////////////////////////
//////// objects ///////////////////////////////
/**
	初期配置数の設定
	@param objectType オブジェクトタイプ
		_saved_item
		_saved_monster
	@param index どのオブジェクトの初期は位置をいじるか
	@param num 増減させる値
	@return 増減の結果の数
*
int hpl::aleph::map::addInitialPlacementNum(int objectType, int index, int num)
{
	struct object_frequency_definition* place = hpl::aleph::map::getPlacementData(objectType, index);
	if(place){
		place->initial_count += num;
        return place->initial_count;
	}else{
		return NONE;
	}
}*/
/**
	配置情報を取得
	@param objectType オブジェクトタイプ
		_saved_item
		_saved_monster
	@param index どのオブジェクトの初期は位置をいじるか
	@return 配置情報。配置数やランダムマックスなど
*/
struct object_frequency_definition* hpl::aleph::map::getPlacementData(int objectType, int index)
{
    if(item_placement_info == NULL || monster_placement_info == NULL){
	    item_placement_info = object_placement_info;
	    monster_placement_info = object_placement_info+MAXIMUM_OBJECT_TYPES;

	    /* Clear the arrays */
	    objlist_clear(object_placement_info, 2*MAXIMUM_OBJECT_TYPES);
    }
	struct object_frequency_definition* place = NULL;
	if(objectType == _saved_item && item_placement_info){
		place = &item_placement_info[index];
	}else if(objectType == _saved_monster && monster_placement_info){
		place = &monster_placement_info[index];
	}
	return place;
}

/**
	指定したType/Indexの数を求めます
*/
int hpl::aleph::map::getObjectCount(int type, int index)
{
	int counter = 0;
	for(int i = 0; i < (int)SavedObjectList.size(); i ++){
		map_object* obj = &SavedObjectList[i];
		if(obj->type == type && obj->index == index){
			counter ++;
		}
	}
	return counter;
}

/**
	特定のType/Indexの数を調べ、initial値より少ない場合は合わせる
	@return 何か変化が生じた場合真
*/
bool hpl::aleph::map::updateObjectInitialPlacement(int type, int index)
{
	int counter = hpl::aleph::map::getObjectCount(type, index);
	object_frequency_definition* place = hpl::aleph::map::getPlacementData(type, index);
	if(counter > place->initial_count){
		place->initial_count = counter;
		return true;
	}
	return false;
}


///////////////////////////////////
//	Platform
int hpl::aleph::map::getPlatformIndexFromPolygonIndex(
	int polyIndex, hpl::aleph::HPLStockManager* smgr)
{
	for(int i = 0; i < (int)PlatformList.size(); i ++){
		if(smgr->isDeletePlatform(i)){
			continue;
		}
		platform_data* temp = &PlatformList[i];
		if(temp->polygon_index == polyIndex){
			return i;
		}
	}
	return NONE;
}

 
/**
	Check map items' validity
	valid:		[0,n)
	invalid:	-1], [n
	-1ならばNONEなのでInvalid。
	-2],[nの場合そもそもIndexの設定がおかしいのでアサーションをとばす
	削除確認は行わないので注意
	@return -1なら偽。正しい値なら真。
*/
template<class T>
bool hpl::aleph::map::isValidIndex(int index, T numMax)
{
	int n = (int)numMax;
	if(index == NONE){
		return false;
	}else if(n > 0 && index >= 0 && index < n){
		return true;
	}else{
		hpl::error::halt("out of index [%d] (and not NONE=-1) EndpointList.size()=%d",
			index, numMax);
		return false;
	}
}

template bool hpl::aleph::map::isValidIndex(int index, int numMax);
template bool hpl::aleph::map::isValidIndex(int index, size_t numMax);
template bool hpl::aleph::map::isValidIndex(int index, unsigned int numMax);

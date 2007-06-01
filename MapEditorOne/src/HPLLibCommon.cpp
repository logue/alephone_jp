#include "HPLLibCommon.h"
#include <float.h>

#include "HPLLib/HPLAlephLib.h"

static double getInnerProduct(double x0, double y0, double x1, double y1)
{
    double num = x0 * x1 + y0 * y1;
    return num;
}

/**
    calculate degree between two connected lines
*/
double getDegreeBetweenTwoLines(int lineIndex0, int lineIndex1)
{
    endpoint_data *begin0, *end0;
    endpoint_data *begin1, *end1;

    begin0 = get_endpoint_data(get_line_data(lineIndex0)->endpoint_indexes[0]);
    end0 = get_endpoint_data(get_line_data(lineIndex0)->endpoint_indexes[1]);
    begin1 = get_endpoint_data(get_line_data(lineIndex1)->endpoint_indexes[0]);
    end1 = get_endpoint_data(get_line_data(lineIndex1)->endpoint_indexes[1]);

    //cos距離
    //clockwise_endpoint_in_line(
    
    return 0;
}

/**
    check is polygon valid
*/
bool isPolygonValid(int polygonIndex)
{
    return false;
}


/** 
    add annotation text on map
*/
void addAnnotationText(world_point2d& point, string text)
{
    map_annotation annotationData;
    annotationData.type = 0;
    annotationData.location = point;
    strcpy(annotationData.text,// MAXIMUM_ANNOTATION_TEXT_LENGTH,
        text.c_str());
    MapAnnotationList.push_back(annotationData);
}


/**
    search polygon include point stated.
    @return points included in a new or existing valid polygon
        if no points returned, no valid polygon can create or found
*
vector<int> getValidPoligon(world_point2d& point, short maxHeight, short minHeight)
{
    vector<int> points;
    //sort point index
    int pointMax = static_cast<int>(EndpointList.size());
    int* indexes = new int[pointMax];
    int* datas = new int[pointMax];
    //・高さに問題がある点を省く
    //・点がポリゴン内にある場合、そのポリゴンに対応する点は考慮しない
    //　また、そのポリゴンより下にある点については考慮しない
    int* invalidPoints = new int[pointMax];
    int polygonMax = static_cast<int>(PolygonList.size());
    int* includingPolygons = new int[polygonMax];
    for(int i = 0; i < polygonMax; i ++){
		if(hpl::aleph::map::isPointInPolygon(point, i))
		{//point_in_polygon(i, &point)){
        }
    }
    //距離を求めてデータに入れる
    for(int i = 0; i < pointMax; i ++){
        endpoint_data* ep = get_endpoint_data(i);
        //高さが正しいかチェック
        bool invalid = false;
        if(!isPointInHeight(ep, maxHeight, minHeight)){
            invalid = true;
        }
        invalidPoints[i] = invalid ? 1: 0;
        if(invalid){
            datas[i] = INT_MAX;
            continue;
        }
        datas[i] = static_cast<int>(hpl::aleph::map::getPointsDistance(ep->vertex, point));
    }
    sortMap(indexes, pointMax, datas);

    delete datas;
    //近い順に調べていく
    for(int i = 0; i < pointMax; i ++){
        endpoint_data* ep = get_endpoint_data(indexes[i]);
        
        //右回りに進み、角度が180度を超えていないか確かめていく。
    }
    delete invalidPoints;
    delete includingPolygons;
    delete indexes;
    return points;
}

/**
    check which is the polygon valid.
*/
bool isValidPolygon(int polygonIndex)
{
    return false;
}

/**
    get point nearby
    (in the range)
*/
int getNearestPoint(world_point2d& pointFrom, short maxHeight, short minHeight)
{
    double minLength = DBL_MAX;
    int minIndex = -1;
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        //get endpoint data...
        endpoint_data* point = get_endpoint_data(i);
        if(isPointInHeight(point, maxHeight, minHeight)){
            //get length
            double length = hpl::aleph::map::getPointsDistance(point->vertex, pointFrom);
            if(minLength > length){
                minLength = length;
                minIndex = i;
            }
        }
    }
    return minIndex;
}
bool isPointInHeight(endpoint_data* point, short maxHeight, short minHeight)
{
    if(point->highest_adjacent_floor_height >= minHeight &&
        point->lowest_adjacent_ceiling_height <= maxHeight)
    {
        return true;
    }
    return false;
            
}

/**
    get point nearest the one
*/
int getNearestPoint(world_point2d& pointFrom)
{
    double minLength = DBL_MAX;
    int minIndex = -1;
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        //get endpoint data...
        endpoint_data* point = get_endpoint_data(i);

        //get length
        double length = hpl::aleph::map::getPointsDistance(point->vertex, pointFrom);
        if(minLength > length){
            minLength = length;
            minIndex = i;
        }
    }
    return minIndex;
}


/**
//1対1対応のマップをソートする。値側を比較する
    @param indexes インデックス
*
void sortMap(int *indexes, int max, int* datas)
{
    //datasをソート
    int* temp = new int[max];
    int* doneIndex = new int[max];
    //コピー
    memcpy(temp, datas, sizeof(int) * max);
    memset(doneIndex, 0, sizeof(int) * max);

    //quick sort
    hpl::math::qsort::quickSort(temp, max);
    
    for(int i = 0; i < max; i ++){
        int index = 0;
        for(int k = 0; k < max; k ++){
            if(doneIndex[k] == 0 && temp[i] == datas[k]){
                //同率は同率で。
                index = k;
                break;
            }
        }
        indexes[i] = index;
        doneIndex[index] = 1;
    }
    delete doneIndex;
    delete temp;
}

/**
    get point list ordered by length from a point
*
void getPointListLengthOrder(world_point2d& pointFrom, int* indexes)
{
    int max = static_cast<int>(EndpointList.size());
    int* datas = new int[max];
    //代入
    for(int i = 0; i < max; i ++){
        datas[i] = static_cast<int>(hpl::aleph::map::getPointsDistance(pointFrom, get_endpoint_data(i)->vertex));
    }
    //求める
    sortMap(indexes, max, datas);
}

/**
    指定した点と線で繋がっている点を探す
*/
vector<int> getLineSharedPoints(int fromPointIndex)
{
    vector<int> points;

    for(int i = 0; i < static_cast<int>(LineList.size()); i ++){
        line_data* ldata = get_line_data(i);
        if(ldata->endpoint_indexes[0] == fromPointIndex){
            points.push_back(ldata->endpoint_indexes[1]);
        }else if(ldata->endpoint_indexes[1] == fromPointIndex){
            points.push_back(ldata->endpoint_indexes[0]);
        }else{
            //含まれない
        }
    }
    return points;
}


/**
    <jp>指定した点を含む線を取得
    <en>get lines include the point
*/
vector<int> getLineIncludePoint(int pointIndex)
{
    vector<int> lines;
    for(int i = 0; i < static_cast<int>(LineList.size()); i ++){
        line_data* ldata = get_line_data(i);
        if(ldata->endpoint_indexes[0] == pointIndex ||
            ldata->endpoint_indexes[1] == pointIndex)
        {
            lines.push_back(i);
        }
    }
    return lines;
}

/**
    3つの連続する点が成す線の角度が右回りで180度以内か
    [0]始点
    [1]経由点
    [2]終点
*/
bool isThreeClockwisePointsInValidDegree(int pointIndexes[3])
{
    int lineIndex0 = getLineFromPoints(pointIndexes[0], pointIndexes[1]);
    return false;
}

/** 
    <jp>二つの点を持つ線情報を取得します。失敗時は負数
    <en>
    @return -1 when failed
*/
int getLineFromPoints(int point0, int point1)
{
    for(int i = 0; i < static_cast<int>(LineList.size()); i ++){
        line_data* ldata = get_line_data(i);
        if((ldata->endpoint_indexes[0] == point0 &&
            ldata->endpoint_indexes[1] == point1) ||
            (ldata->endpoint_indexes[0] == point1 &&
            ldata->endpoint_indexes[1] == point0))
        {
            return i;
        }
    }
    return -1;
}


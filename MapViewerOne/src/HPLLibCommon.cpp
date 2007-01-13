#include "HPLLibCommon.h"
#include <float.h>

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
bool isSelectPoint(world_point2d &point0, world_point2d &point1,
                   int distance)
{
    //check
    bool isSelect = isNearbyPoints(
        point0.x,point0.y, point1.x, point1.y,
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
bool isSelectLine(world_point2d &point,
                  world_point2d &linePoint0, world_point2d &linePoint1,
                  int distance)
{
    bool isSelect = isNearbyPointToLine(point.x, point.y,
        linePoint0.x, linePoint0.y, linePoint1.x, linePoint1.y, distance);
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
        if(isSelectPoint(px, py,
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
        if(isSelectPoint(px, py,
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
        if(isSelectLine(px, py, begin->vertex.x, begin->vertex.y,
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


//calcurate degree from vector
//down to 90 degree. right to 0 degree.(right and bottom are plus)
double getDegreeFromVector(double dx, double dy)
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

//sort order from index to height
void sortOrderToHeight(int max, int type, int *sortedOne, bool isFloor)
{
    int *temp = new int[max];
    if(max == 1){
        sortedOne[0] = 0;
    }else{
        for(int i = 0; i < max; i ++){
            switch(type){
            case LINE_TAG:
                if(isFloor){
                    temp[i] = LineList[i].highest_adjacent_floor;
                }else{
                    temp[i] = LineList[i].lowest_adjacent_ceiling;
                }
                break;
            }
        }

        //sort it
        quickSort(temp, max);
        //copy to original
        memcpy(sortedOne, temp, sizeof(int) * max);
    }
    delete temp;
}

//exchange between a and b
template<class T>
void exchange(T *a, T *b)
{
    T temp = *a;
    *a = *b;
    *b = temp;
}

/**
    select axis-num 
    -find two different nums from indexes' left
    -return bigger one
    -if all nums are equal, return -1
*/
static int pivot(int *indexes, int start, int end)
{
    int k = start + 1;
    while( k <= end && indexes[start] == indexes[k])k ++;
    //all are same
    if(k > end) return -1;
    //if not
    if(indexes[start] >= indexes[k]){
        return start;
    }else{
        return k;
    }
}

/**
    divide [more than axis] and [less than axis]
    -smaller is left, bigger is right
    -return offset of start of biggers
*/
static int partition(int *indexes, int start, int end, int axis)
{
    int left = start, right = end;
    while( left <= right){
        while(left <= end && indexes[left] < axis)left ++;
        while(right >= start && indexes[right] >= axis)right --;
        if(left > right)break;
        exchange(&indexes[left], &indexes[right]);
    }
    return left;
}

void repeatbleQuickSort(int *indexes, int start, int end)
{
    if( start == end){
        return;
    }
    int p = pivot(indexes, start, end);
    if(p != -1){
        int offset = partition(indexes, start, end, indexes[p]);
        repeatbleQuickSort(indexes, start, offset - 1);
        repeatbleQuickSort(indexes, offset, end);
    }
}

//sort quickly!
//
void quickSort(int *indexes, int max)
{
    int *temp = new int[max];
    if(max == 1){
        indexes[0] = 0;
    }else{
        //sort it
        repeatbleQuickSort(indexes, 0, max);
    }
    delete temp;
}

/**
	文字列の分割
*/
vector<string> Split( string src, const char* key){
	//結果用
	vector<string> vList;

	int index = 0;
	//用意された文字列srcの長さ分だけ調べる。
	//また、1週するごとにindexに検索結果が出るので、検索結果が無かった場合に終了する。
	while( index < (int)src.size() && index != (int)string::npos){
		//前に検索した場所を覚えておく
		int oldindex = index;
		//指定文字列で前から検索する
		index = (int)src.find( key,index);
		if( index != (int)string::npos){
			//見つかった
			//→前に検索した場所からindexまで((index-oldindex)個分)を取得
			string str = src.substr( oldindex, index-oldindex);
			//結果に追加。
			vList.push_back(str);
			//検索位置を記憶
			index += (int)strlen(key);//key.size();
		}else{
			//見つからなかった
			//→その場所から最後までを最後の要素として追加。次のwhileでループから抜ける
			string str = src.substr(oldindex);
			vList.push_back(str);
		}
	}
	return vList;
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
    
    
    return 0;
}

/**
    check is polygon valid
*/
bool isPolygonValid(int polygonIndex)
{
    return false;
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    return getpixel((Uint8*)surface->pixels, (int)surface->pitch, bpp, x, y);
}

Uint32 getpixel(Uint8* pixels, int pitch, int bpp, int x, int y)
{
    /* この p は取得したいピクセルを指すアドレス */
    Uint8 *p = (Uint8 *)pixels + y * pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32 *)p;

    default:
        return 0;       /* 起こるはずがないが、ワーニングを回避 */
    }
}

/** 
    サーフェイスに指定したピクセルを打ちます
*/
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    int bpp = surface->format->BytesPerPixel;
    /* この p は取得したいピクセルを指すアドレス */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32 *)p = pixel;
        break;
    }
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

//get polygon index which include the point
//return NONE when not found
int getPolygonIdPointIn(world_point2d& point)
{
    for(int i = 0; i < (int)PolygonList.size(); i ++){

        if(point_in_polygon(i, &point)){
            return i;
        }
    }
    return NONE;
}

/**
    search polygon include point stated.
    @return points included in a new or existing valid polygon
        if no points returned, no valid polygon can create or found
*/
vector<int> getValidPoligon(world_point2d& point, short maxHeight, short minHeight)
{
    vector<int> points;
    /*
    //get nearest point
    int nearestPointIndex = getNearestPoint(point);

    //点が存在しない
    if(nearestPointIndex < 0){
        return points;
    }
    */
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
        if(point_in_polygon(i, &point)){
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
        datas[i] = static_cast<int>(getLength(ep->vertex, point));
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
            double length = getLength(point->vertex, pointFrom);
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
        double length = getLength(point->vertex, pointFrom);
        if(minLength > length){
            minLength = length;
            minIndex = i;
        }
    }
    return minIndex;
}

/**
*/
double getLength(world_point2d& pointA, world_point2d& pointB)
{
    double length = getLength(pointA.x - pointB.x, pointA.y - pointB.y);
    return length;
}

/**
//1対1対応のマップをソートする。値側を比較する
    @param indexes インデックス
*/
void sortMap(int *indexes, int max, int* datas)
{
    //datasをソート
    int* temp = new int[max];
    int* doneIndex = new int[max];
    //コピー
    memcpy(temp, datas, sizeof(int) * max);
    memset(doneIndex, 0, sizeof(int) * max);

    //quick sort
    quickSort(temp, max);
    
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
*/
void getPointListLengthOrder(world_point2d& pointFrom, int* indexes)
{
    int max = static_cast<int>(EndpointList.size());
    int* datas = new int[max];
    //代入
    for(int i = 0; i < max; i ++){
        datas[i] = static_cast<int>(getLength(pointFrom, get_endpoint_data(i)->vertex));
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


#include "HPLMapTool.h"
#include "HPLMath.h"
#include <limits.h>
#include "HPLQuickSort.h"
#include <fstream>
#include "HPLError.h"
#include "HPLStringModifier.h"

//�����񉼓ǂݍ��݂̃T�C�Y
//<en>size for buffering string
const int BUF_MAX = 1024;

//�F���̋�؂蕶��
static char* COLOR_ITEM_SEPARATER = ",";
//�F���̎���
const int COL_NUM = 3;

/**
    �������������߂܂�
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
        hpl::error::halt("Fail to open tag file:%s", filePath);
    }
    int lineCounter = 0;
    char buf[BUF_MAX];
    while((ifs.getline(buf, BUF_MAX)) != NULL){
        if(strcmp(buf, "") == 0){
            continue;
        }
        //string�ɂ���
        infos[lineCounter].jname = std::string(buf);
        lineCounter ++;
        if(lineCounter >= maxLines){
            break;
        }
    }
    ifs.close();
}

/**
    �J���[�f�[�^���t�@�C������ǂݍ��݂܂�
    @return ���s���ɋU
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
    �w�肵���ꏊ�ɓ_�����邩�ǂ����𓾂܂�
    @return ���̏ꏊ�ɓ_������΂��̃C���f�b�N�X��������܂��B
        �Ȃ����NONE
*/
int hpl::aleph::map::getSelectPointIndex(world_point2d& wpoint, int threshold, int zMin, int zMax)
{
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        endpoint_data* ep = get_endpoint_data(i);
        //�����`�F�b�N
        if(!hpl::aleph::map::isValidHeight(ep->highest_adjacent_floor_height, ep->lowest_adjacent_ceiling_height,  zMin, zMax)){
            continue;
        }
        if(hpl::aleph::map::isSelectPoint(wpoint, ep->vertex, threshold)){
            return i;
        }
    }
    return NONE;
}

/**
    ���鍂�����K��͈͓��ɂ��邩���m���߂܂�
    @return ���鍂�x�͈̔͂��K��͈͂Ƌ��L���镔���������Ȃ��ꍇ��
*/
bool hpl::aleph::map::isValidHeight(int checkMin, int checkMax, int validMin, int validMax)
{
    if(checkMin > checkMax || checkMin > validMax || checkMax < validMin){
        //�E�����w�肪�t
        //�E�������e�͈͂���ɂ���
        //�E�V�䂪���e�͈͂�艺�ɂ���
        //���ȏ�̏ꍇ�K��͈͊O�i�s���j�Ƃ݂Ȃ�
        return false;
    }else{
        return true;
    }
}
/**
    �w�肵���_�����𓥂�ł���ꍇ�A���̓_
*/
int hpl::aleph::map::getSelectLineIndex(world_point2d& wpoint, int threshold, int zMin, int zMax)
{
    for(int i = 0; i < (int)LineList.size(); i ++){
        line_data* line = get_line_data(i);
        //�����`�F�b�N
        if(!hpl::aleph::map::isValidHeight(line->highest_adjacent_floor, line->lowest_adjacent_ceiling,
            zMin, zMax))
        {
            continue;
        }

        endpoint_data* begin = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* end = get_endpoint_data(line->endpoint_indexes[1]);

        //�I�����Ă��邩����
        if(hpl::aleph::map::isSelectLine(wpoint, begin->vertex, end->vertex, threshold)){
            //�I���ł��Ă���ionline�j
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
    int x0 = (worldPX0 + offsetWorldX) / div + offsetViewX;
    int y0 = (worldPY0 + offsetWorldY) / div + offsetViewY;
    int x1 = (worldPX1 + offsetWorldX) / div + offsetViewX;
    int y1 = (worldPY1 + offsetWorldY) / div + offsetViewY;

    bool isSelect = hpl::math::isNearbyPointToLine(viewPX, viewPY, x0, y0, x1, y1, distance);
    return isSelect;
}
/**
    �w�肵�����W�ł͐���I���ł������H
    @param point �w��|�C���g
    @param linePoint0 ���̒[�_0
    @param linePoint1 ���̒[�_1
    @param distance 臒l
    @return �I���ł���Ȃ�^
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
    ���̒��������߂܂�
    @param index ���C���f�b�N�X
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
    2�_�̋��������߂܂�
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
    ����������\������_�ɂ���Ď擾���܂�
    get line index with two point indexes
    @return �������݂��Ȃ��ꍇNONE
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
            //�o������v�����ꍇ�̂ݕԂ�
            return i;
        }
    }
    return NONE;
}

/**
	�_�����L������C���f�b�N�X�̃��X�g���擾���܂�
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
	�������L����|���S���̃��X�g���擾���܂�
*
std::vector<int> hpl::aleph::map::getPolygonIndexesIncludeLine(int lineIndex)
{
	std::vector<int> polygonIndexes;
	for(int i = 0; i < (int)LineList.size(); i ++){
		polygon_data* polygon = get_polygon_data(i);
		//���_�̐�
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
	�_�����L����|���S���̃��X�g���擾���܂�
*/
std::vector<int> hpl::aleph::map::getPolygonIndexesIncludePoint(int endpointIndex)
{
	std::vector<int> polygonIndexes;
	for(int i = 0; i < (int)LineList.size(); i ++){
		polygon_data* polygon = get_polygon_data(i);
		//���_�̐�
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
	�}�E�X�����ɑI������Ă���A�C�e�����N���b�N���Ă��邩�m���߂܂�
	<en>is point in select groups?
	@param px point locatin(view)				�}�E�X�ʒu�i�r���[���W�j
	@param offsetViewX offset(view)				�r���[���W�Y��
	@param offsetWorldX offset(world)			�����W
	@param pointDistance distance as nearby		�_�p臒l
	@param lineDistance distance as nearby		���p臒l
	@param selectInfo select group for check	�O���[�v�N���X
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
    �|���S�������݂Ƃ��Đ��������ǂ����𔻒肵�܂�
    @param index index of polygon which is checked �����Ώۂ̃|���S���C���f�b�N�X
*/
bool hpl::aleph::map::isValidPolygon(int index)
{
    //TODO
    //�|���S�������擾���܂�
    polygon_data *polygon = get_polygon_data(index);

    //�|���S����񂪖���
    if(polygon == NULL){
        return false;
    }

    //���̕��т����������`�F�b�N
    int vertexCount = polygon->vertex_count;
    double points[MAXIMUM_VERTICES_PER_POLYGON][2];
    for(int i = 0; i < vertexCount; i ++){
        //int a = polygon->endpoint_indexes[i];
        //int next = i + 1;
        //if(i == vertexCount - 2){
        //    next = 0;
        //}
        //int b = polygon->endpoint_indexes[next];
        //int lineIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(a, b);
        //if(lineIndex == NONE){
        //    return false;
        //}
		endpoint_data* ep = get_endpoint_data(polygon->endpoint_indexes[i]);
		points[i][0] = ep->vertex.x;
		points[i][1] = ep->vertex.y;
    }
    bool isValid = hpl::math::isValidPolygon(points, vertexCount);
	return isValid;

/*    int startPointIndex = polygon->endpoint_indexes[0];
    int pointA, pointB, pointC;
    
    
    //���v��肩�A�����v��肩
	int polygonRotationType = hpl::math::RotationType::Clockwise;
    bool isFirstLoop = true;

    for(int i = 0; i < vertexCount - 2; i ++){
        //�_i�Ɠ_i+1���܂ސ���AB, �_i+1�Ɠ_i+2���܂ސ���BC�Ƃ���B
        //�ŏ��̐�[�_0,�_1]�Ɛ�[�_1,�_2]�̊p�x����A���v��肩�A�����v��肩�𔻒肷��
        pointA = polygon->endpoint_indexes[i];
        pointB = polygon->endpoint_indexes[i + 1];
        pointC = polygon->endpoint_indexes[i + 2];
        
        //��̐�AB,BC���D�萬���p�x�����߂�
        double firstDegree = hpl::aleph::map::getTwoLinesDegree(pointA, pointB, pointB, pointC);
        int lineABIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(pointA, pointB);
        int lineBCIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(pointB, pointC);
        if(lineABIndex == NONE || lineBCIndex == NONE){
            //���̕��я����������Ȃ�
            return false;
        }
        //line_indexes�̂Ȃ�тɑΉ����Ă��邩�ǂ���
        if(polygon->line_indexes[i] != lineABIndex ||
            polygon->line_indexes[i + 1] != lineBCIndex){
            return false;
        }
        //optimize degree to [0,360)
        double optDeg = hpl::math::optimizeDegree(firstDegree);

        if(isFirstLoop){
            //�����p�x��[0,180)�Ȃ�΁A�E���ł���
            //����ȊO�i[180,360)�j�Ȃ�΁A�����ł���
            if(optDeg >= 180.0){
				polygonRotationType = hpl::math::RotationType::Counterclockwise;
            }
            isFirstLoop = false;
        }else{
            //�|���S�����t�s�p�i�؂荞��ł�j��ԂȂ�Έُ�ł���Ƃ���
            if((polygonRotationType == hpl::math::RotationType::Clockwise && optDeg >= 180) ||
                (polygonRotationType == hpl::math::RotationType::Counterclockwise && optDeg < 180)){
                return false;
            }
        }
    }
    return true;
*/
	}

/**
    ���W�����͂ރ|���S���̂����A�|���S���Ƃ��Đ������Ă�����̂��������܂�
    ���łɃ|���S�������݂��Ă���ꍇ�͖������܂�
    @param wpoint �T����_�B�������͂ރ|���S����T��
    @return �|���S���̎��f�[�^���B��������ɐ�������Ɨǂ��B�f�[�^��createPolygon�Ő������ׂ�
*/
std::vector<polygon_data> hpl::aleph::map::searchValidPolygon(world_point2d wpoint)
{
    std::vector<polygon_data> polyDatas;

    int max = (int)LineList.size();
    //���ւ̐����̋������Ő��񂷂�
    //�S���̐��ւ̐��������߂�
    struct hpl::math::qsort::Pair<double>* pairs = new struct hpl::math::qsort::Pair<double>[max];
    for(int i = 0; i < max; i ++){
        line_data* line = get_line_data(i);
        endpoint_data* epStart = get_endpoint_data(line->endpoint_indexes[0]);
        endpoint_data* epEnd = get_endpoint_data(line->endpoint_indexes[1]);
        pairs[i].data = hpl::math::getPointDistanceFromLine(wpoint.x, wpoint.y, 
            epStart->vertex.x, epStart->vertex.y, epEnd->vertex.x, epEnd->vertex.y);
    }
    hpl::math::qsort::quickSort<double>(pairs, max);

    //�߂��ɂ�������猩�Ă���
    for(int i = 0; i < max; i ++){
        line_data* startLine = get_line_data(pairs[i].index);
		endpoint_data* epStart = get_endpoint_data(startLine->endpoint_indexes[0]);
		endpoint_data* epEnd = get_endpoint_data(startLine->endpoint_indexes[1]);

        //���̍��E�ǂ���̑��ɓ_�����邩���`�F�b�N���܂�
		int rotRem = hpl::math::getPointRotationTypeFromLine(
			wpoint.x, wpoint.y, epStart->vertex.x, epStart->vertex.y,
			epEnd->vertex.x, epEnd->vertex.y);
		int previousPoint;
		//TODO
    }
    
    //���
    delete pairs;
    return polyDatas;
}

/**
    ���E���W����|���S���f�[�^�����܂�
    TODO ������
    @param points ���E���W
    @param ep �������ꂽ�_�f�[�^
    @param ld �������ꂽ���f�[�^
    @param n n�p�`
*/
polygon_data hpl::aleph::map::createPolygon(world_point2d points[],
                                            endpoint_data epd[], line_data ld[],
        int n)
{
    //�_����
    for(int i = 0; i < n; i ++){
        epd[i].flags = 0;
        epd[i].highest_adjacent_floor_height = 0;
        epd[i].lowest_adjacent_ceiling_height = WORLD_ONE;
        epd[i].vertex.x = points[i].x;
        epd[i].vertex.y = points[i].y;

        epd[i].supporting_polygon_index = 0;
    }

    //��
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

        ld[i].length = (world_distance)hpl::aleph::map::getPointsDistance(
            epd[ld[i].endpoint_indexes[0]].vertex, epd[ld[i].endpoint_indexes[1]].vertex);
    }

    //�|���S��
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
    �Ɨ������|���S���f�[�^��ǉ����܂�
*/
void hpl::aleph::map::addNewPolygon(polygon_data& pdata, endpoint_data epd[],
                                    line_data ld[], int n)
{
    //�_
    std::map<int,int> epIndexTable;
    std::string str;
    for(int i = 0; i < n; i ++){
		int newIndex = hpl::aleph::map::addEndpoint(epd[i]);
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
        //�C��
        for(int j = 0; j < 2; j ++){
            ld[i].endpoint_indexes[j] = epIndexTable[ld[i].endpoint_indexes[j]];
        }

		int newIndex = hpl::aleph::map::addLine(ld[i]);
        lIndexTable[i] = newIndex;
    }
    
    //�|���S�����C��
    for(int i = 0; i < n; i ++){
        pdata.endpoint_indexes[i] = epIndexTable[pdata.endpoint_indexes[i]];
    }
    for(int i = 0; i < n; i ++){
        pdata.line_indexes[i] = lIndexTable[pdata.line_indexes[i]];
    }
	
	//�|���S���ǉ�
	int newPolygonIndex = hpl::aleph::map::addPolygon(pdata);
	//�����C��
    for(int i = 0; i < n; i ++){
        int newIndex = epIndexTable[i];
        endpoint_data* ep = get_endpoint_data(newIndex);
        ep->supporting_polygon_index = newPolygonIndex;
    }
    for(int i = 0; i < n - 1; i ++){
        int newIndex = lIndexTable[i];
        line_data* l = &(LineList[newIndex]);
        l->clockwise_polygon_owner = newPolygonIndex;
		l->counterclockwise_polygon_owner = NONE;
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
    ��̐����D�萬���p�x�����߂܂�
    @param pIndexA1,2 ����A1-A2�̓_�C���f�b�N�X
    @param pIndexB1,2 ����B1-B2�̓_�C���f�b�N�X
*/
double hpl::aleph::map::getTwoLinesDegree(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2)
{
    //degree�ɂ��܂�
    double rad = hpl::aleph::map::getTwoLinesRadian(pIndexA1, pIndexA2, pIndexB1, pIndexB2);
    double deg = hpl::math::getDegreeFromRadian(rad);
    return deg;
}
double hpl::aleph::map::getTwoLinesRadian(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2)
{
    //radian�ŋ��߂܂�
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
    �w�肵���_���|���S���̒��ɑ��݂��邩�ǂ������m���߂܂�
    @
*/
bool hpl::aleph::map::isPointInPolygon(int viewPX, int viewPY, int polygonIndex,
                                       int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety)
{
    //���[���h���W�ɕϊ����܂�
    world_point2d wpoint = hpl::aleph::map::getWorldPoint2DFromViewPoint(viewPX, viewPY, 
        offsetXWorld, offsetYWorld, zoomDivision, offsetx, offsety);
	bool isPointIn = hpl::aleph::map::isPointInPolygon(wpoint, polygonIndex);
	return isPointIn;
}

bool hpl::aleph::map::isPointInPolygon(world_point2d& wpoint, int polygonIndex)
{
    double points[MAXIMUM_VERTICES_PER_POLYGON][2];
    //�|���S�����𓾂܂�
    polygon_data* poly = get_polygon_data(polygonIndex);
    int n = poly->vertex_count;
    for(int i = 0; i < n; i ++){
        endpoint_data* ep = get_endpoint_data(poly->endpoint_indexes[i]);
        points[i][0] = ep->vertex.x;
        points[i][1] = ep->vertex.y;
    }
    //�ʒu�������܂�
    bool isPointIn = hpl::math::isPointInPolygon(wpoint.x, wpoint.y, points, n);
    return isPointIn;
}

//////////////////////////////////////////////////////
/////// add delete and modify
/**
	�_����ǉ����܂�
	@param ep �ǉ�����_�f�[�^�i�l�n���Ȃ̂ŃR�s�[����܂��j
	@return �ǉ����ꂽ�_�̃C���f�b�N�X�l
*/
int hpl::aleph::map::addEndpoint(endpoint_data ep)
{
	EndpointList.push_back(ep);
	dynamic_world->endpoint_count = (int16)EndpointList.size();
	int index = dynamic_world->endpoint_count - 1;
	return index;
}
int hpl::aleph::map::addLine(line_data line)
{
	LineList.push_back(line);
	dynamic_world->line_count = (int16)LineList.size();
	int index = dynamic_world->line_count - 1;
	return index;
}
int hpl::aleph::map::addSide(side_data side)
{
	SideList.push_back(side);
	dynamic_world->side_count = (int16)SideList.size();
	int index = dynamic_world->side_count - 1;
	return index;
}
int hpl::aleph::map::addPolygon(polygon_data polygon)
{
	PolygonList.push_back(polygon);
	dynamic_world->polygon_count = (int16)PolygonList.size();
	int index = dynamic_world->polygon_count - 1;
	return index;
}
int hpl::aleph::map::addMapSavedObject(map_object object)
{
	SavedObjectList.push_back(object);
	//TODO
	//�v���[�X�����g���ɕt��

	//TODO �ǂ���W�v����Ηǂ��̂��H
//	dynamic_world->object_count ++;// SavedObjectList.size();
	dynamic_world->initial_objects_count = (int16)SavedObjectList.size();
	int index = dynamic_world->initial_objects_count - 1;
	return index;
}
int hpl::aleph::map::addAnnotation(map_annotation annotation)
{
	MapAnnotationList.push_back(annotation);
/*	dynamic_world-> = MapAnnotationList.size();
	int index = dynamic_world->annotation_count - 1;*/
	int index = (int16)MapAnnotationList.size() - 1;
	return index;
}

/**
    �ȗ��o�[�W����
*/
bool hpl::aleph::map::createPoint(world_point2d& wpoint, endpoint_data* ep,
                                  int threshold)
{
    //TODO
    ep->flags = 1;
    ep->vertex.x = wpoint.x;
    ep->vertex.y = wpoint.y;

    //���̓_�𓥂�ł��Ȃ����m�F
    int pIndex = hpl::aleph::map::getSelectPointIndex(wpoint, threshold,
        -SHRT_MIN, SHRT_MAX);
    if(pIndex != NONE){
        //����ł�
        //���쐬�ł��Ȃ�
        return false;
    }
    ep->highest_adjacent_floor_height = 0;
    ep->lowest_adjacent_ceiling_height = WORLD_ONE;
    ep->supporting_polygon_index = NONE;
    return true;
}
/**
    @param polyIndex �ڂ���|���S���̃C���f�b�N�X
*/
bool hpl::aleph::map::createObject(world_point2d& wpoint, int polyIndex, map_object* obj,
                                   int flags)
{
    //TODO
    obj->polygon_index = polyIndex;
    obj->location.x = wpoint.x;
    obj->location.y = wpoint.y;
    polygon_data* poly = get_polygon_data(polyIndex);
    if(poly == NULL){
        return false;
    }
    //TODO flag?
    if(flags & _map_object_hanging_from_ceiling){
        obj->location.z = poly->ceiling_height;
    }else{
        obj->location.z = poly->floor_height;
    }
    obj->flags = flags;
}

bool hpl::aleph::map::createLine(int beginPointIndex, int endPointIndex, line_data* line)
{
    endpoint_data* begin = get_endpoint_data(beginPointIndex);
    endpoint_data* end = get_endpoint_data(endPointIndex);
    if(begin == NULL || end == NULL){
        return false;
    }
    line->clockwise_polygon_owner = NONE;
    line->clockwise_polygon_side_index = NONE;
    line->counterclockwise_polygon_owner = NONE;
    line->counterclockwise_polygon_side_index = NONE;
    line->endpoint_indexes[0] = beginPointIndex;
    line->endpoint_indexes[1] = endPointIndex;
    line->flags = SOLID_LINE_BIT;
    //TODO �_�̂����������̃t���A���x
    line->highest_adjacent_floor = 0;
    return true;
}

bool hpl::aleph::map::createPolygon(int pointIndexes[], int n, polygon_data* poly)
{
    endpoint_data* ep[MAXIMUM_VERTICES_PER_POLYGON];

    for(int i = 0; i < n; i ++){
        ep[i] = get_endpoint_data(pointIndexes[i]);
        if(ep[i] == NULL){
            return false;
        }
        poly->endpoint_indexes[i] = pointIndexes[i];
    }
    for(int i = 0; i < n; i ++){
        int next = i + 1;
        if(i == n - 1){
            next = 0;
        }
        int lIndex = hpl::aleph::map::getLineIndexFromTwoLPoints(pointIndexes[i], pointIndexes[next]);
        if(lIndex == NONE){
            return false;
        }
        poly->line_indexes[i] = lIndex;
    }
    //TODO
    //poly->adjacent_polygon_indexes = NONE;
    poly->ambient_sound_image_index = NONE;
    //TODO area?
    poly->area = 0;
    //TODO �_�̂�����ԍ������x
    poly->ceiling_height = WORLD_ONE;
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
    //TODO count ���̔��Α���
    poly->neighbor_count = 0;
    //TODO ?
    poly->permutation = 0;
    poly->random_sound_image_index = NONE;
    //poly->side_indexes[0] = NONE;
    //poly->sound_source_indexes;
    poly->type = _polygon_is_normal;
    poly->vertex_count = n;
    return true;
}

/**
	�ꕔ���΂����V�����C���f�b�N�X�\�����܂�
*/
static std::map<int, int> getIndexMapSkipped(size_t max, int skipIndex)
{
	std::map<int, int> indexMap;
	for(int i = 0; i < (int)max; i ++){
		int newIndex = i;
		if(i > skipIndex){
			newIndex = i - 1;
		}
		indexMap[i] = newIndex;
	}
	return indexMap;
}

/**
	�_�����폜���܂�
*/
bool hpl::aleph::map::deleteEndpoint(int index)
{
	endpoint_data* ep = get_endpoint_data(index);
	if(!ep){
		return false;
	}
	//�֘A����C���f�b�N�X�����ꂼ�꒼���K�v����
	//���̓_��L������ƃ|���S���A�I�u�W�F�N�g�����폜����
	std::vector<int> lineIndexes = hpl::aleph::map::getLineIndexesIncludePoint(index);
	for(int i = 0; i < (int)lineIndexes.size(); i ++){
		//���폜
		//���̂Ƃ��A���̍��E�ɂ���|���S�����폜�����
		//�|���S�����폜����ƒ��ɂ���I�u�W�F�N�g������
		hpl::aleph::map::deleteLine(i);
	}
	std::map<int, int> indexMap = getIndexMapSkipped(EndpointList.size(), index);

	//�|���S���Ɛ��̓_�C���f�b�N�X����Ȃ���
	//TODO ���ɂ��K�v�����H
	for(int i = 0; i < (int)LineList.size(); i ++){
		line_data* line = get_line_data(i);
		for(int j = 0; j < 2; j ++){
			line->endpoint_indexes[j] = indexMap[line->endpoint_indexes[j]];
		}
	}
	for(int i = 0; i < (int)PolygonList.size(); i ++){
		polygon_data* polygon = get_polygon_data(i);
		int n = polygon->vertex_count;
		for(int j = 0; j < n; j ++){
			polygon->endpoint_indexes[j] = indexMap[polygon->endpoint_indexes[j]];
		}
	}
	//�폜�I
	hpl::aleph::removeIndexInVector<endpoint_data>(&EndpointList, index);
	//dynamic!
	dynamic_world->endpoint_count = (int16)EndpointList.size();
	return true;
}
bool hpl::aleph::map::deleteLine(int index)
{
	//TODO
	line_data* line = get_line_data(index);
	if(line == NULL){
		return false;
	}
	//�����ɍ��E�ɂ���|���S���𖕎E���܂�
	if(line->clockwise_polygon_owner != NONE){
		//�폜
		hpl::aleph::map::deletePolygon(line->clockwise_polygon_owner);
	}
	if(line->counterclockwise_polygon_owner != NONE){
		hpl::aleph::map::deletePolygon(line->counterclockwise_polygon_owner);
	}
	///���ł�side���폜���܂�
	if(line->clockwise_polygon_side_index != NONE){
		hpl::aleph::map::deleteSide(line->clockwise_polygon_side_index);
	}
	if(line->counterclockwise_polygon_side_index != NONE){
		hpl::aleph::map::deleteSide(line->counterclockwise_polygon_side_index);
	}
	std::map<int, int> indexMap = getIndexMapSkipped(LineList.size(), index);

	//�C���f�b�N�X�𒣂�Ȃ����܂�
	//TODO
	//�|���S����Side�̃C���f�b�N�X����Ȃ���
	for(int i = 0; i < (int)PolygonList.size(); i ++){
		polygon_data* polygon = get_polygon_data(i);
		int n = polygon->vertex_count;
		for(int j = 0; j < n; j ++){
			polygon->line_indexes[j] = indexMap[polygon->line_indexes[j]];
		}
	}
	for(int i = 0; i < (int)SideList.size(); i ++){
		side_data* side = get_side_data(i);
		side->line_index = indexMap[side->line_index];
	}
	//�폜
	hpl::aleph::removeIndexInVector<line_data>(&LineList, index);
	dynamic_world->line_count = (int16)LineList.size();
	return true;
}
bool hpl::aleph::map::deleteSide(int index)
{
	//TODO
	side_data* side = get_side_data(index);
	if(side == NULL){
		return false;
	}
	//���L�҂ł��������͂����܂�
	if(side->line_index != NONE){
		line_data* line = get_line_data(side->line_index);
		if(line->clockwise_polygon_side_index == index){
			line->clockwise_polygon_side_index = NONE;
		}
		if(line->counterclockwise_polygon_side_index == index){
			line->counterclockwise_polygon_side_index = NONE;
		}
	}

	//�C���f�b�N�X�𒣂�Ȃ����܂�
	std::map<int,int> indexMap = getIndexMapSkipped(SideList.size(), index);

	//TODO
	//���̏��𒣂蒼���܂�
	for(int i = 0; i < (int)LineList.size(); i ++){
		line_data* line = get_line_data(i);
		if(line->counterclockwise_polygon_side_index != NONE){
			line->counterclockwise_polygon_side_index =
				indexMap[line->counterclockwise_polygon_side_index];
		}
		if(line->clockwise_polygon_side_index != NONE){
			line->clockwise_polygon_side_index =
				indexMap[line->clockwise_polygon_side_index];
		}
	}

	//�폜���܂�
	hpl::aleph::removeIndexInVector(&SideList, index);
	dynamic_world->side_count = (int16)SideList.size();
	return true;
}
bool hpl::aleph::map::deletePolygon(int index)
{
	//TODO
	polygon_data* polygon = get_polygon_data(index);
	if(polygon == NULL){
		return false;
	}
	//�̂������Ă���I�u�W�F�N�g���폜���܂�
	for(int i = 0; i < (int)SavedObjectList.size(); i ++){
		map_object* obj = &SavedObjectList[i];
		if(obj->polygon_index == index){
			//�폜
			hpl::aleph::map::deleteMapSavedObject(i);
		}
	}

	std::map<int,int> indexMap = getIndexMapSkipped(PolygonList.size(), index);
	//�����X�V���܂�
	//TODO
	//�������X�V���܂�
	for(int i = 0; i < (int)LineList.size(); i ++){
		line_data* line = get_line_data(i);
		if(line->clockwise_polygon_owner != NONE){
			line->clockwise_polygon_owner = 
				indexMap[line->clockwise_polygon_owner];
		}
		if(line->counterclockwise_polygon_owner != NONE){
			line->counterclockwise_polygon_owner =
				indexMap[line->counterclockwise_polygon_owner];
		}
	}
	//�I�u�W�F�N�g�����X�V���܂�
	for(int i = 0; i < (int)SavedObjectList.size(); i ++){
		map_object* obj = &SavedObjectList[i];
		obj->polygon_index = indexMap[obj->polygon_index];
	}
	//�폜
	hpl::aleph::removeIndexInVector(&PolygonList, index);
	dynamic_world->polygon_count = (int16)PolygonList.size();
	return true;
}
bool hpl::aleph::map::deleteMapSavedObject(int index)
{
	//TODO
	if(index < 0 || index >= (int)SavedObjectList.size()){
		return false;
	}
	//�폜
	hpl::aleph::removeIndexInVector(&SavedObjectList, index);
	return true;
}

////////////////////////////////////////////////
//////// objects ///////////////////////////////
/**
	�����z�u���̐ݒ�
	@param objectType �I�u�W�F�N�g�^�C�v
		_saved_item
		_saved_monster
	@param index �ǂ̃I�u�W�F�N�g�̏����͈ʒu�������邩
	@param num ����������l
	@return �����̌��ʂ̐�
*/
int hpl::aleph::map::addInitialPlacementNum(int objectType, int index, int num)
{
	struct object_frequency_definition* place = hpl::aleph::map::getPlacementData(objectType, index);
	if(place){
		place->initial_count += num;
        return place->initial_count;
	}else{
		return NONE;
	}
}
/**
	�z�u�����擾
	@param objectType �I�u�W�F�N�g�^�C�v
		_saved_item
		_saved_monster
	@param index �ǂ̃I�u�W�F�N�g�̏����͈ʒu�������邩
	@return �z�u���B�z�u���⃉���_���}�b�N�X�Ȃ�
*/
struct object_frequency_definition* hpl::aleph::map::getPlacementData(int objectType, int index)
{
	struct object_frequency_definition* place = NULL;
	if(objectType == _saved_item && item_placement_info){
		place = &item_placement_info[index];
	}else if(objectType == _saved_monster && monster_placement_info){
		place = &monster_placement_info[index];
	}
	return place;
}


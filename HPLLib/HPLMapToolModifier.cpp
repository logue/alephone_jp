#include "HPLMapTool.h"
#include "HPLMath.h"
#include <limits.h>
#include "HPLQuickSort.h"
#include <fstream>
#include "HPLError.h"
#include "HPLStringModifier.h"
#include "map.h"
#include "HPLStockManager.h"
//�p�x�̍ő�
const double DEG_ROUND = 360.0;

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
int hpl::aleph::map::addSide(side_data side, bool isClockwise)
{
	SideList.push_back(side);
	dynamic_world->side_count = (int16)SideList.size();
	int index = dynamic_world->side_count - 1;
    //�ˑ�������̂��C������
    //�E��
    //�E�|���S��
    //�ESide
    //TODO ���E�̊m�F���K�v
    side_data* newSide = get_side_data(index);
    line_data* line = get_line_data(newSide->line_index);
#ifdef __WXDEBUG__
    wxASSERT(line);
#else
    if(!line){
        hpl::error::halt("line[%d] doesn't exist", newSide->line_index);
    }
#endif
    polygon_data* poly = get_polygon_data(newSide->polygon_index);
#ifdef __WXDEBUG__
    wxASSERT(poly);
#else
    if(!poly){
        hpl::error::halt("polygon[%d] doesn't exist", newSide->polygon_index);
    }
#endif
    if(isClockwise){
        line->clockwise_polygon_side_index = index;
    }else{
        line->counterclockwise_polygon_side_index = index;
    }

    //�|���S��
    int lineIndexInPolygon = NONE;
    for(int i = 0; i < poly->vertex_count; i ++){
        if(poly->line_indexes[i] == newSide->line_index){
            lineIndexInPolygon = i;
            break;
        }
    }
#ifdef __WXDEBUG__
    wxASSERT(lineIndexInPolygon != NONE);
#else
    if(lineIndexInPolygon == NONE){
        hpl::error::halt("line[%d] doesn't exist in polygon[%d]'s line_index", newSide->line_index,
            newSide->polygon_index);
    }
#endif
    poly->side_indexes[lineIndexInPolygon] = index;


	return index;
}
int hpl::aleph::map::addPolygon(polygon_data polygon)
{
	PolygonList.push_back(polygon);
	dynamic_world->polygon_count = (int16)PolygonList.size();
	int index = dynamic_world->polygon_count - 1;

    polygon_data* poly = get_polygon_data(index);

    //�ȉ��̈ˑ����鍀�ڂ��C������
    //�E�_�iadjacent�j
    //�E���iowner�j
    //�ESide
    //TODO
    for(int i = 0; i < poly->vertex_count; i ++){
        int next = i + 1;
        if(next >= poly->vertex_count){
            next = 0;
        }
        endpoint_data* ep1 = get_endpoint_data(poly->endpoint_indexes[i]);
        //�֘A�|���S���̎w�肪������Ύw��
        if(ep1->supporting_polygon_index == NONE){
            ep1->supporting_polygon_index = index;
        }

        endpoint_data* ep2 = get_endpoint_data(poly->endpoint_indexes[next]);

        //��
        line_data* line = get_line_data(poly->line_indexes[i]);
        if(line->endpoint_indexes[0] == poly->endpoint_indexes[i]){
            //��������clockwise
            line->clockwise_polygon_owner = index;
            side_data* side = get_side_data(line->clockwise_polygon_side_index);
            if(side)
                side->polygon_index = index;
        }else if(line->endpoint_indexes[0] == poly->endpoint_indexes[next]){
            //�t������counterclockwise
            line->counterclockwise_polygon_owner = index;
            side_data* side = get_side_data(line->counterclockwise_polygon_side_index);
            if(side)
                side->polygon_index = index;
        }else{
#ifdef __WXDEBUG__
            wxASSERT(false);
#else
            hpl::error::halt("invalid polygon frame");
#endif
        }
    }
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

    map_object* obj = &SavedObjectList[index];

    //�ˑ����鍀�ڂ��C������
    //�E�|���S��
    polygon_data* poly = get_polygon_data(obj->polygon_index);
#ifdef __WXDEBUG__
    wxASSERT(poly);
#else
    if(!poly){
        hpl::error::halt("poly[%d] not found", obj->polygon_index);
    }
#endif
    if(poly->first_object == NONE){
        poly->first_object = index;
    }
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
    �}�b�v�A�C�e���i�_�E���ESide�E�|���S���E�I�u�W�F�N�g�j
    ���폜���܂�
    ��@�Ƃ��ẮA
    �P�F���̒[�_�ȂǁA�Q�ƌ����폜�ΏۂƂȂ��Ă���ꍇ�A
        �E�Q�Ƃ�NONE�ɂ���
        �E�������g���폜�ΏۂƂ���
    �Q�F�폜�Ώۂ��폜���Ă���
        �E�폜�ԍ��̗�����
        �E��둤��������Ă���

    @param 
*/
bool hpl::aleph::map::deleteMapItems(std::vector<bool>& delPoints, std::vector<bool>& delLines,
                                     std::vector<bool>& delSides,
    std::vector<bool>& delPolygons, std::vector<bool>& delObjects)
{
    if(delPoints.size() != EndpointList.size() ||
        delPoints.size() != dynamic_world->endpoint_count ||
        delLines.size() != LineList.size() ||
        delLines.size() != dynamic_world->line_count ||
        delSides.size() != SideList.size() ||
        delSides.size() != dynamic_world->side_count ||
        delPolygons.size() != PolygonList.size() ||
        delPolygons.size() != dynamic_world->polygon_count ||
        delObjects.size() != SavedObjectList.size())
    {
        hpl::error::halt("���������Ă��Ȃ�");
        return false;
    }



    /////////////////
    //���ۂɍ폜����
    std::map<int, int> indexMapPoints;
    std::map<int, int> indexMapLines;
    std::map<int, int> indexMapSides;
    std::map<int, int> indexMapPolygons;
    std::map<int, int> indexMapObjects;
    //�Ή��\�����
    int counter = 0;
    for(int i = 0; i < (int)delPoints.size(); i ++){
        if(!delPoints[i]){   indexMapPoints[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)delLines.size(); i ++){
        if(!delLines[i]){   indexMapLines[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)delSides.size(); i ++){
        if(!delSides[i]){   indexMapSides[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)delPolygons.size(); i ++){
        if(!delPolygons[i]){   indexMapPolygons[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)delObjects.size(); i ++){
        if(!delObjects[i]){   indexMapObjects[i] = counter;   counter ++;}
    }

    //�C���f�b�N�X��t������
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        if(!delPoints[i]){
            endpoint_data* ep = get_endpoint_data(i);
            ep->supporting_polygon_index = indexMapPolygons[ep->supporting_polygon_index];
        }
    }
    for(int i = 0; i < (int)LineList.size(); i ++){
        if(!delLines[i]){
            line_data* line = get_line_data(i);
            assert(line);
            if(line->clockwise_polygon_owner != NONE){
                line->clockwise_polygon_owner = indexMapPolygons[line->clockwise_polygon_owner];
            }
            if(line->clockwise_polygon_side_index != NONE){
                line->clockwise_polygon_side_index = indexMapSides[line->clockwise_polygon_side_index];
            }
            if(line->counterclockwise_polygon_owner != NONE){
                line->counterclockwise_polygon_owner = indexMapPolygons[line->counterclockwise_polygon_owner];
            }
            if(line->counterclockwise_polygon_side_index != NONE){
                line->counterclockwise_polygon_side_index = indexMapSides[line->counterclockwise_polygon_side_index];
            }
            for(int j = 0; j < 2; j ++){
                line->endpoint_indexes[j] = indexMapPoints[line->endpoint_indexes[j]];
            }
        }
    }
    for(int i = 0; i < (int)SideList.size(); i ++){
        if(!delSides[i]){
            side_data* side = get_side_data(i);
            assert(side);
            side->line_index = indexMapLines[side->line_index];
            side->polygon_index = indexMapPolygons[side->polygon_index];
        }
    }
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        if(!delPolygons[i]){
            polygon_data* poly = get_polygon_data(i);
            assert(poly);
            int n = poly->vertex_count;
            for(int j = 0; j < n; j ++){
                if(poly->adjacent_polygon_indexes[j] != NONE){
                    poly->adjacent_polygon_indexes[j] =
                        indexMapPolygons[poly->adjacent_polygon_indexes[j]];
                }
                poly->line_indexes[j] = indexMapLines[poly->line_indexes[j]];
                poly->endpoint_indexes[j] = indexMapPoints[poly->endpoint_indexes[j]];
                poly->side_indexes[j] = indexMapSides[poly->side_indexes[j]];
            }
            if(poly->first_object != NONE){
                poly->first_object = indexMapObjects[poly->first_object];
            }
        }
    }
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        if(!delObjects[i]){
            map_object* obj = &SavedObjectList[i];
            obj->polygon_index = indexMapPolygons[obj->polygon_index];
        }
    }

    return true;
}

///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
/// add
/**
    ��{�̐�&�_����Ȃ�����̂����A�T�C�Y�������Ƃ��������Ȃ�悤��
    �_�̃��X�g���擾���܂��B�_�̕��т̓|���S���w��ɂ��̂܂܎g���镨�ƂȂ��Ă��܂��B

    �ċA�I�ɌĂяo���܂��B
    @param pointIndexes ����܂łɂȂ��Ă����_�̃��X�g�B���̌���MAXIMUM_VERTEX_PER_POLYGON
        �𒴂����猩����Ȃ��������̂Ƃ���
    @return �|���S�������������ꍇ�^
*/
static bool getValidLines(int basePointIndex, int baseLineIndex,
                          std::vector<int> *pointIndexes,
                          hpl::aleph::HPLStockManager* smgr,
                          int rotRem, std::set<int>* doneList,
                          int zMin, int zMax,
                          world_point2d& wpoint)
{
    //�ő�̊p�x
    double maxDeg = 0;
    int maxLineIndex = NONE;

    line_data* baseLine = get_line_data(baseLineIndex);
    int startBasePointIndex = baseLine->endpoint_indexes[0];
    int endBasePointIndex =  baseLine->endpoint_indexes[1];
    if(startBasePointIndex == basePointIndex){
        //����ւ�
        hpl::math::exchange(&startBasePointIndex, &endBasePointIndex);
    }else if(endBasePointIndex == basePointIndex){
    }else{
        hpl::error::halt("invalid basePointIndex");
    }

    int lastPointIndex = NONE;
    //�x�[�X�|�C���g�Ɍq����������o��
    std::vector<int> conLines = hpl::aleph::map::getLineIndexesIncludePoint(basePointIndex);
    for(int k = 0; k < (int)conLines.size(); k ++){
        int conLineIndex = conLines[k];
        if(doneList->find(conLines[k]) != doneList->end()){
            //���Ɍ����o�������̂͏Ȃ�
            continue;
        }
        //delLines�͏Ȃ�
        if(smgr->delLines[conLineIndex]){
            continue;
        }
        //�x�[�X�̐��ƈꏏ�̏ꍇ�����O����
        if(baseLineIndex == conLineIndex){
            continue;
        }

        line_data* line = get_line_data(conLineIndex);
        if(!line)hpl::error::halt("line is null");
        //�����`�F�b�N
        if(!hpl::aleph::map::isValidHeight(line->highest_adjacent_floor,
            line->lowest_adjacent_ceiling, zMin, zMax))
        {
            continue;
        }

        int ep0Index = line->endpoint_indexes[0];
        int ep1Index = line->endpoint_indexes[1];
        if(basePointIndex == ep0Index){
        }else if(basePointIndex == ep1Index){
            //����ւ�
            hpl::math::exchange(&ep0Index, &ep1Index);
        }else{
            assert(false);
        }

        endpoint_data* ep0 = get_endpoint_data(ep0Index);
        if(!ep0)hpl::error::halt("ep0 is null");
        endpoint_data* ep1 = get_endpoint_data(ep1Index);
        if(!ep1)hpl::error::halt("ep1 is null");

        double l0x = ep0->vertex.x;
        double l0y = ep0->vertex.y;
        double l1x = ep1->vertex.x;
        double l1y = ep1->vertex.y;
        //������w��_�ɑ΂���p�x�����߂�i���E�̊m�F�j
        int rot = hpl::math::getPointRotationTypeFromLine(
            wpoint.x, wpoint.y, l0x, l0y, l1x, l1y);
        //�ŏ��̐��ƈႤ�i�t�����j�Ɏw��_�����Ă���ꍇ�͐������Ȃ����̂Ƃ���B
        if(rotRem != rot){
            continue;
        }

        //�O�̐��̎n�_�����L�_���Ō�̓_�Ŋp�x�����߂�
        //�O�̐��̎n�_
        endpoint_data* prevStartEp = get_endpoint_data(startBasePointIndex);
        assert(prevStartEp);
        double deg = hpl::math::getTwoLinesDegree(prevStartEp->vertex.x,
            prevStartEp->vertex.y, l0x, l0y,
            l0x, l0y, l1x, l1y);
        //[0,360)�ɐ�������
        deg = hpl::math::optimizeDegree(deg);
        if(deg > DEG_ROUND / 2.0){
            deg = DEG_ROUND - deg;
        }
        //�p�x�����ݍő傩�ǂ����m�F����
        if(deg > maxDeg){
            maxDeg = deg;
            //���܂ł��傫��
            maxLineIndex = conLineIndex;
            //�Ō�̓_
            lastPointIndex = ep1Index;
        }
        //�ς�
        doneList->insert(conLineIndex);
    }

    if(maxLineIndex == NONE){
        //������Ȃ�����
        //����Ė߂��Ă���
        return false;
    }else{
        //��������
        //�Ō�ɒǉ�����
        pointIndexes->push_back(lastPointIndex);

        //�Ō�̓_��pointIndexes[0]�Ɠ���i������Ă����j��������
        //�I������Ƃ���
        if(lastPointIndex == pointIndexes->at(0)){
            //�|���S���Ƃ��Đ�������Z�b�g�������o����
            return true;
        }else{
            //�܂��܂�
            if(pointIndexes->size() >= MAXIMUM_VERTICES_PER_POLYGON + 1){
                return false;
            }
            //�����ő吔�𒴂��Ă���
            //����T��
            baseLineIndex = maxLineIndex;
            basePointIndex = lastPointIndex;
            bool found = getValidLines(basePointIndex, baseLineIndex, pointIndexes,
                smgr, rotRem, doneList, zMin, zMax, wpoint);
            //���ǌ����������ǂ����͎q���������m���Ă���
            return found;
        }
    }
}

/**
    ���W�����͂ރ|���S���̂����A�|���S���Ƃ��Đ������Ă�����̂��������܂�
    ���łɃ|���S�������݂��Ă���ꍇ�͖������܂�
    @param wpoint �T����_�B�������͂ރ|���S����T��
    @return �|���S���̎��f�[�^���B��������ɐ�������Ɨǂ��B�f�[�^��createPolygon�Ő������ׂ�
*/
std::vector<polygon_data> hpl::aleph::map::searchValidPolygon(world_point2d wpoint,
                                                              hpl::aleph::HPLStockManager* smgr,
                                                              int zMin, int zMax)
{
    std::vector<polygon_data> polyDatas;

    int max = (int)LineList.size();
    //���ւ̐����̋������Ő��񂷂�
    //�S���̐��ւ̐��������߂�
    struct hpl::math::qsort::Pair<double>* pairs = new struct hpl::math::qsort::Pair<double>[max];
    for(int i = 0; i < max; i ++){
        line_data* line = get_line_data(i);
        assert(line);
        endpoint_data* epStart = get_endpoint_data(line->endpoint_indexes[0]);
        assert(epStart);
        endpoint_data* epEnd = get_endpoint_data(line->endpoint_indexes[1]);
        assert(epEnd);
        pairs[i].data = hpl::math::getPointDistanceFromLine(wpoint.x, wpoint.y, 
            epStart->vertex.x, epStart->vertex.y, epEnd->vertex.x, epEnd->vertex.y);
    }
    hpl::math::qsort::quickSort<double>(pairs, max);

    //���ɒ��ׂ����X�g(���̃C���f�b�N�X�l������)
    std::set<int> doneList;

    //�߂��ɂ�������猩�Ă���
    for(int i = 0; i < max; i ++){
        //�폜�ΏۂȂ疳��
        if(smgr->delLines[i]){
            continue;
        }
        //���łɒ��ׂ����Ȃ疳��
        if(doneList.find(i) != doneList.end()){
            continue;
        }
        int lineIndexBase = pairs[i].index;
        line_data* startLine = get_line_data(lineIndexBase);
        if(!startLine)hpl::error::halt("startLine is null");
        //�����`�F�b�N
        if(!hpl::aleph::map::isValidHeight(startLine->highest_adjacent_floor,
            startLine->lowest_adjacent_ceiling, zMin, zMax))
        {
            continue;
        }

        int startPointIndex = startLine->endpoint_indexes[0];
		endpoint_data* epStart = get_endpoint_data(startPointIndex);
        if(!epStart)hpl::error::halt("epStart is null");
        int endPointIndex = startLine->endpoint_indexes[1];
		endpoint_data* epEnd = get_endpoint_data(endPointIndex);
        if(!epEnd)hpl::error::halt("epEnd is null");

        //���̍��E�ǂ���̑��ɓ_�����邩���`�F�b�N���܂�
		int rotRem = hpl::math::getPointRotationTypeFromLine(
			wpoint.x, wpoint.y, epStart->vertex.x, epStart->vertex.y,
			epEnd->vertex.x, epEnd->vertex.y);
        if(rotRem == hpl::math::RotationType::Clockwise &&
            startLine->counterclockwise_polygon_owner != NONE)
        {
            //�E����ŁA�����̉E���i�w��_�̂���̈�j
            //�Ƀ|���S�������ɂ���ꍇ�X�L�b�v
            hpl::error::caution("already polygon exists");
            continue;
        }
        if(rotRem == hpl::math::RotationType::Counterclockwise &&
            startLine->clockwise_polygon_owner != NONE)
        {
            hpl::error::caution("already polygon exists");
            continue;
        }
        //����ȍ~�͂��łɎw��_�̕����Ƀ|���S�����Ȃ��Ɖ��肷��

        //��_
		int nowBasePointIndex = endPointIndex;
        int prevLineIndex = lineIndexBase;
		//TODO
        //startLine->endpoint_indexes[1]����Ȃ�����𒲂ׂ�
        std::vector<int> pointIndexes;
        //�ŏ��̓�������Ă���
        pointIndexes.push_back(startPointIndex);
        pointIndexes.push_back(endPointIndex);

        bool found = getValidLines(nowBasePointIndex, prevLineIndex,
            &pointIndexes, smgr, rotRem, &doneList,
            zMin, zMax, wpoint);
        if(found){
            //�����I
            //�_�C���f�b�N�X�i�l�n���p�j
            int indexes[MAXIMUM_VERTICES_PER_POLYGON];

            //�_�f�[�^�W�v
            for(int l = 0; l < (int)pointIndexes.size() - 1; l ++){
                //
                indexes[l] = pointIndexes[l];
            }
            int vertexCount = (int)pointIndexes.size() - 1;
            //�|���S���쐬
            polygon_data poly;
            hpl::aleph::map::createPolygon(indexes, vertexCount, &poly);
            
            polyDatas.push_back(poly);

            //TODO ���������o���̂��H
            //�������H���̂��Ƃ��ˁH
            //���o�I�ɋ߂��������΂����񂶂�ˁH
            break;
        }
        doneList.insert(i);
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
*
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
        pdata.endpoint_indexes[i] = i; //* clockwise *
        pdata.line_indexes[i] = i;
        pdata.side_indexes[i] = NONE;
    }
	
	pdata.floor_texture = NONE;
    pdata.ceiling_texture = NONE;
	pdata.floor_height = 0;
    pdata.ceiling_height = WORLD_ONE;
	pdata.floor_lightsource_index = NONE;
    pdata.ceiling_lightsource_index = NONE;
	
//	pdata.area; 
	
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
*/
/**
    �Ɨ������|���S���f�[�^��ǉ����܂�
*
void hpl::aleph::map::addNewPolygon(polygon_data& pdata, endpoint_data epd[],
                                    line_data ld[], int n)
{
    //�_
    std::map<int,int> epIndexTable;
    std::string str;
    for(int i = 0; i < n; i ++){
        //�_�̒ǉ�
		int newIndex = hpl::aleph::map::addEndpoint(epd[i]);
        epIndexTable[i] = newIndex;

    }
//    const char *buf = str.c_str();

    //���̒ǉ�
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
        pdata.line_indexes[i] = lIndexTable[pdata.line_indexes[i]];
        pdata.side_indexes[i] = NONE;
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
*/

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
    //endpoint�̍쐬
    int epIndexes[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < n; i ++){
        //endpoint�̐���
        endpoint_data ep;
        hpl::aleph::map::createPoint(points[i], &ep);
        int epIndex = hpl::aleph::map::addEndpoint(ep);
        epIndexes[i] = epIndex;
    }

    //line�̍쐬
    //int lineIndexes[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < n; i ++){
        int next = i + 1;
        if(next >= n){
            next = 0;
        }
        line_data line;
        hpl::aleph::map::createLine(epIndexes[i], epIndexes[next], &line);
        int lineIndex = hpl::aleph::map::addLine(line);
        //lineIndexes[i] = lineIndex;
    }
    polygon_data poly;
    hpl::aleph::map::createPolygon(epIndexes, n, &poly);
    hpl::aleph::map::addPolygon(poly);
}


#include "HPLMapTool.h"
#include "HPLMath.h"
#include <limits.h>
#include "HPLQuickSort.h"
#include <fstream>
#include "HPLError.h"
#include "HPLStringModifier.h"
#include "map.h"
#include "platforms.h"
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
	return index;
}
int hpl::aleph::map::addPolygon(polygon_data polygon)
{
	PolygonList.push_back(polygon);
	dynamic_world->polygon_count = (int16)PolygonList.size();
	int index = dynamic_world->polygon_count - 1;

	if(!hpl::aleph::map::isValidIndex(index, PolygonList.size())){
		return NONE;
	}
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
#ifdef __WXDEBUG__
        wxASSERT(ep1);
#else
        if(!ep1)continue;
#endif
        //�֘A�|���S���̎w�肪������Ύw��
        if(!hpl::aleph::map::isValidIndex(ep1->supporting_polygon_index,
			PolygonList.size()))
		{
            ep1->supporting_polygon_index = index;
        }

        endpoint_data* ep2 = get_endpoint_data(poly->endpoint_indexes[next]);
#ifdef __WXDEBUG__
        wxASSERT(ep2);
#else
        if(!ep2)continue;
#endif

/*        //��
        line_data* line = get_line_data(poly->line_indexes[i]);
#ifdef __WXDEBUG__
        wxASSERT(line);
#else
        if(!line)continue;
#endif
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
            continue;
//            hpl::error::halt("invalid polygon frame");
#endif
        }*/
    }
	return index;
}
int hpl::aleph::map::addMapSavedObject(map_object object)
{
	SavedObjectList.push_back(object);
	//TODO
	//�v���[�X�����g���ɕt��

	//�ǉ������Ƃ��A���̓_�����|���S���ɃI�u�W�F�N�g�̃|���S���ԍ���ݒ肷��
	//	�O���ł���Ă�

	//TODO �ǂ���W�v����Ηǂ��̂��H
//	dynamic_world->object_count ++;// SavedObjectList.size();
	dynamic_world->initial_objects_count = (int16)SavedObjectList.size();
	int index = dynamic_world->initial_objects_count - 1;
	
	
    map_object* obj = &SavedObjectList[index];

	//placement �����`�F�b�N�B
	object_frequency_definition* placement =
		hpl::aleph::map::getPlacementData(object.type, object.index);
	hpl::aleph::map::updateObjectInitialPlacement(obj->type, obj->index);

    //�ˑ����鍀�ڂ��C������
    //�E�|���S��
	hpl::aleph::map::isValidIndex(obj->polygon_index, PolygonList.size());
	/*
	if(!hpl::aleph::map::isValidIndex(obj->polygon_index)){
		obj->polygon_index = NULL;
	}else{
	    polygon_data* poly = get_polygon_data(obj->polygon_index);
	}
	*/
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
									 std::vector<bool>& delPolygons,
                                     std::vector<bool>& delSides,
								    std::vector<bool>& delObjects)
{
    if(delPoints.size() < EndpointList.size() ||
        EndpointList.size() != dynamic_world->endpoint_count ||
        delLines.size() < LineList.size() ||
        LineList.size() != dynamic_world->line_count ||
        delSides.size() < SideList.size() ||
        SideList.size() != dynamic_world->side_count ||
        delPolygons.size() < PolygonList.size() ||
        PolygonList.size() != dynamic_world->polygon_count ||
        delObjects.size() < SavedObjectList.size())
    {
        hpl::error::caution("dismatch delP[%d],EndpointList.size()[%d],world.endpoint_count[%d]",
			delPoints.size(), EndpointList.size(), dynamic_world->endpoint_count);
        hpl::error::caution("dismatch delL[%d],LineList.size()[%d],world.line_count[%d]",
			delLines.size(), LineList.size(), dynamic_world->line_count);
        hpl::error::caution("dismatch delPoly[%d],PolygonList.size()[%d],world.polygon_count[%d]",
			delPolygons.size(), PolygonList.size(), dynamic_world->polygon_count);
        hpl::error::caution("dismatch delS[%d],SideList.size()[%d],world.side_count[%d]",
			delSides.size(), SideList.size(), dynamic_world->side_count);
        hpl::error::halt("dismatch delO[%d],SavedObjectList.size()[%d],world.initial[%d]",
			delObjects.size(), SavedObjectList.size(), dynamic_world->initial_objects_count);
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
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        if(!delPoints[i]){   indexMapPoints[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)LineList.size(); i ++){
        if(!delLines[i]){   indexMapLines[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        if(!delPolygons[i]){   indexMapPolygons[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)SideList.size(); i ++){
        if(!delSides[i]){   indexMapSides[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        if(!delObjects[i]){   indexMapObjects[i] = counter;   counter ++;}
    }
	//TODO Platform
	
	//�폜���܂�
	for(int i = (int)EndpointList.size() - 1; i >= 0; i --){
		if(delPoints[i]){
			EndpointList.erase(EndpointList.begin() + i);
		}
	}
	for(int i = (int)LineList.size() - 1; i >= 0; i --){
		if(delLines[i]){
			LineList.erase(LineList.begin() + i);
		}
	}
	for(int i = (int)PolygonList.size() - 1; i >= 0; i --){
		if(delPolygons[i]){
			PolygonList.erase(PolygonList.begin() + i);
		}
	}
	for(int i = (int)SideList.size() - 1; i >= 0; i --){
		if(delSides[i]){
			SideList.erase(SideList.begin() + i);
		}
	}
	for(int i = (int)SavedObjectList.size() - 1; i >= 0; i --){
		if(delObjects[i]){
			SavedObjectList.erase(SavedObjectList.begin() + i);
		}
	}
	/*
	for(int i = (int)delPlatforms.size() - 1; i >= 0; i --){
		if(delPlatforms[i]){
			PlatformList.erase(PlatformList.begin() + i);
		}
	}*/
	
    //�C���f�b�N�X��t������
	hpl::aleph::map::changeIndexMapping(
		EndpointList,
		LineList,
		PolygonList,
		SideList,
		SavedObjectList,
		0, (int)EndpointList.size(),
		0, (int)LineList.size(),
		0, (int)PolygonList.size(),
		0, (int)SideList.size(),
		0, (int)SavedObjectList.size(),
		indexMapPoints, indexMapLines, indexMapPolygons, indexMapSides, indexMapObjects);
    return true;
}


/**
	�}�b�v�A�C�e���̃C���f�b�N�X���w�肵���e�[�u���ɏ]���ĕύX���܂��B
	<en> change map items' indexes with prepared index map
	@param *List ���̃}�b�v�C���f�b�N�X�ō\�����ꂽ�I�u�W�F�N�g�f�[�^
	@param *IndexMap <originalIndex, newIndex>
*/
void hpl::aleph::map::changeIndexMapping(
	std::vector<endpoint_data>& endpointList, std::vector<line_data>& lineList, 
	std::vector<polygon_data>& polygonList, std::vector<side_data>& sideList,
	std::vector<map_object>& objectList,
	int endpointIndexStart, int endpointIndexEnd,
	int lineIndexStart, int lineIndexEnd,
	int polygonIndexStart, int polygonIndexEnd,
	int sideIndexStart, int sideIndexEnd,
	int objectIndexStart, int objectIndexEnd,
	std::map<int, int>& endpointIndexMap, std::map<int, int>& lineIndexMap, 
	std::map<int, int>& polygonIndexMap, std::map<int, int>& sideIndexMap, 
	std::map<int, int>& objectIndexMap)
{
	//points
    for(int i = endpointIndexStart; i < endpointIndexEnd; i ++){
#ifdef _WXDEBUG_
		wxASSERT(endpointIndexStart >= 0 && endpointIndexStart <= (int)endpointList.size() &&
			endpointIndexStart <= endpointIndexEnd && endpointIndexEnd <= (int)endpointList.size());
#endif
		endpoint_data* ep = &endpointList[i];
		//��������|���S��Index
		std::map<int, int>::iterator it = polygonIndexMap.find(ep->supporting_polygon_index);
		if(it == polygonIndexMap.end()){
			//���݂��Ȃ�
			//�_��L����|���S����T��
			int orgIndex = getKeyByValue(endpointIndexMap, i);
			wxASSERT(orgIndex >= 0);

			std::vector<int> belongPolygonIndexes = hpl::aleph::map::getPolygonIndexesIncludePoint(orgIndex);
			bool found = false;
			for(int j = 0; j < (int)belongPolygonIndexes.size(); j ++){
				int polyIndex = belongPolygonIndexes[j];
				//�o�^�����|���S���Ɋ܂܂�Ă��邩�ǂ����������܂�
				if(polygonIndexMap.find(polyIndex) == polygonIndexMap.end()){
					//�܂܂�Ȃ�
				}else{
					//���Ɋ܂܂��
					//�����ΏۂƂ���
					found = true;
					ep->supporting_polygon_index = belongPolygonIndexes[j];
					wxASSERT(ep->supporting_polygon_index >= 0);
					break;
				}
			}
			if(!found){
				//�ǉ�����|���S���̓X�g�b�N����Ă��Ȃ�
				//NONE�Ƃ���
				ep->supporting_polygon_index = NONE;
			}
		}else{
			//���݂���
			ep->supporting_polygon_index = it->second;
			wxASSERT(it->second >= 0);
		}
    }

    //lines
    for(int i = lineIndexStart; i < lineIndexEnd; i ++){
		line_data* line = &lineList[i];
		//�������Ă���_�f�[�^
		for(int j = 0; j < 2; j ++){
			int epIndex = line->endpoint_indexes[j];
			wxASSERT(epIndex >= 0);
			//�X�V
			line->endpoint_indexes[j] = endpointIndexMap[epIndex];
			wxASSERT(endpointIndexMap[epIndex] >= 0);
		}
		//�������Ă���T�C�h�f�[�^
		//��������|���S���f�[�^
		{
			int clockPoly = line->clockwise_polygon_owner;
			int clockSide = line->clockwise_polygon_side_index;
			if(clockPoly >= 0){
				//�|���S����o�^���Ă��邩
				std::map<int, int>::iterator it = polygonIndexMap.find(clockPoly);
				if(it != polygonIndexMap.end()){
					//�|���S�������݂���
					if(clockSide >= 0 &&
						sideIndexMap.find(clockSide) != sideIndexMap.end())
					{
						//Side�����݂���
						wxASSERT(sideIndexMap[clockSide] >= 0);
						clockSide = sideIndexMap[clockSide];
					}else{
						clockSide = NONE;
					}
					clockPoly = it->second;
				}else{
					clockPoly = NONE;
					clockSide = NONE;
				}
			}else{
				//�|���S�������݂��Ȃ�
				clockSide = NONE;
			}
			line->clockwise_polygon_side_index = clockSide;
			line->clockwise_polygon_owner = clockPoly;
		}

		{
			//counter clock side 
			int counterPoly = line->counterclockwise_polygon_owner;
			int counterSide = line->counterclockwise_polygon_side_index;
			if(counterPoly >= 0){
				//�|���S����o�^���Ă��邩
				std::map<int, int>::iterator it = polygonIndexMap.find(counterPoly);
				if(it != polygonIndexMap.end()){
					if(counterSide >= 0 && sideIndexMap.find(counterSide) != sideIndexMap.end()){
						counterSide = sideIndexMap[counterSide];
					}else{
						counterSide = NONE;
					}
					counterPoly = it->second;
				}else{
					counterSide = NONE;
					counterPoly = NONE;
				}
			}else{
				counterSide = NONE;
			}
			line->counterclockwise_polygon_side_index = counterSide;
			line->counterclockwise_polygon_owner = counterPoly;
		}

    }

    //polygons
    for(int i = polygonIndexStart; i < polygonIndexEnd; i ++){
		polygon_data* poly = &polygonList[i];

		int n = poly->vertex_count;

		//��������_�C���f�b�N�X
		//<en> modify endpoint indexes
		for(int i = 0; i < n; i ++){
			poly->endpoint_indexes[i] = endpointIndexMap[poly->endpoint_indexes[i]];
			wxASSERT(poly->endpoint_indexes[i] >= 0);
		}

		//����������C���f�b�N�X
		//<en> modify line indexes
		for(int i = 0; i < n; i ++){
			poly->line_indexes[i] = endpointIndexMap[poly->line_indexes[i]];
			wxASSERT(poly->line_indexes[i] >= 0);
		}

		//��������Side�C���f�b�N�X
		//<en> modify side indexes
		for(int i = 0; i < n; i ++){
			if(poly->side_indexes[i] == NONE){
			}else{
				poly->side_indexes[i] = endpointIndexMap[poly->side_indexes[i]];
				wxASSERT(poly->side_indexes[i] >= 0);
			}
		}

    }

	//sides 
	for(int i = sideIndexStart; i < sideIndexEnd; i ++){
		side_data* side = &sideList[i];
		//���������
		int lineIndex = side->line_index;
#ifdef _WXDEBUG_
		wxASSERT(lineIndex >= 0);
#endif
		side->line_index = lineIndexMap[lineIndex];
		wxASSERT(side->line_index >= 0);

		//��������|���S��
		int polyIndex = side->polygon_index;
#ifdef _WXDEBUG_
		wxASSERT(polyIndex >= 0);
#endif
		side->polygon_index = polygonIndexMap[polyIndex];
	}

	//objects
    for(int i = objectIndexStart; i < objectIndexEnd; i ++){
		map_object* obj = &objectList[i];
		wxASSERT(obj->polygon_index >= -1);
		//��������|���S��
		if(obj->polygon_index >= 0 && 
			polygonIndexMap.find(obj->polygon_index) != polygonIndexMap.end()){
			obj->polygon_index = polygonIndexMap[obj->polygon_index];
			wxASSERT(obj->polygon_index >= 0);
		}else{
			obj->polygon_index = NONE;
		}
		//���ǂ̓y�[�X�g���E�ړ����ɂ��̂Ƃ���������Ă���|���S���ɏ������邱�ƂɂȂ�̂ł��������Ӗ��͂Ȃ�
    }
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
#ifdef __WXDEBUG__
        wxASSERT(false);
#else
        return false;
#endif

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
        if(smgr->isDeleteLine(conLineIndex)){
            continue;
        }
        //�x�[�X�̐��ƈꏏ�̏ꍇ�����O����
        if(baseLineIndex == conLineIndex){
            continue;
        }

        line_data* line = get_line_data(conLineIndex);
#ifdef __WXDEBUG__
        wxASSERT(line );
#else
        if(!line )continue;
#endif
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
#ifdef __WXDEBUG__
            wxASSERT(false );
#else
            continue;
#endif
        }

        endpoint_data* ep0 = get_endpoint_data(ep0Index);
#ifdef __WXDEBUG__
        wxASSERT(ep0 );
#else
        if(!ep0 )continue;
#endif
        endpoint_data* ep1 = get_endpoint_data(ep1Index);
#ifdef __WXDEBUG__
        wxASSERT(ep1 );
#else
        if(!ep1 )continue;
#endif

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
#ifdef __WXDEBUG__
        wxASSERT(prevStartEp );
#else
        if(!prevStartEp )continue;
#endif
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
        if(smgr->isDeleteLine(i)){
            continue;
        }
        //���łɒ��ׂ����Ȃ疳��
        if(doneList.find(i) != doneList.end()){
            continue;
        }
        int lineIndexBase = pairs[i].index;
        line_data* startLine = get_line_data(lineIndexBase);
#ifdef __WXDEBUG__
        wxASSERT(startLine );
#else
        if(!startLine )continue;
#endif
        //�����`�F�b�N
        if(!hpl::aleph::map::isValidHeight(startLine->highest_adjacent_floor,
            startLine->lowest_adjacent_ceiling, zMin, zMax))
        {
            continue;
        }

        int startPointIndex = startLine->endpoint_indexes[0];
		endpoint_data* epStart = get_endpoint_data(startPointIndex);
#ifdef __WXDEBUG__
        wxASSERT(epStart );
#else
        if(!epStart )continue;
#endif
        int endPointIndex = startLine->endpoint_indexes[1];
		endpoint_data* epEnd = get_endpoint_data(endPointIndex);
#ifdef __WXDEBUG__
        wxASSERT(epEnd );
#else
        if(!epEnd )continue;
#endif

        //���̍��E�ǂ���̑��ɓ_�����邩���`�F�b�N���܂�
		int rotRem = hpl::math::getPointRotationTypeFromLine(
			wpoint.x, wpoint.y, epStart->vertex.x, epStart->vertex.y,
			epEnd->vertex.x, epEnd->vertex.y);
        if(rotRem == hpl::math::RotationType::Clockwise &&
            startLine->counterclockwise_polygon_owner != NONE)
        {
            //�E����ŁA�����̉E���i�w��_�̂���̈�j
            //�Ƀ|���S�������ɂ���ꍇ�X�L�b�v
//            hpl::error::caution("already polygon exists");
            continue;
        }
        if(rotRem == hpl::math::RotationType::Counterclockwise &&
            startLine->clockwise_polygon_owner != NONE)
        {
//            hpl::error::caution("already polygon exists");
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


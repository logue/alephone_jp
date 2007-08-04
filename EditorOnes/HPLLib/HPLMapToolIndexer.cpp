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
#include <map>

///////////////////////////////////
//	�v���g�^�C�v
//	prototypes
static void changeSidePolygonIndexOfLine(line_data* line,
							   std::map<int, int>& polygonIndexMap,
							   std::map<int, int>& sideIndexMap,
							   bool isClockwise);
static void changeChildIndex(int16 indexes[], int num,
								std::map<int, int>& indexMap);

/**
	���ɑ΂��āA���ꂪ�֘A����Side��Polygon�̃C���f�b�N�X�𒲐����܂��B
	�Ώۂ��C���f�b�N�X�ϊ��}�b�v�ɑ��݂��Ȃ����NONE��������܂�
	@param isClockwise �E�E���v���̘b�Ȃ�^
*/
static void changeSidePolygonIndexOfLine(line_data* line,
							   std::map<int, int>& polygonIndexMap,
							   std::map<int, int>& sideIndexMap,
							   bool isClockwise)
{
	int polyIndex = line->clockwise_polygon_owner;
	int sideIndex = line->clockwise_polygon_side_index;
	if(!isClockwise){
		polyIndex = line->counterclockwise_polygon_owner;
		sideIndex = line->counterclockwise_polygon_side_index;
	}

	wxASSERT(polyIndex >= NONE);
	wxASSERT(sideIndex >= NONE);

	if(polyIndex >= 0){

		//�|���S�����C���f�b�N�X�ϊ��}�b�v�ɓo�^���Ă��邩
		std::map<int, int>::iterator it = polygonIndexMap.find(polyIndex);

		if(it != polygonIndexMap.end()){

			//�|���S�������݂���
			if(sideIndex >= 0 &&
				sideIndexMap.find(sideIndex) != sideIndexMap.end())
			{
				//Side�����݂���
				wxASSERT(sideIndexMap[sideIndex] >= 0);
				sideIndex = sideIndexMap[sideIndex];
			}else{
				//Side�����݂��Ȃ��i�܂����e�͈͓̔��j
				sideIndex = NONE;
			}
			polyIndex = it->second;
			wxASSERT(polyIndex >= 0);
		}else{
			//�w�肳��Ă��Ȃ�
			polyIndex = NONE;
			sideIndex = NONE;
		}
	}else if(polyIndex == NONE){
		//�|���S�������݂��Ȃ�
		sideIndex = NONE;
	}else{
		//�s��l
		wxASSERT(false);
	}
	if(isClockwise){
		line->clockwise_polygon_owner = polyIndex;
		line->clockwise_polygon_side_index = sideIndex;
		wxASSERT(line->clockwise_polygon_owner >= -1);
		wxASSERT(line->clockwise_polygon_side_index >= -1);
	}else{
		line->counterclockwise_polygon_owner = polyIndex;
		line->counterclockwise_polygon_side_index = sideIndex;
		wxASSERT(line->counterclockwise_polygon_owner >= -1);
		wxASSERT(line->counterclockwise_polygon_side_index >= -1);
	}
}
/**
	
*/
static void changeChildIndex(int16 indexes[], int num,
								std::map<int, int>& indexMap)
{
	//�������Ă���_�f�[�^
	for(int j = 0; j < num; j ++){
		int index = indexes[j];
		wxASSERT(index >= 0);
		//�X�V
		wxASSERT(indexMap.find(index) != indexMap.end());
		indexes[j] = indexMap[index];
		wxASSERT(indexMap[index] >= 0);
	}
}
/**
	�}�b�v�A�C�e���̃C���f�b�N�X���w�肵���e�[�u���ɏ]���ĕύX���܂��B
	<en> change map items' indexes with prepared index map
	@param *List ���̃}�b�v�C���f�b�N�X�ō\�����ꂽ�I�u�W�F�N�g�f�[�^
	@param *IndexMap <originalIndex, newIndex>

	�Ή���
	???IndexStart		:	a
	???IndexStart + 1	:	b
	???IndexStart + 2	:	c
	�ƂȂ��Ă���AoriginalIndex��endpointList�ȂǁA
	�x�N�^�̗v�f�̃C���f�b�N�X�ɑΉ����Ă���A���ꂼ��
	[0]	:	???IndexStart		:	a
	[1]	:	???IndexStart + 1	:	b
	�ƂȂ�
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
	/*
		�������`�F�b�N
		0 <= start <= end <= list.size()
	*/
	wxASSERT(endpointIndexStart >= 0 &&
		endpointIndexStart <= (int)endpointList.size() &&
		endpointIndexStart <= endpointIndexEnd &&
		endpointIndexEnd <= (int)endpointList.size() &&
		endpointIndexEnd - endpointIndexStart == (int)endpointIndexMap.size());
	wxASSERT(lineIndexStart >= 0 &&
		lineIndexStart <= (int)lineList.size() &&
		lineIndexStart <= lineIndexEnd &&
		lineIndexEnd <= (int)lineList.size() &&
		lineIndexEnd - lineIndexStart == (int)lineIndexMap.size());
	wxASSERT(polygonIndexStart >= 0 &&
		polygonIndexStart <= (int)polygonList.size() &&
		polygonIndexStart <= polygonIndexEnd &&
		polygonIndexEnd <= (int)polygonList.size() &&
		polygonIndexEnd - polygonIndexStart == (int)polygonIndexMap.size());
	wxASSERT(sideIndexStart >= 0 &&
		sideIndexStart <= (int)sideList.size() &&
		sideIndexStart <= sideIndexEnd &&
		sideIndexEnd <= (int)sideList.size() &&
		sideIndexEnd - sideIndexStart == (int)sideIndexMap.size());
	wxASSERT(objectIndexStart >= 0 &&
		objectIndexStart <= (int)objectList.size() &&
		objectIndexStart <= objectIndexEnd &&
		objectIndexEnd <= (int)objectList.size() &&
		objectIndexEnd - objectIndexStart == (int)objectIndexMap.size());

	//points
    for(int i = endpointIndexStart; i < endpointIndexEnd; i ++){
		endpoint_data* ep = &endpointList[i];

		//�_����������|���S�����擾���܂�
		//get polygon endpoint belongs to 
		std::map<int, int>::iterator it = 
			polygonIndexMap.find(ep->supporting_polygon_index);
		if(it == polygonIndexMap.end()){
			//������Ȃ�

			//�_��L����|���S����T��
			//int orgIndex = getKeyByValue(endpointIndexMap, i);
			//wxASSERT(orgIndex >= 0);

			//hpl::aleph::map::getPolygonIndexesIncludePoint(orgIndex);
			//���̊֐��̓O���[�o���ϐ��ł���PolygonList���炳�����̂ŁA
			//�ėp�I�ł͂Ȃ�

			//�����polygonList����T��

			bool found = false;
			for(int j = polygonIndexStart; j < polygonIndexEnd; j ++){
				polygon_data* poly = &polygonList[j];
				for(int k = 0; k < poly->vertex_count; k ++){
					if(poly->endpoint_indexes[k] == i){
						//���݂���
						wxASSERT(polygonIndexMap.find(j) != polygonIndexMap.end());
						ep->supporting_polygon_index = polygonIndexMap[j];
						wxASSERT(ep->supporting_polygon_index >= 0);
						found = true;
						break;
					}
				}
				if(found){
					break;
				}
			}
			if(!found){
				//�ǉ�����|���S���̓X�g�b�N����Ă��Ȃ�
				//NONE�Ƃ���
				ep->supporting_polygon_index = NONE;
			}

		}else{	//	it != polygonIndexMap.end()
			//���݂���
			//iterator��pair�ł���A���̃����o�ł���second�͕ϊ���̃C���f�b�N�X�l
			//����Ă����������΂悢
			ep->supporting_polygon_index = it->second;
			wxASSERT(it->second >= 0);
		}
		wxASSERT(ep->supporting_polygon_index >= -1);
    }

    //lines
    for(int i = lineIndexStart; i < lineIndexEnd; i ++){
		line_data* line = &lineList[i];
		//�������Ă���_�f�[�^
		changeChildIndex(line->endpoint_indexes, 2, endpointIndexMap);

		//�������Ă���T�C�h�f�[�^
		//��������|���S���f�[�^
		bool isClockwise = true;
		changeSidePolygonIndexOfLine(line, polygonIndexMap, sideIndexMap, isClockwise);
		isClockwise = false;
		changeSidePolygonIndexOfLine(line, polygonIndexMap, sideIndexMap, isClockwise);
    }

    //polygons
    for(int i = polygonIndexStart; i < polygonIndexEnd; i ++){
		polygon_data* poly = &polygonList[i];

		int n = poly->vertex_count;

		//��������_�C���f�b�N�X
		//<en> modify endpoint indexes
		changeChildIndex(poly->endpoint_indexes, n, endpointIndexMap);

		//����������C���f�b�N�X
		//<en> modify line indexes
		changeChildIndex(poly->line_indexes, n, lineIndexMap);

		//��������Side�C���f�b�N�X
		//NONE������̂�
		//<en> modify side indexes
		for(int i = 0; i < n; i ++){
			int sideIndex = poly->side_indexes[i];
			if(sideIndex == NONE){
			}else{
				wxASSERT(sideIndexMap.find(sideIndex) != sideIndexMap.end());
				poly->side_indexes[i] = sideIndexMap[sideIndex];
				wxASSERT(poly->side_indexes[i] >= 0);
			}
		}

    }

	//sides 
	for(int i = sideIndexStart; i < sideIndexEnd; i ++){
		side_data* side = &sideList[i];
		//���������
		int lineIndex = side->line_index;
		wxASSERT(lineIndex >= 0 && lineIndexMap.find(lineIndex) != lineIndexMap.end());
		side->line_index = lineIndexMap[lineIndex];
		wxASSERT(side->line_index >= 0);

		//��������|���S��
		int polyIndex = side->polygon_index;
		wxASSERT(polyIndex >= 0 && polygonIndexMap.find(polyIndex) != polygonIndexMap.end());
		side->polygon_index = polygonIndexMap[polyIndex];
		wxASSERT(side->polygon_index >= 0);
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

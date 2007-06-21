#include "HPLMapTool.h"
#include "HPLMath.h"
#include <limits.h>
#include "HPLQuickSort.h"
#include <fstream>
#include "HPLError.h"
#include "HPLStringModifier.h"

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
        delPoints.size() != dynamic_world.endpoint_count ||
        delLines.size() != LineList.size() ||
        delLines.size() != dynamic_world.line_count ||
        delSides.size() != SideList.size() ||
        delSides.size() != dynamic_world.side_count ||
        delPolygons.size() != PolygonList.size() ||
        delPolygons.size() != dynamic_world.polygon_count ||
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
}

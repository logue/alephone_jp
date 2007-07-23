#include "HPLRealMapData.h"
#include "HPLError.h"
#include "HPLMapTool.h"

#include <memory.h>

hpl::aleph::map::HPLRealMapData::HPLRealMapData()
{
}
hpl::aleph::map::HPLRealMapData::~HPLRealMapData()
{
    //this->removeAll();
}


//�R�s�[�Ώۂ̃}�b�v�f�[�^(�I�𕔕�)
void hpl::aleph::map::HPLRealMapData::set(hpl::aleph::map::HPLSelectData& copyTargetData)
{
    removeAll();

	//<int, int> = <originalIndex, newIndex>
	std::map<int, int> pointIndexMap;
	
    //points
    for(int i = 0; i < (int)copyTargetData.getSelPoints()->size(); i ++){
        int index = copyTargetData.getSelPoints()->at(i).index;
		addPoint(index, pointIndexMap);
    }

	std::map<int, int> lineIndexMap;
    //lines
    for(int i = 0; i < (int)copyTargetData.getSelLines()->size(); i ++){
        addLine(copyTargetData.getSelLines()->at(i).index, lineIndexMap, pointIndexMap);

    }

	std::map<int, int> polygonIndexMap;
	std::map<int, int> sideIndexMap;
    //polygons
    for(int i = 0; i < (int)copyTargetData.getSelPolygons()->size(); i ++){
        int index = copyTargetData.getSelPolygons()->at(i).index;
		addPolygon(index, polygonIndexMap, lineIndexMap, pointIndexMap, sideIndexMap);
    }

	//objects
	std::map<int, int> objectIndexMap;
    for(int i = 0; i < (int)copyTargetData.getSelObjects()->size(); i ++){
        int index = copyTargetData.getSelObjects()->at(i).index;
        addObject(index, objectIndexMap);
    }

	//////////////////////////////
	//�C���f�b�N�X�𒲐�����
	//�Ώۂ����݂��Ȃ��ꍇ�ł��A
	//	���݂��v���I�ł���ꍇ�̓G���[�\��(�o�O)
	//	���݂��v���I�łȂ��ꍇ��NONE�Ƃ���
	hpl::aleph::map::changeIndexMapping(
		*this->getPoints(),
		*this->getLines(),
		*this->getPolygons(),
		*this->getSides(),
		*this->getObjects(),
		0, this->getPoints()->size(),
		0, this->getLines()->size(),
		0, this->getPolygons()->size(),
		0, this->getSides()->size(),
		0, this->getObjects()->size(),
		pointIndexMap,
		lineIndexMap,
		polygonIndexMap,
		sideIndexMap,
		objectIndexMap);
}

void hpl::aleph::map::HPLRealMapData::addObject(int index, std::map<int, int>& objectIndexMap){
    map_object* org = &SavedObjectList[index];
    map_object copy;
    memcpy(&copy, org, sizeof(map_object));
    this->realObjects.push_back(copy);

	//new index registering
	objectIndexMap[index] = (int)realObjects.size() - 1;
}
void hpl::aleph::map::HPLRealMapData::addPoint(int index, std::map<int, int>& pointIndexMap)
{
	//���ɒǉ����Ă��Ȃ����`�F�b�N
	if(pointIndexMap.find(index) != pointIndexMap.end()){
		return;
	}
    endpoint_data* org = get_endpoint_data(index);
    endpoint_data copy;
    memcpy(&copy, org, sizeof(endpoint_data));
    this->realPoints.push_back(copy);

	//new index registering
	pointIndexMap[index] = (int)realPoints.size() - 1;
}

void hpl::aleph::map::HPLRealMapData::addLine(int index, std::map<int, int>& lineIndexMap
											  , std::map<int, int>& pointIndexMap)
{
	if(lineIndexMap.find(index) != lineIndexMap.end()){
		return;
	}
    line_data* org = get_line_data(index);
    line_data copy;
    memcpy(&copy, org, sizeof(line_data));
    this->realLines.push_back(copy);

	//new index registering
	lineIndexMap[index] = (int)realLines.size() - 1;

	//���ɏ�������_��ǉ����� <en> add points belonged to the line
	for(int i = 0; i < 2; i ++){
		int epointIndex = copy.endpoint_indexes[i];
		addPoint(epointIndex, pointIndexMap);
	}
}
void hpl::aleph::map::HPLRealMapData::addPolygon(int index, std::map<int, int>& polygonIndexMap,
												 std::map<int, int>& lineIndexMap,
												 std::map<int, int>& pointIndexMap,
												 std::map<int, int>& sideIndexMap)
{
	//���łɒǉ����Ă�����X�L�b�v
	if(polygonIndexMap.find(index) != polygonIndexMap.end()){
		return;
	}
	polygon_data* org = get_polygon_data(index);
    polygon_data copy;
    memcpy(&copy, org, sizeof(polygon_data));
    this->realPolygons.push_back(copy);

	//new index registering
	polygonIndexMap[index] = (int)realPolygons.size() - 1;

	//lines
	int vertexCount = copy.vertex_count;
	for(int i = 0; i < vertexCount; i ++){
		int lineIndex = copy.line_indexes[i];
		//���ɒǉ��������̓X�L�b�v
		if(lineIndexMap.find(lineIndex) != lineIndexMap.end()){
			continue;
		}
		addLine(lineIndex, lineIndexMap, pointIndexMap);

		//���ɏ������A���|���S������Side��ǉ�����
		//����ȊO�̐���Side���ǉ�����Ȃ��̂�NONE�ɂȂ�
		//<en> add side belonged to the line which belonged to this polygon
		//TODO
		int sideIndex = copy.side_indexes[i];
		if(sideIndex != NONE){
			addSide(sideIndex, sideIndexMap);
		}
	}

	
}
void hpl::aleph::map::HPLRealMapData::addSide(int index, std::map<int, int>& sideIndexMap){
    side_data* org = get_side_data(index);
    side_data copy;
    memcpy(&copy, org, sizeof(side_data));
    this->realSides.push_back(copy);
	sideIndexMap[index] = (int)realSides.size() - 1;

}
//��������f�[�^�������܂�
void hpl::aleph::map::HPLRealMapData::removeAll()
{
    this->realObjects.clear();
    this->realPoints.clear();
    this->realLines.clear();
    this->realPolygons.clear();
    this->realSides.clear();
}
std::vector<map_object>* hpl::aleph::map::HPLRealMapData::getObjects()
{
    return &this->realObjects;
}
std::vector<endpoint_data>* hpl::aleph::map::HPLRealMapData::getPoints()
{
    return &this->realPoints;
}
std::vector<line_data>* hpl::aleph::map::HPLRealMapData::getLines()
{
    return &this->realLines;
}
std::vector<polygon_data>* hpl::aleph::map::HPLRealMapData::getPolygons()
{
    return &this->realPolygons;
}
std::vector<side_data>* hpl::aleph::map::HPLRealMapData::getSides()
{
    return &this->realSides;
}

//�f�[�^�����݂��邩�m���߂܂�
bool hpl::aleph::map::HPLRealMapData::isEmpty()
{
	if( this->getObjects()->size() == 0 &&
		this->getPoints()->size() == 0 &&
		this->getLines()->size() == 0 &&
		this->getPolygons()->size() == 0 &&
		this->getSides()->size() == 0)
	{
		return true;
	}
	return false;
}


/*
bool hpl::aleph::map::HPLRealMapData::containsPoint(int index)
{
	//���ɒǉ����Ă��Ȃ����`�F�b�N
	for(std::map<int, endpoint_data>::iterator it = this->getPoints()->begin();
		it != this->getPoints()->end(); it ++)
	{
		if(it->first == index){
			return true;
		}
	}
	return false;
}
bool hpl::aleph::map::HPLRealMapData::containsLine(int index)
{
	//���ɒǉ����Ă��Ȃ����`�F�b�N
	for(std::map<int, line_data>::iterator it = this->getLines()->begin();
		it != this->getLines()->end(); it ++)
	{
		if(it->first == index){
			return true;
		}
	}
	return false;
}
*/
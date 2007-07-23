#include "HPLCopyPasteManager.h"
hpl::aleph::HPLCopyPasteManager::HPLCopyPasteManager()
{
}
hpl::aleph::HPLCopyPasteManager::~HPLCopyPasteManager()
{
	this->clear();
}

/**
	�ێ����Ă���f�[�^�����������܂�
*/
void hpl::aleph::HPLCopyPasteManager::clear()
{
	this->storedMapData.removeAll();
}

/**
	�R�s�[���܂�
	���l�̑Ή��͈�U�����C���f�b�N�X�ɕϊ����܂�
	���݂��Ȃ����̂�NONE�ɂȂ�܂����A
	���݂̂̃R�s�[�̏ꍇ�A�V���ɓ_����t�������܂�
	@param sel �R�s�[���̑I���f�[�^
*/
void hpl::aleph::HPLCopyPasteManager::copy(hpl::aleph::map::HPLSelectData& sel)
{
	//������
	clear();

	this->storedMapData.set(&sel);
	//�ʒu�ݒ�
	storedDataDiffPointDelta[0] = COPY_AND_PASTE_DELTA_X;
	storedDataDiffPointDelta[1] = COPY_AND_PASTE_DELTA_Y;
}

/**
	�ێ����Ă�����e���y�[�X�g���܂�
	@return �y�[�X�g�Ɏ��s�����ꍇ�i�����ێ����Ă��Ȃ��Ƃ��j�ɋU
*/
bool hpl::aleph::HPLCopyPasteManager::paste(int div)
{
	if(this->storedMapData.isEmpty()){
		hpl::error::caution("No map items stored. No items are pasted. Copy items first.");
		return false;
	}
	
	std::map<int, int> endpointIndexMap;
	std::map<int, int> lineIndexMap;
	std::map<int, int> polygonIndexMap;
	std::map<int, int> sideIndexMap;
	std::map<int, int> objectIndexMap;

	//�_�̒ǉ�
	std::vector<endpoint_data>* endpointList = this->storedMapData.getPoints();
	for(int i = 0; i < (int)endpointList->size(); i ++){
		//�f�[�^���R�s�[����
		endpoint_data ep;
		memcpy(&ep, &endpointList[i], sizeof(endpoint_data));

		//�ʒu�����炷
		ep.vertex.x += storedDataDiffPointDelta[0] * div;
		ep.vertex.y += storedDataDiffPointDelta[1] * div;

		int newIndex = hpl::aleph::map::addEndpoint(ep);
		endpointIndexMap[i] = newIndex;
	}
	
	//add lines
	std::vector<line_data>* lineList = this->storedMapData.getLines();
	for(int i = 0; i < (int)lineList->size(); i ++){
		//�f�[�^���R�s�[����
		line_data line;
		memcpy(&line, &lineList[i], sizeof(line_data));

		//�����͈̂ʒu���������Ȃ����߁A���炷��Ƃ͂���Ȃ�

		int newIndex = hpl::aleph::map::addline(line);
		lineIndexMap[i] = newIndex;
	}
	
	//add polygons
	std::vector<polygon_data>* polygonList = this->storedMapData.getPolygons();
	for(int i = 0; i < (int)polygonList->size(); i ++){
		int newIndex = hpl::aleph::map::addPolygon(polygonList[i]);
		polygonIndexMap[i] = newIndex;
	}
	
	//add sides
	std::vector<side_data>* sideList = this->storedMapData.getSides();
	for(int i = 0; i < (int)sideList->size(); i ++){
		int newIndex = hpl::aleph::map::addSide(sideList[i]);
		sideIndexMap[i] = newIndex;
	}
	
	//add objects
	std::vector<map_object>* objectList = this->storedMapData.getObjects();
	for(int i = 0; i < (int)objectList->size(); i ++){
		map_object obj;
		memcpy(&obj, &objectList[i], sizeof(map_object));
		obj.location.x += storedDataDiffPointDelta[0] * div;
		obj.location.y += storedDataDiffPointDelta[1] * div;
		int newIndex = hpl::aleph::map::addObject(obj);
		objectIndexMap[i] = newIndex;
	}

	//�C���f�b�N�X����
	hpl::aleph::map::changeIndexMapping(
		EndpointList,
		LineList,
		PolygonList,
		SideList,
		SavedObjectList,
		EndpointList.size() - endpointList->size(), EndpointList.size(),
		LineList.size() - lineList->size(), LineList.size(),
		PolygonList.size() - polygonList->size(), PolygonList.size(),
		SideList.size() - sideList->size(), SideList.size(),
		SavedObjectList.size() - objectList->size(), SavedObjectList.size(),
		pointIndexMap,
		lineIndexMap,
		polygonIndexMap,
		sideIndexMap,
		objectIndexMap);


	storedDataDiffPointDelta[0] += COPY_AND_PASTE_DELTA_X;
	storedDataDiffPointDelta[1] += COPY_AND_PASTE_DELTA_Y;
	return true;
}

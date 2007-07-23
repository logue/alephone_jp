#include "HPLCopyPasteManager.h"
hpl::aleph::HPLCopyPasteManager::HPLCopyPasteManager()
{
}
hpl::aleph::HPLCopyPasteManager::~HPLCopyPasteManager()
{
	this->clear();
}

/**
	保持しているデータを初期化します
*/
void hpl::aleph::HPLCopyPasteManager::clear()
{
	this->storedMapData.removeAll();
}

/**
	コピーします
	数値の対応は一旦内部インデックスに変換します
	存在しないものはNONEになりますが、
	線のみのコピーの場合、新たに点情報を付け加えます
	@param sel コピー元の選択データ
*/
void hpl::aleph::HPLCopyPasteManager::copy(hpl::aleph::map::HPLSelectData& sel)
{
	//初期化
	clear();

	this->storedMapData.set(&sel);
	//位置設定
	storedDataDiffPointDelta[0] = COPY_AND_PASTE_DELTA_X;
	storedDataDiffPointDelta[1] = COPY_AND_PASTE_DELTA_Y;
}

/**
	保持している内容をペーストします
	@return ペーストに失敗した場合（何も保持していないとき）に偽
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

	//点の追加
	std::vector<endpoint_data>* endpointList = this->storedMapData.getPoints();
	for(int i = 0; i < (int)endpointList->size(); i ++){
		//データをコピーする
		endpoint_data ep;
		memcpy(&ep, &endpointList[i], sizeof(endpoint_data));

		//位置をずらす
		ep.vertex.x += storedDataDiffPointDelta[0] * div;
		ep.vertex.y += storedDataDiffPointDelta[1] * div;

		int newIndex = hpl::aleph::map::addEndpoint(ep);
		endpointIndexMap[i] = newIndex;
	}
	
	//add lines
	std::vector<line_data>* lineList = this->storedMapData.getLines();
	for(int i = 0; i < (int)lineList->size(); i ++){
		//データをコピーする
		line_data line;
		memcpy(&line, &lineList[i], sizeof(line_data));

		//線自体は位置情報を持たないため、ずらす作業はいらない

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

	//インデックス調整
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

#include "HPLCopyPasteManager.h"
#include "HPLError.h"
#include "HPLMapTool.h"

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

	this->storedMapData.set(sel);
	//位置設定
	storedDataDiffPointDelta[0] = COPY_AND_PASTE_DELTA_X;
	storedDataDiffPointDelta[1] = COPY_AND_PASTE_DELTA_Y;
}

/**
	保持している内容をペーストします
	@return ペーストに失敗した場合（何も保持していないとき）に偽
*/
bool hpl::aleph::HPLCopyPasteManager::paste(int div, hpl::aleph::map::HPLSelectData* sel)
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
		//memcpy(&ep, &endpointList->at(i), sizeof(endpoint_data));
		ep = endpointList->at(i);

		//位置をずらす
		ep.vertex.x += storedDataDiffPointDelta[0] * div;
		ep.vertex.y += storedDataDiffPointDelta[1] * div;

		int newIndex = hpl::aleph::map::addEndpoint(ep);
		endpointIndexMap[i] = newIndex;
	}
	
	//add polygons
	std::vector<polygon_data>* polygonList = this->storedMapData.getPolygons();
	for(int i = 0; i < (int)polygonList->size(); i ++){
		int newIndex = hpl::aleph::map::addPolygon(polygonList->at(i));
		polygonIndexMap[i] = newIndex;
	}

	//add lines
	std::vector<line_data>* lineList = this->storedMapData.getLines();
	std::vector<side_data>* sideList = this->storedMapData.getSides();
	for(int i = 0; i < (int)lineList->size(); i ++){
		//データをコピーする
		line_data line;
		//memcpy(&line, &lineList->at(i), sizeof(line_data));
		line = lineList->at(i);

		//線自体は位置情報を持たないため、ずらす作業はいらない

		
		int newIndex = hpl::aleph::map::addLine(line);
		lineIndexMap[i] = newIndex;
		if(line.clockwise_polygon_side_index != NONE &&
			line.clockwise_polygon_side_index < (int)this->storedMapData.getSides()->size())
		{
			//Sideの追加
			int oldSideIndex = line.clockwise_polygon_side_index;
			int newSideIndex = hpl::aleph::map::addSide(sideList->at(oldSideIndex), true);
			sideIndexMap[oldSideIndex] = newSideIndex;
		}else{
			line.clockwise_polygon_side_index = NONE;
		}
		if(line.counterclockwise_polygon_side_index != NONE &&
			line.counterclockwise_polygon_side_index < (int)this->storedMapData.getSides()->size())
		{
			//逆
			int oldSideIndex = line.counterclockwise_polygon_side_index;
			int newSideIndex = hpl::aleph::map::addSide(sideList->at(oldSideIndex), false);
			sideIndexMap[oldSideIndex] = newSideIndex;
		}else{
			line.counterclockwise_polygon_side_index = NONE;
		}
		
	}
	
	
	/*
	//add sides
	for(int i = 0; i < (int)sideList->size(); i ++){
		int newIndex = hpl::aleph::map::addSide(sideList->at(i));
		sideIndexMap[i] = newIndex;
	}*/
	
	//add objects
	std::vector<map_object>* objectList = this->storedMapData.getObjects();
	for(int i = 0; i < (int)objectList->size(); i ++){
		map_object obj;
		//memcpy(&obj, &objectList->at(i), sizeof(map_object));
		obj = objectList->at(i);
		obj.location.x += storedDataDiffPointDelta[0] * div;
		obj.location.y += storedDataDiffPointDelta[1] * div;
		int newIndex = hpl::aleph::map::addMapSavedObject(obj);
		objectIndexMap[i] = newIndex;
	}

	//インデックス調整
	hpl::aleph::map::changeIndexMapping(
		EndpointList,
		LineList,
		PolygonList,
		SideList,
		SavedObjectList,
		(int)(EndpointList.size() - endpointList->size()), (int)(EndpointList.size()),
		(int)(LineList.size() - lineList->size()), (int)(LineList.size()),
		(int)(PolygonList.size() - polygonList->size()), (int)(PolygonList.size()),
		(int)(SideList.size() - sideList->size()), (int)(SideList.size()),
		(int)(SavedObjectList.size() - objectList->size()), (int)(SavedObjectList.size()),
		endpointIndexMap,
		lineIndexMap,
		polygonIndexMap,
		sideIndexMap,
		objectIndexMap);

	//選択状態にする
	sel->clear();
	for(int i = (int)(EndpointList.size() - endpointList->size());
			i < (int)EndpointList.size(); i ++)
	{
		int offset[2] = {0,0};
		sel->addSelPoint(i, offset);
	}
	for(int i = (int)LineList.size() - (int)lineList->size(); i < (int)LineList.size(); i ++){
		int offset[2][2] = {{0,0},{0,0}};
		sel->addSelLine(i, offset);
	}
	for(int i = (int)PolygonList.size() - (int)polygonList->size(); i < (int)PolygonList.size(); i ++){
		int offset[MAXIMUM_VERTICES_PER_POLYGON][2] = {{0}};
		polygon_data* poly = get_polygon_data(i);
		sel->addSelPolygon(i, offset, poly->vertex_count);
	}
	for(int i = (int)SavedObjectList.size() - (int)objectList->size(); i < (int)SavedObjectList.size(); i ++){
		int offset[2] = {0};
		sel->addSelObject(i, offset);
	}

	storedDataDiffPointDelta[0] += COPY_AND_PASTE_DELTA_X;
	storedDataDiffPointDelta[1] += COPY_AND_PASTE_DELTA_Y;
	return true;
}

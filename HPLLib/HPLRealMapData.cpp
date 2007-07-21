#include "HPLRealMapData.h"

#include <memory.h>

hpl::aleph::map::HPLRealMapData::HPLRealMapData()
{
}
hpl::aleph::map::HPLRealMapData::~HPLRealMapData()
{
    removeAll();
}

//コピー対象のマップデータ(選択部分)
void hpl::aleph::map::HPLRealMapData::set(hpl::aleph::map::HPLSelectData* copyTargetData)
{
    removeAll();
    //objects
    for(int i = 0; i < (int)copyTargetData->getSelObjects()->size(); i ++){
        int index = copyTargetData->getSelObjects()->at(i).index;
        addObject(index);
    }


    //points
    for(int i = 0; i < (int)copyTargetData->getSelPoints()->size(); i ++){
        int index = copyTargetData->getSelPoints()->at(i).index;
		addEndpoint(index);
    }
    //lines
    for(int i = 0; i < (int)copyTargetData->getSelLines()->size(); i ++){
        addLine(copyTargetData->getSelLines()->at(i).index);
    }
    //polygons
    for(int i = 0; i < (int)copyTargetData->getSelPolygons()->size(); i ++){
        int index = copyTargetData->getSelPolygons()->at(i).index;
		addPolygon(index);
    }
/*	線と同時に追加される
	//sides
    for(int i = 0; i < (int)copyTargetData->getSelSides()->size(); i ++){
        int index = copyTargetData->getSelSides()->at(i).index;
//		addSide(index);
    }
	*/
}

void hpl::aleph::map::HPLRealMapData::addObject(int index){
    map_object* org = &SavedObjectList[index];
    map_object copy;
    memcpy(&copy, org, sizeof(map_object));
    this->realObjects[index] = copy;
}
void hpl::aleph::map::HPLRealMapData::addPoint(int index){
    endpoint_data* org = get_endpoint_data(index);
    endpoint_data copy;
    memcpy(&copy, org, sizeof(endpoint_data));
    this->realPoints[index] = copy;
}
void hpl::aleph::map::HPLRealMapData::addLine(int index){
    line_data* org = get_line_data(index);
    line_data copy;
    memcpy(&copy, org, sizeof(line_data));
    this->realLines[index] = copy;

    //線に所属する点を追加する
    for(int i = 0; i < 2; i ++){
		int epointIndex = copy.endpoint_indexes[i];
		//既に追加していないかチェック
		if(this->containsPoint(epointIndex){
			continue;
		}
        addPoint(epointIndex);
    }
}
void hpl::aleph::map::HPLRealMapData::addPolygon(int index){
    polygon_data* org = get_polygon_data(index);
    polygon_data copy;
    memcpy(&copy, org, sizeof(polygon_data));
    this->realPolygons[index] = copy;

    //lines
    int vertexCount = copy.vertex_count;
    for(int i = 0; i < vertexCount - 1; i ++){
		int lineIndex = copy.line_indexes[i];
		//既に追加した線はスキップ
		if(this->containsLine(lineIndex)){
			continue;
		}
        addLine(lineIndex);
    }
}
void hpl::aleph::map::HPLRealMapData::addSide(int index){
    side_data* org = get_side_data(index);
    side_data copy;
    memcpy(&copy, org, sizeof(side_data));
    this->realSides[index] = copy;
}
//所持するデータを消します
void hpl::aleph::map::HPLRealMapData::removeAll()
{
    this->realObjects.clear();
    this->realPoints.clear();
    this->realLines.clear();
    this->realPolygons.clear();
    this->realSides.clear();
}
std::map<int, map_object>* hpl::aleph::map::HPLRealMapData::getObjects()
{
    return &this->realObjects;
}
std::map<int, endpoint_data>* hpl::aleph::map::HPLRealMapData::getPoints()
{
    return &this->realPoints;
}
std::map<int, line_data>* hpl::aleph::map::HPLRealMapData::getLines()
{
    return &this->realLines;
}
std::map<int, polygon_data>* hpl::aleph::map::HPLRealMapData::getPolygons()
{
    return &this->realPolygons;
}
std::map<int, side_data>* hpl::aleph::map::HPLRealMapData::getSides()
{
    return &this->realSides;
}

//データが存在するか確かめます
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

bool hpl::aleph::map::HPLRealMapData::containsPoint(int index)
{
	//既に追加していないかチェック
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
	//既に追加していないかチェック
	for(std::map<int, line_data>::iterator it = this->getLines()->begin();
		it != this->getLines()->end(); it ++)
	{
		if(it->first == index){
			return true;
		}
	}
	return false;
}

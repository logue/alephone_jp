#include "HPLMapTool.h"
#include "HPLMath.h"
#include <limits.h>
#include "HPLQuickSort.h"
#include <fstream>
#include "HPLError.h"
#include "HPLStringModifier.h"

/**
    マップアイテム（点・線・Side・ポリゴン・オブジェクト）
    を削除します
    手法としては、
    １：線の端点など、参照元が削除対象となっている場合、
        ・参照をNONEにする
        ・自分自身も削除対象とする
    ２：削除対象を削除していく
        ・削除番号の列を作る
        ・後ろ側から消していく

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
        hpl::error::halt("数があっていない");
        return false;
    }



    /////////////////
    //実際に削除する
    std::map<int, int> indexMapPoints;
    std::map<int, int> indexMapLines;
    std::map<int, int> indexMapSides;
    std::map<int, int> indexMapPolygons;
    std::map<int, int> indexMapObjects;
    //対応表を作る
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

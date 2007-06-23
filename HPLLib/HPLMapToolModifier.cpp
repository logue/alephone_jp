#include "HPLMapTool.h"
#include "HPLMath.h"
#include <limits.h>
#include "HPLQuickSort.h"
#include <fstream>
#include "HPLError.h"
#include "HPLStringModifier.h"
#include "map.h"

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
        delPoints.size() != dynamic_world->endpoint_count ||
        delLines.size() != LineList.size() ||
        delLines.size() != dynamic_world->line_count ||
        delSides.size() != SideList.size() ||
        delSides.size() != dynamic_world->side_count ||
        delPolygons.size() != PolygonList.size() ||
        delPolygons.size() != dynamic_world->polygon_count ||
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

    //インデックスを付け直す
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
}

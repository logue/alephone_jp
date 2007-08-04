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
//	プロトタイプ
//	prototypes
static void changeSidePolygonIndexOfLine(line_data* line,
							   std::map<int, int>& polygonIndexMap,
							   std::map<int, int>& sideIndexMap,
							   bool isClockwise);
static void changeChildIndex(int16 indexes[], int num,
								std::map<int, int>& indexMap);

/**
	線に対して、それが関連するSideとPolygonのインデックスを調整します。
	対象がインデックス変換マップに存在しなければNONEが入れられます
	@param isClockwise 右・時計回りの話なら真
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

		//ポリゴンをインデックス変換マップに登録しているか
		std::map<int, int>::iterator it = polygonIndexMap.find(polyIndex);

		if(it != polygonIndexMap.end()){

			//ポリゴンが存在する
			if(sideIndex >= 0 &&
				sideIndexMap.find(sideIndex) != sideIndexMap.end())
			{
				//Sideも存在する
				wxASSERT(sideIndexMap[sideIndex] >= 0);
				sideIndex = sideIndexMap[sideIndex];
			}else{
				//Sideが存在しない（まあ許容の範囲内）
				sideIndex = NONE;
			}
			polyIndex = it->second;
			wxASSERT(polyIndex >= 0);
		}else{
			//指定されていない
			polyIndex = NONE;
			sideIndex = NONE;
		}
	}else if(polyIndex == NONE){
		//ポリゴンが存在しない
		sideIndex = NONE;
	}else{
		//不定値
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
	//所属してくる点データ
	for(int j = 0; j < num; j ++){
		int index = indexes[j];
		wxASSERT(index >= 0);
		//更新
		wxASSERT(indexMap.find(index) != indexMap.end());
		indexes[j] = indexMap[index];
		wxASSERT(indexMap[index] >= 0);
	}
}
/**
	マップアイテムのインデックスを指定したテーブルに従って変更します。
	<en> change map items' indexes with prepared index map
	@param *List 元のマップインデックスで構成されたオブジェクトデータ
	@param *IndexMap <originalIndex, newIndex>

	対応は
	???IndexStart		:	a
	???IndexStart + 1	:	b
	???IndexStart + 2	:	c
	となっており、originalIndexはendpointListなど、
	ベクタの要素のインデックスに対応しており、それぞれ
	[0]	:	???IndexStart		:	a
	[1]	:	???IndexStart + 1	:	b
	となる
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
		整合性チェック
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

		//点が所属するポリゴンを取得します
		//get polygon endpoint belongs to 
		std::map<int, int>::iterator it = 
			polygonIndexMap.find(ep->supporting_polygon_index);
		if(it == polygonIndexMap.end()){
			//見つからない

			//点を有するポリゴンを探す
			//int orgIndex = getKeyByValue(endpointIndexMap, i);
			//wxASSERT(orgIndex >= 0);

			//hpl::aleph::map::getPolygonIndexesIncludePoint(orgIndex);
			//この関数はグローバル変数であるPolygonListからさがすので、
			//汎用的ではない

			//代わりにpolygonListから探す

			bool found = false;
			for(int j = polygonIndexStart; j < polygonIndexEnd; j ++){
				polygon_data* poly = &polygonList[j];
				for(int k = 0; k < poly->vertex_count; k ++){
					if(poly->endpoint_indexes[k] == i){
						//存在した
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
				//追加するポリゴンはストックされていない
				//NONEとする
				ep->supporting_polygon_index = NONE;
			}

		}else{	//	it != polygonIndexMap.end()
			//存在する
			//iteratorはpairであり、そのメンバであるsecondは変換後のインデックス値
			//よってこれを代入すればよい
			ep->supporting_polygon_index = it->second;
			wxASSERT(it->second >= 0);
		}
		wxASSERT(ep->supporting_polygon_index >= -1);
    }

    //lines
    for(int i = lineIndexStart; i < lineIndexEnd; i ++){
		line_data* line = &lineList[i];
		//所属してくる点データ
		changeChildIndex(line->endpoint_indexes, 2, endpointIndexMap);

		//所属してくるサイドデータ
		//所属するポリゴンデータ
		bool isClockwise = true;
		changeSidePolygonIndexOfLine(line, polygonIndexMap, sideIndexMap, isClockwise);
		isClockwise = false;
		changeSidePolygonIndexOfLine(line, polygonIndexMap, sideIndexMap, isClockwise);
    }

    //polygons
    for(int i = polygonIndexStart; i < polygonIndexEnd; i ++){
		polygon_data* poly = &polygonList[i];

		int n = poly->vertex_count;

		//所属する点インデックス
		//<en> modify endpoint indexes
		changeChildIndex(poly->endpoint_indexes, n, endpointIndexMap);

		//所属する線インデックス
		//<en> modify line indexes
		changeChildIndex(poly->line_indexes, n, lineIndexMap);

		//所属するSideインデックス
		//NONEがあるので
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
		//所属する線
		int lineIndex = side->line_index;
		wxASSERT(lineIndex >= 0 && lineIndexMap.find(lineIndex) != lineIndexMap.end());
		side->line_index = lineIndexMap[lineIndex];
		wxASSERT(side->line_index >= 0);

		//所属するポリゴン
		int polyIndex = side->polygon_index;
		wxASSERT(polyIndex >= 0 && polygonIndexMap.find(polyIndex) != polygonIndexMap.end());
		side->polygon_index = polygonIndexMap[polyIndex];
		wxASSERT(side->polygon_index >= 0);
	}

	//objects
    for(int i = objectIndexStart; i < objectIndexEnd; i ++){
		map_object* obj = &objectList[i];
		wxASSERT(obj->polygon_index >= -1);
		//所属するポリゴン
		if(obj->polygon_index >= 0 && 
			polygonIndexMap.find(obj->polygon_index) != polygonIndexMap.end()){
			obj->polygon_index = polygonIndexMap[obj->polygon_index];
			wxASSERT(obj->polygon_index >= 0);
		}else{
			obj->polygon_index = NONE;
		}
		//結局はペースト時・移動時にそのとき乗っかっているポリゴンに所属することになるのでたいした意味はない
    }
}

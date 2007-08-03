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

//角度の最大
const double DEG_ROUND = 360.0;

//////////////////////////////////////////////////////
/////// add delete and modify
/**
	点情報を追加します
	@param ep 追加する点データ（値渡しなのでコピーされます）
	@return 追加された点のインデックス値
*/
int hpl::aleph::map::addEndpoint(endpoint_data ep)
{
	EndpointList.push_back(ep);
	dynamic_world->endpoint_count = (int16)EndpointList.size();
	int index = dynamic_world->endpoint_count - 1;
	return index;
}
int hpl::aleph::map::addLine(line_data line)
{
	LineList.push_back(line);
	dynamic_world->line_count = (int16)LineList.size();
	int index = dynamic_world->line_count - 1;
	return index;
}
int hpl::aleph::map::addSide(side_data side, bool isClockwise)
{
	SideList.push_back(side);
	dynamic_world->side_count = (int16)SideList.size();
	int index = dynamic_world->side_count - 1;
	return index;
}
int hpl::aleph::map::addPolygon(polygon_data polygon)
{
	PolygonList.push_back(polygon);
	dynamic_world->polygon_count = (int16)PolygonList.size();
	int index = dynamic_world->polygon_count - 1;

	if(!hpl::aleph::map::isValidIndex(index, PolygonList.size())){
		return NONE;
	}
	polygon_data* poly = get_polygon_data(index);

    //以下の依存する項目を修正する
    //・点（adjacent）
    //・線（owner）
    //・Side
    //TODO
    for(int i = 0; i < poly->vertex_count; i ++){
        int next = i + 1;
        if(next >= poly->vertex_count){
            next = 0;
        }
        endpoint_data* ep1 = get_endpoint_data(poly->endpoint_indexes[i]);
#ifdef __WXDEBUG__
        wxASSERT(ep1);
#else
        if(!ep1)continue;
#endif
        //関連ポリゴンの指定が無ければ指定
        if(!hpl::aleph::map::isValidIndex(ep1->supporting_polygon_index,
			PolygonList.size()))
		{
            ep1->supporting_polygon_index = index;
        }

        endpoint_data* ep2 = get_endpoint_data(poly->endpoint_indexes[next]);
#ifdef __WXDEBUG__
        wxASSERT(ep2);
#else
        if(!ep2)continue;
#endif

/*        //線
        line_data* line = get_line_data(poly->line_indexes[i]);
#ifdef __WXDEBUG__
        wxASSERT(line);
#else
        if(!line)continue;
#endif
        if(line->endpoint_indexes[0] == poly->endpoint_indexes[i]){
            //順向き→clockwise
            line->clockwise_polygon_owner = index;
            side_data* side = get_side_data(line->clockwise_polygon_side_index);
            if(side)
                side->polygon_index = index;
        }else if(line->endpoint_indexes[0] == poly->endpoint_indexes[next]){
            //逆向き→counterclockwise
            line->counterclockwise_polygon_owner = index;
            side_data* side = get_side_data(line->counterclockwise_polygon_side_index);
            if(side)
                side->polygon_index = index;
        }else{
#ifdef __WXDEBUG__
            wxASSERT(false);
#else
            continue;
//            hpl::error::halt("invalid polygon frame");
#endif
        }*/
    }
	return index;
}
int hpl::aleph::map::addMapSavedObject(map_object object)
{
	SavedObjectList.push_back(object);
	//TODO
	//プレースメント情報に付加

	//追加したとき、その点が乗るポリゴンにオブジェクトのポリゴン番号を設定する
	//	外部でやってね

	//TODO どれを集計すれば良いのか？
//	dynamic_world->object_count ++;// SavedObjectList.size();
	dynamic_world->initial_objects_count = (int16)SavedObjectList.size();
	int index = dynamic_world->initial_objects_count - 1;
	
	
    map_object* obj = &SavedObjectList[index];

	//placement 情報をチェック。
	object_frequency_definition* placement =
		hpl::aleph::map::getPlacementData(object.type, object.index);
	hpl::aleph::map::updateObjectInitialPlacement(obj->type, obj->index);

    //依存する項目を修正する
    //・ポリゴン
	hpl::aleph::map::isValidIndex(obj->polygon_index, PolygonList.size());
	/*
	if(!hpl::aleph::map::isValidIndex(obj->polygon_index)){
		obj->polygon_index = NULL;
	}else{
	    polygon_data* poly = get_polygon_data(obj->polygon_index);
	}
	*/
	return index;
}
int hpl::aleph::map::addAnnotation(map_annotation annotation)
{
	MapAnnotationList.push_back(annotation);
/*	dynamic_world-> = MapAnnotationList.size();
	int index = dynamic_world->annotation_count - 1;*/
	int index = (int16)MapAnnotationList.size() - 1;
	return index;
}

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
									 std::vector<bool>& delPolygons,
                                     std::vector<bool>& delSides,
								    std::vector<bool>& delObjects)
{
    if(delPoints.size() < EndpointList.size() ||
        EndpointList.size() != dynamic_world->endpoint_count ||
        delLines.size() < LineList.size() ||
        LineList.size() != dynamic_world->line_count ||
        delSides.size() < SideList.size() ||
        SideList.size() != dynamic_world->side_count ||
        delPolygons.size() < PolygonList.size() ||
        PolygonList.size() != dynamic_world->polygon_count ||
        delObjects.size() < SavedObjectList.size())
    {
        hpl::error::caution("dismatch delP[%d],EndpointList.size()[%d],world.endpoint_count[%d]",
			delPoints.size(), EndpointList.size(), dynamic_world->endpoint_count);
        hpl::error::caution("dismatch delL[%d],LineList.size()[%d],world.line_count[%d]",
			delLines.size(), LineList.size(), dynamic_world->line_count);
        hpl::error::caution("dismatch delPoly[%d],PolygonList.size()[%d],world.polygon_count[%d]",
			delPolygons.size(), PolygonList.size(), dynamic_world->polygon_count);
        hpl::error::caution("dismatch delS[%d],SideList.size()[%d],world.side_count[%d]",
			delSides.size(), SideList.size(), dynamic_world->side_count);
        hpl::error::halt("dismatch delO[%d],SavedObjectList.size()[%d],world.initial[%d]",
			delObjects.size(), SavedObjectList.size(), dynamic_world->initial_objects_count);
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
    for(int i = 0; i < (int)EndpointList.size(); i ++){
        if(!delPoints[i]){   indexMapPoints[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)LineList.size(); i ++){
        if(!delLines[i]){   indexMapLines[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        if(!delPolygons[i]){   indexMapPolygons[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)SideList.size(); i ++){
        if(!delSides[i]){   indexMapSides[i] = counter;   counter ++;}
    }
    counter = 0;
    for(int i = 0; i < (int)SavedObjectList.size(); i ++){
        if(!delObjects[i]){   indexMapObjects[i] = counter;   counter ++;}
    }
	//TODO Platform
	
	//削除します
	for(int i = (int)EndpointList.size() - 1; i >= 0; i --){
		if(delPoints[i]){
			EndpointList.erase(EndpointList.begin() + i);
		}
	}
	for(int i = (int)LineList.size() - 1; i >= 0; i --){
		if(delLines[i]){
			LineList.erase(LineList.begin() + i);
		}
	}
	for(int i = (int)PolygonList.size() - 1; i >= 0; i --){
		if(delPolygons[i]){
			PolygonList.erase(PolygonList.begin() + i);
		}
	}
	for(int i = (int)SideList.size() - 1; i >= 0; i --){
		if(delSides[i]){
			SideList.erase(SideList.begin() + i);
		}
	}
	for(int i = (int)SavedObjectList.size() - 1; i >= 0; i --){
		if(delObjects[i]){
			SavedObjectList.erase(SavedObjectList.begin() + i);
		}
	}
	/*
	for(int i = (int)delPlatforms.size() - 1; i >= 0; i --){
		if(delPlatforms[i]){
			PlatformList.erase(PlatformList.begin() + i);
		}
	}*/
	
    //インデックスを付け直す
	hpl::aleph::map::changeIndexMapping(
		EndpointList,
		LineList,
		PolygonList,
		SideList,
		SavedObjectList,
		0, (int)EndpointList.size(),
		0, (int)LineList.size(),
		0, (int)PolygonList.size(),
		0, (int)SideList.size(),
		0, (int)SavedObjectList.size(),
		indexMapPoints, indexMapLines, indexMapPolygons, indexMapSides, indexMapObjects);
    return true;
}


/**
	マップアイテムのインデックスを指定したテーブルに従って変更します。
	<en> change map items' indexes with prepared index map
	@param *List 元のマップインデックスで構成されたオブジェクトデータ
	@param *IndexMap <originalIndex, newIndex>
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
	//points
    for(int i = endpointIndexStart; i < endpointIndexEnd; i ++){
#ifdef _WXDEBUG_
		wxASSERT(endpointIndexStart >= 0 && endpointIndexStart <= (int)endpointList.size() &&
			endpointIndexStart <= endpointIndexEnd && endpointIndexEnd <= (int)endpointList.size());
#endif
		endpoint_data* ep = &endpointList[i];
		//所属するポリゴンIndex
		std::map<int, int>::iterator it = polygonIndexMap.find(ep->supporting_polygon_index);
		if(it == polygonIndexMap.end()){
			//存在しない
			//点を有するポリゴンを探す
			int orgIndex = getKeyByValue(endpointIndexMap, i);
			wxASSERT(orgIndex >= 0);

			std::vector<int> belongPolygonIndexes = hpl::aleph::map::getPolygonIndexesIncludePoint(orgIndex);
			bool found = false;
			for(int j = 0; j < (int)belongPolygonIndexes.size(); j ++){
				int polyIndex = belongPolygonIndexes[j];
				//登録したポリゴンに含まれているかどうか検索します
				if(polygonIndexMap.find(polyIndex) == polygonIndexMap.end()){
					//含まれない
				}else{
					//中に含まれる
					//それを対象とする
					found = true;
					ep->supporting_polygon_index = belongPolygonIndexes[j];
					wxASSERT(ep->supporting_polygon_index >= 0);
					break;
				}
			}
			if(!found){
				//追加するポリゴンはストックされていない
				//NONEとする
				ep->supporting_polygon_index = NONE;
			}
		}else{
			//存在する
			ep->supporting_polygon_index = it->second;
			wxASSERT(it->second >= 0);
		}
    }

    //lines
    for(int i = lineIndexStart; i < lineIndexEnd; i ++){
		line_data* line = &lineList[i];
		//所属してくる点データ
		for(int j = 0; j < 2; j ++){
			int epIndex = line->endpoint_indexes[j];
			wxASSERT(epIndex >= 0);
			//更新
			line->endpoint_indexes[j] = endpointIndexMap[epIndex];
			wxASSERT(endpointIndexMap[epIndex] >= 0);
		}
		//所属してくるサイドデータ
		//所属するポリゴンデータ
		{
			int clockPoly = line->clockwise_polygon_owner;
			int clockSide = line->clockwise_polygon_side_index;
			if(clockPoly >= 0){
				//ポリゴンを登録しているか
				std::map<int, int>::iterator it = polygonIndexMap.find(clockPoly);
				if(it != polygonIndexMap.end()){
					//ポリゴンが存在する
					if(clockSide >= 0 &&
						sideIndexMap.find(clockSide) != sideIndexMap.end())
					{
						//Sideも存在する
						wxASSERT(sideIndexMap[clockSide] >= 0);
						clockSide = sideIndexMap[clockSide];
					}else{
						clockSide = NONE;
					}
					clockPoly = it->second;
				}else{
					clockPoly = NONE;
					clockSide = NONE;
				}
			}else{
				//ポリゴンが存在しない
				clockSide = NONE;
			}
			line->clockwise_polygon_side_index = clockSide;
			line->clockwise_polygon_owner = clockPoly;
		}

		{
			//counter clock side 
			int counterPoly = line->counterclockwise_polygon_owner;
			int counterSide = line->counterclockwise_polygon_side_index;
			if(counterPoly >= 0){
				//ポリゴンを登録しているか
				std::map<int, int>::iterator it = polygonIndexMap.find(counterPoly);
				if(it != polygonIndexMap.end()){
					if(counterSide >= 0 && sideIndexMap.find(counterSide) != sideIndexMap.end()){
						counterSide = sideIndexMap[counterSide];
					}else{
						counterSide = NONE;
					}
					counterPoly = it->second;
				}else{
					counterSide = NONE;
					counterPoly = NONE;
				}
			}else{
				counterSide = NONE;
			}
			line->counterclockwise_polygon_side_index = counterSide;
			line->counterclockwise_polygon_owner = counterPoly;
		}

    }

    //polygons
    for(int i = polygonIndexStart; i < polygonIndexEnd; i ++){
		polygon_data* poly = &polygonList[i];

		int n = poly->vertex_count;

		//所属する点インデックス
		//<en> modify endpoint indexes
		for(int i = 0; i < n; i ++){
			poly->endpoint_indexes[i] = endpointIndexMap[poly->endpoint_indexes[i]];
			wxASSERT(poly->endpoint_indexes[i] >= 0);
		}

		//所属する線インデックス
		//<en> modify line indexes
		for(int i = 0; i < n; i ++){
			poly->line_indexes[i] = endpointIndexMap[poly->line_indexes[i]];
			wxASSERT(poly->line_indexes[i] >= 0);
		}

		//所属するSideインデックス
		//<en> modify side indexes
		for(int i = 0; i < n; i ++){
			if(poly->side_indexes[i] == NONE){
			}else{
				poly->side_indexes[i] = endpointIndexMap[poly->side_indexes[i]];
				wxASSERT(poly->side_indexes[i] >= 0);
			}
		}

    }

	//sides 
	for(int i = sideIndexStart; i < sideIndexEnd; i ++){
		side_data* side = &sideList[i];
		//所属する線
		int lineIndex = side->line_index;
#ifdef _WXDEBUG_
		wxASSERT(lineIndex >= 0);
#endif
		side->line_index = lineIndexMap[lineIndex];
		wxASSERT(side->line_index >= 0);

		//所属するポリゴン
		int polyIndex = side->polygon_index;
#ifdef _WXDEBUG_
		wxASSERT(polyIndex >= 0);
#endif
		side->polygon_index = polygonIndexMap[polyIndex];
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


///////////////////////////////////////////////////////
///////////////////////////////////////////////////////
/// add
/**
    基本の線&点からつながる線のうち、サイズがもっとも小さくなるように
    点のリストを取得します。点の並びはポリゴン指定にそのまま使える物となっています。

    再帰的に呼び出します。
    @param pointIndexes これまでにつなげてきた点のリスト。この個数がMAXIMUM_VERTEX_PER_POLYGON
        を超えたら見つからなかったものとする
    @return ポリゴンが完結した場合真
*/
static bool getValidLines(int basePointIndex, int baseLineIndex,
                          std::vector<int> *pointIndexes,
                          hpl::aleph::HPLStockManager* smgr,
                          int rotRem, std::set<int>* doneList,
                          int zMin, int zMax,
                          world_point2d& wpoint)
{
    //最大の角度
    double maxDeg = 0;
    int maxLineIndex = NONE;

    line_data* baseLine = get_line_data(baseLineIndex);
    int startBasePointIndex = baseLine->endpoint_indexes[0];
    int endBasePointIndex =  baseLine->endpoint_indexes[1];
    if(startBasePointIndex == basePointIndex){
        //入れ替え
        hpl::math::exchange(&startBasePointIndex, &endBasePointIndex);
    }else if(endBasePointIndex == basePointIndex){
    }else{
#ifdef __WXDEBUG__
        wxASSERT(false);
#else
        return false;
#endif

    }

    int lastPointIndex = NONE;
    //ベースポイントに繋がる線を取り出す
    std::vector<int> conLines = hpl::aleph::map::getLineIndexesIncludePoint(basePointIndex);
    for(int k = 0; k < (int)conLines.size(); k ++){
        int conLineIndex = conLines[k];
        if(doneList->find(conLines[k]) != doneList->end()){
            //既に見つけ出したものは省く
            continue;
        }
        //delLinesは省く
        if(smgr->isDeleteLine(conLineIndex)){
            continue;
        }
        //ベースの線と一緒の場合も除外する
        if(baseLineIndex == conLineIndex){
            continue;
        }

        line_data* line = get_line_data(conLineIndex);
#ifdef __WXDEBUG__
        wxASSERT(line );
#else
        if(!line )continue;
#endif
        //高さチェック
        if(!hpl::aleph::map::isValidHeight(line->highest_adjacent_floor,
            line->lowest_adjacent_ceiling, zMin, zMax))
        {
            continue;
        }

        int ep0Index = line->endpoint_indexes[0];
        int ep1Index = line->endpoint_indexes[1];
        if(basePointIndex == ep0Index){
        }else if(basePointIndex == ep1Index){
            //入れ替え
            hpl::math::exchange(&ep0Index, &ep1Index);
        }else{
#ifdef __WXDEBUG__
            wxASSERT(false );
#else
            continue;
#endif
        }

        endpoint_data* ep0 = get_endpoint_data(ep0Index);
#ifdef __WXDEBUG__
        wxASSERT(ep0 );
#else
        if(!ep0 )continue;
#endif
        endpoint_data* ep1 = get_endpoint_data(ep1Index);
#ifdef __WXDEBUG__
        wxASSERT(ep1 );
#else
        if(!ep1 )continue;
#endif

        double l0x = ep0->vertex.x;
        double l0y = ep0->vertex.y;
        double l1x = ep1->vertex.x;
        double l1y = ep1->vertex.y;
        //線から指定点に対する角度を求める（左右の確認）
        int rot = hpl::math::getPointRotationTypeFromLine(
            wpoint.x, wpoint.y, l0x, l0y, l1x, l1y);
        //最初の線と違う（逆向き）に指定点が来ている場合は正しくないものとする。
        if(rotRem != rot){
            continue;
        }

        //前の線の始点→共有点→最後の点で角度を求める
        //前の線の始点
        endpoint_data* prevStartEp = get_endpoint_data(startBasePointIndex);
#ifdef __WXDEBUG__
        wxASSERT(prevStartEp );
#else
        if(!prevStartEp )continue;
#endif
        double deg = hpl::math::getTwoLinesDegree(prevStartEp->vertex.x,
            prevStartEp->vertex.y, l0x, l0y,
            l0x, l0y, l1x, l1y);
        //[0,360)に制限する
        deg = hpl::math::optimizeDegree(deg);
        if(deg > DEG_ROUND / 2.0){
            deg = DEG_ROUND - deg;
        }
        //角度が現在最大かどうか確認する
        if(deg > maxDeg){
            maxDeg = deg;
            //今までより大きい
            maxLineIndex = conLineIndex;
            //最後の点
            lastPointIndex = ep1Index;
        }
        //済み
        doneList->insert(conLineIndex);
    }

    if(maxLineIndex == NONE){
        //見つからなかった
        //よって戻っていく
        return false;
    }else{
        //見つかった
        //最後に追加する
        pointIndexes->push_back(lastPointIndex);

        //最後の点がpointIndexes[0]と同一（一周してきた）だったら
        //終わったとする
        if(lastPointIndex == pointIndexes->at(0)){
            //ポリゴンとして成立するセットを見つけ出せた
            return true;
        }else{
            //まだまだ
            if(pointIndexes->size() >= MAXIMUM_VERTICES_PER_POLYGON + 1){
                return false;
            }
            //もう最大数を超えている
            //次を探す
            baseLineIndex = maxLineIndex;
            basePointIndex = lastPointIndex;
            bool found = getValidLines(basePointIndex, baseLineIndex, pointIndexes,
                smgr, rotRem, doneList, zMin, zMax, wpoint);
            //結局見つかったかどうかは子供だけが知っている
            return found;
        }
    }
}

/**
    座標を取り囲むポリゴンのうち、ポリゴンとして成立しているものをさがします
    すでにポリゴンが存在している場合は無視します
    @param wpoint 探索基点。ここを囲むポリゴンを探す
    @return ポリゴンの実データ候補。これを元に生成すると良い。データはcreatePolygonで生成すべし
*/
std::vector<polygon_data> hpl::aleph::map::searchValidPolygon(world_point2d wpoint,
                                                              hpl::aleph::HPLStockManager* smgr,
                                                              int zMin, int zMax)
{
    std::vector<polygon_data> polyDatas;

    int max = (int)LineList.size();
    //線への垂線の距離順で整列する
    //全部の線への垂線を求める
    struct hpl::math::qsort::Pair<double>* pairs = new struct hpl::math::qsort::Pair<double>[max];
    for(int i = 0; i < max; i ++){
        line_data* line = get_line_data(i);
        assert(line);
        endpoint_data* epStart = get_endpoint_data(line->endpoint_indexes[0]);
        assert(epStart);
        endpoint_data* epEnd = get_endpoint_data(line->endpoint_indexes[1]);
        assert(epEnd);
        pairs[i].data = hpl::math::getPointDistanceFromLine(wpoint.x, wpoint.y, 
            epStart->vertex.x, epStart->vertex.y, epEnd->vertex.x, epEnd->vertex.y);
    }
    hpl::math::qsort::quickSort<double>(pairs, max);

    //既に調べたリスト(線のインデックス値を入れる)
    std::set<int> doneList;

    //近くにある線から見ていく
    for(int i = 0; i < max; i ++){
        //削除対象なら無視
        if(smgr->isDeleteLine(i)){
            continue;
        }
        //すでに調べた線なら無視
        if(doneList.find(i) != doneList.end()){
            continue;
        }
        int lineIndexBase = pairs[i].index;
        line_data* startLine = get_line_data(lineIndexBase);
#ifdef __WXDEBUG__
        wxASSERT(startLine );
#else
        if(!startLine )continue;
#endif
        //高さチェック
        if(!hpl::aleph::map::isValidHeight(startLine->highest_adjacent_floor,
            startLine->lowest_adjacent_ceiling, zMin, zMax))
        {
            continue;
        }

        int startPointIndex = startLine->endpoint_indexes[0];
		endpoint_data* epStart = get_endpoint_data(startPointIndex);
#ifdef __WXDEBUG__
        wxASSERT(epStart );
#else
        if(!epStart )continue;
#endif
        int endPointIndex = startLine->endpoint_indexes[1];
		endpoint_data* epEnd = get_endpoint_data(endPointIndex);
#ifdef __WXDEBUG__
        wxASSERT(epEnd );
#else
        if(!epEnd )continue;
#endif

        //線の左右どちらの側に点があるかをチェックします
		int rotRem = hpl::math::getPointRotationTypeFromLine(
			wpoint.x, wpoint.y, epStart->vertex.x, epStart->vertex.y,
			epEnd->vertex.x, epEnd->vertex.y);
        if(rotRem == hpl::math::RotationType::Clockwise &&
            startLine->counterclockwise_polygon_owner != NONE)
        {
            //右周りで、かつ線の右側（指定点のある領域）
            //にポリゴンが既にある場合スキップ
//            hpl::error::caution("already polygon exists");
            continue;
        }
        if(rotRem == hpl::math::RotationType::Counterclockwise &&
            startLine->clockwise_polygon_owner != NONE)
        {
//            hpl::error::caution("already polygon exists");
            continue;
        }
        //これ以降はすでに指定点の部分にポリゴンがないと仮定する

        //基点
		int nowBasePointIndex = endPointIndex;
        int prevLineIndex = lineIndexBase;
		//TODO
        //startLine->endpoint_indexes[1]からつながる線を調べる
        std::vector<int> pointIndexes;
        //最初の二つを代入しておく
        pointIndexes.push_back(startPointIndex);
        pointIndexes.push_back(endPointIndex);

        bool found = getValidLines(nowBasePointIndex, prevLineIndex,
            &pointIndexes, smgr, rotRem, &doneList,
            zMin, zMax, wpoint);
        if(found){
            //発見！
            //点インデックス（値渡し用）
            int indexes[MAXIMUM_VERTICES_PER_POLYGON];

            //点データ集計
            for(int l = 0; l < (int)pointIndexes.size() - 1; l ++){
                //
                indexes[l] = pointIndexes[l];
            }
            int vertexCount = (int)pointIndexes.size() - 1;
            //ポリゴン作成
            polygon_data poly;
            hpl::aleph::map::createPolygon(indexes, vertexCount, &poly);
            
            polyDatas.push_back(poly);

            //TODO 複数見つけ出すのか？
            //高さ順？何のことかね？
            //感覚的に近い線を取ればいいんじゃね？
            break;
        }
        doneList.insert(i);
    }
    
    //解放
    delete pairs;
    return polyDatas;
}


void hpl::aleph::map::addNewPolygon(world_distance points[][2], int n)
{
    world_point2d pt[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < n; i ++){
        pt[i].x = points[i][0];
        pt[i].y = points[i][1];
    }
    hpl::aleph::map::addNewPolygon(pt, n);
}
void hpl::aleph::map::addNewPolygon(world_point2d points[], int n)
{
    //endpointの作成
    int epIndexes[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < n; i ++){
        //endpointの生成
        endpoint_data ep;
        hpl::aleph::map::createPoint(points[i], &ep);
        int epIndex = hpl::aleph::map::addEndpoint(ep);
        epIndexes[i] = epIndex;
    }

    //lineの作成
    //int lineIndexes[MAXIMUM_VERTICES_PER_POLYGON];
    for(int i = 0; i < n; i ++){
        int next = i + 1;
        if(next >= n){
            next = 0;
        }
        line_data line;
        hpl::aleph::map::createLine(epIndexes[i], epIndexes[next], &line);
        int lineIndex = hpl::aleph::map::addLine(line);
        //lineIndexes[i] = lineIndex;
    }
    polygon_data poly;
    hpl::aleph::map::createPolygon(epIndexes, n, &poly);
    hpl::aleph::map::addPolygon(poly);
}


#include "HPLStockManager.h"
#include "HPLMapTool.h"

#include "map.h"

hpl::aleph::HPLStockManager::HPLStockManager()
{
}
hpl::aleph::HPLStockManager::~HPLStockManager()
{
}

//ポリゴンが正しいかどうかを検査します(高速版)
bool hpl::aleph::HPLStockManager::isPolygonValidityStored(int polyIndex)
{
	if(polyIndex < 0){
		return false;
	}else if(polyIndex >= (int)this->polygonValidity.size()){
		//存在しないもの
		//更新
		updatePolygonValidityStored();
		if(polyIndex >= (int)this->polygonValidity.size()){
			//それでもやっぱりない→無視
			return false;
		}
	}

	return this->polygonValidity[polyIndex];
}

//ポリゴン整合性情報を更新します
void hpl::aleph::HPLStockManager::updatePolygonValidityStored()
{
	this->polygonValidity.clear();
	for(int i = 0; i < (int)PolygonList.size(); i ++){
        bool isValid = hpl::aleph::map::isValidPolygon(i);
		this->polygonValidity.push_back(isValid);
	}

    //ついでに高さ順をソートする
    //this->polygonDrawOrderByHeight.clear();
}

/**
    削除情報を更新します。
    具体的にはdynamic_worldの値に合わせて要素数を増加させます
    増加分は削除対象ではないのですべてfalseです。
    次に、実際のデータを調べて関連性があるものをさらに削除します。
    -endpoint_data
        [delete point]
        lines depend this       -> delete line
        polygon depends this    -> delete polygon (but no need to do, because deleted line will delete polygon)
                                    <jp>依存している線を消すときにポリゴンを消してくれるので無視します
        [no delete]
        polygon_index           -> set NONE when polygon is to be deleted

    -line_data
        [delete line]
        endpoints depend this   -> none necessity to do
                                    <jp>点は残ります。
        polygon depends this    -> delete
        sides depend this       -> delete

        [no delete]
        *_polygon_owner         -> set NONE when polygon is to be deleted
        *_polygon_side_owner    -> set NONE when side is to be deleted

    -polygon_data
        [delete polygon]
        points depend this      -> nope
                                    <jp>点は残るんよ
        lines depend this       -> nope
        sides depend this       -> delete side
        objects depend this     -> delete them

        [no delete]
        endpoint_indexes, line_indexes  -> no to do
        side_indexes            -> set NONE when sides are to be deleted
        first_object_index      -> set NONE when no objects are on this

        TODO lineを全てsolidにする

    -side_data
        [delete side]
        nope

        [no delete]
        line_index              -> nope
                                    <jp>線が消えていればSideも消されるので何もしなくてよい
        polygon_index           -> nope

    -map_object
        [delete object]
        nope

        [no delete]
        polygon_index           -> nope

*/
void hpl::aleph::HPLStockManager::updateDeletes()
{
    //points
    for(int i = delPoints.size(); i < dynamic_world->endpoint_count; i ++){
        delPoints.push_back(false);
    }
    for(int i = delLines.size(); i < dynamic_world->line_count; i ++){
        delLines.push_back(false);
    }
    for(int i = delSides.size(); i < dynamic_world->side_count; i ++){
        delSides.push_back(false);
    }
    for(int i = delPolygons.size(); i < dynamic_world->polygon_count; i ++){
        delPolygons.push_back(false);
    }
    for(int i = delObjects.size(); i < SavedObjectList.size(); i ++){
        delObjects.push_back(false);
    }

    //点関連の削除対象整理 <en> endpoints
    for(int i = 0; i < (int)delPoints.size(); i ++){
        if(delPoints[i]){
            //削除対象
            //所有している線も削除する (線と強依存関係 strong depenence -> lines )
            std::vector<int> lineIndexes = hpl::aleph::map::getLineIndexesIncludePoint(i);
            for(int j = 0; j < (int)lineIndexes.size(); j ++){
                delLines[lineIndexes[i]] = true;
            }
            //ポリゴンも強依存関係だが、線から消えていくので放置
        }else{
            //残る
            endpoint_data* ep = get_endpoint_data(i);
            if(ep->supporting_polygon_index != NONE){
                assert(get_polygon_data(ep->supporting_polygon_index));
                if(delPolygons[ep->supporting_polygon_index]){
                    //関連ポリゴンが消されるならば対応を切っておく
                    ep->supporting_polygon_index = NONE;
                }
            }
        }
    }

    //線 <en> lines
    for(int i = 0; i < (int)delLines.size(); i ++){
        line_data* line = get_line_data(i);
        assert(line);
        if(delLines[i]){
            //関連するポリゴンを削除する
            if(line->clockwise_polygon_owner != NONE){
                assert(get_polygon_data(line->clockwise_polygon_owner));
                delPolygons[line->clockwise_polygon_owner] = true;
            }
            if(line->counterclockwise_polygon_owner != NONE){
                assert(get_polygon_data(line->counterclockwise_polygon_owner));
                delPolygons[line->counterclockwise_polygon_owner] = true;
            }
            //線のSideを消す
            if(line->clockwise_polygon_side_index != NONE){
                assert(get_side_data(line->clockwise_polygon_side_index));
                delSides[line->clockwise_polygon_side_index] = true;
            }
            if(line->counterclockwise_polygon_side_index != NONE){
                assert(get_side_data(line->counterclockwise_polygon_side_index));
                delSides[line->counterclockwise_polygon_side_index] = true;
            }
        }else{
            //残る
            //点が消えていたら残っているわけがないので考慮しなくてよい

            //ポリゴンが消えていたら関連を切る
            if(line->clockwise_polygon_owner != NONE){
                assert(get_polygon_data(line->clockwise_polygon_owner));
                if(delPolygons.at(line->clockwise_polygon_owner)){
                    line->clockwise_polygon_owner = NONE;
                }
            }
            if(line->counterclockwise_polygon_owner != NONE){
                assert(get_polygon_data(line->counterclockwise_polygon_owner));
                if(delPolygons[line->counterclockwise_polygon_owner]){
                    line->counterclockwise_polygon_owner = NONE;
                }
            }

            //Sideが消えていたら関連を切る
            if(line->clockwise_polygon_side_index != NONE){
                assert(get_side_data(line->clockwise_polygon_side_index));
                if(delSides.at(line->clockwise_polygon_side_index)){
                    line->clockwise_polygon_side_index = NONE;
                }
            }
            if(line->counterclockwise_polygon_side_index != NONE){
                assert(get_side_data(line->counterclockwise_polygon_side_index));
                if(delSides[line->counterclockwise_polygon_side_index]){
                    line->counterclockwise_polygon_side_index = NONE;
                }
            }
        }
    }

    //ポリゴン
    for(int i = 0; i < (int)delPolygons.size(); i ++){
        polygon_data* poly = get_polygon_data(i);
        int n = poly->vertex_count;
        if(delPolygons[i]){
            //削除対象
            //関連するsideも消す
            for(int j = 0; j < n; j ++){
                if(poly->side_indexes[j] != NONE){
                    assert(get_side_data(poly->side_indexes[j]));
                    delSides[poly->side_indexes[j]] = true;
                }
            }

            //オブジェクトも消す
            for(int j = 0; j < (int)SavedObjectList.size(); j ++){
                map_object* obj = &SavedObjectList[j];
                assert(obj);
                if(obj->polygon_index == i){
                    delObjects[j] = true;
                }
            }
        }else{
            //残る
            for(int j = 0; j < n; j ++){
                if(poly->side_indexes[j] != NONE){
                    assert(get_side_data(poly->side_indexes[j]));
                    if(delSides[poly->side_indexes[j]]){
                        poly->side_indexes[j] = NONE;
                    }
                }
            }

            //乗っているオブジェクトが一つもない場合はfirst_objectをNONEにする
            if(delObjects[poly->first_object]){
                int firstObjIndex = NONE;
                for(int j = 0; j < (int)SavedObjectList.size(); j ++){
                    if(!delObjects[j]){
                        map_object* obj = &SavedObjectList[j];
                        assert(obj);
                        if(obj->polygon_index == i){
                            firstObjIndex = j;
                            break;
                        }
                    }
                }
                poly->first_object = firstObjIndex;
            }
        }
    }

    //Side
    for(int i = 0; i < (int)delSides.size(); i ++){
        side_data* side = get_side_data(i);
        if(delSides[i]){
            //消す
        }else{
            //消さない
        }
    }

    //objects
    for(int i = 0; i < (int)delObjects.size(); i ++){
        if(delObjects[i]){
            //消さない
        }else{
            //消さない
        }
    }
}

/**
    削除情報を初期化
    実際にはclearした後にupdateDeletes()を呼んでるだけ
*/
void hpl::aleph::HPLStockManager::resetDeletes()
{
    delPoints.clear();
    delLines.clear();
    delSides.clear();
    delPolygons.clear();
    delObjects.clear();

    this->updateDeletes();
}

bool hpl::aleph::HPLStockManager::deletePoint(int index)
{
    assert(get_endpoint_data(index));
    this->delPoints[index] = true;
    return true;
}
bool hpl::aleph::HPLStockManager::deleteLine(int index)
{
    assert(get_line_data(index));
    this->delLines[index] = true;
    return true;
}
bool hpl::aleph::HPLStockManager::deletePolygon(int index)
{
    assert(get_polygon_data(index));
    this->delPolygons[index] = true;
    return true;
}
bool hpl::aleph::HPLStockManager::deleteSide(int index)
{
    assert(get_side_data(index));
    this->delSides[index] = true;
    return true;
}
bool hpl::aleph::HPLStockManager::deleteObject(int index)
{
    assert(index >= 0 && index < SavedObjectList.size());
    this->delObjects[index] = true;
    return true;
}

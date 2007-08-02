#include "HPLStockManager.h"
#include "HPLMapTool.h"

#include "map.h"
#include "platforms.h"

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
    サイズを実際のものに合わせます
*/
void hpl::aleph::HPLStockManager::resizeDeletes()
{
    //points
    for(int i = (int)delPoints.size(); i < dynamic_world->endpoint_count; i ++){
        delPoints.push_back(false);
    }
    for(int i = (int)delLines.size(); i < dynamic_world->line_count; i ++){
        delLines.push_back(false);
    }
    for(int i = (int)delSides.size(); i < dynamic_world->side_count; i ++){
        delSides.push_back(false);
    }
    for(int i = (int)delPolygons.size(); i < dynamic_world->polygon_count; i ++){
        delPolygons.push_back(false);
    }
    for(int i = (int)delObjects.size(); i < (int)SavedObjectList.size(); i ++){
        delObjects.push_back(false);
    }
    for(int i = (int)delPlatforms.size(); i < (int)PlatformList.size(); i ++){
        delPlatforms.push_back(false);
    }
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
    this->resizeDeletes();

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
            if(poly->first_object != NONE){
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

	//platform
	for(int i = 0; i < (int)delPlatforms.size(); i ++){
		platform_data* platform = &PlatformList[i];
		int polyIndex = platform->polygon_index;
		if(polyIndex == NONE || delPolygons[polyIndex]){
			delPlatforms[i] = true;
		}else{
			if(delPlatforms[i]){
				//このプラットフォームは存在しない
			}else{
				//何もしない
			}
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
#ifdef _WXDEBUG_
    wxASSERT(get_endpoint_data(index));
#endif
    this->delPoints[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deleteLine(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(get_line_data(index));
#endif
    this->delLines[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deletePolygon(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(get_polygon_data(index));
#endif
    this->delPolygons[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deleteSide(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(get_side_data(index));
#endif
    this->delSides[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deleteObject(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(index >= 0 && index < (int)SavedObjectList.size());
#endif
    this->delObjects[index] = true;
    //updateDeletes();
    return true;
}
bool hpl::aleph::HPLStockManager::deletePlatform(int index)
{
#ifdef _WXDEBUG_
    wxASSERT(index >= 0 && index < (int)PlatformList.size());
#endif
    this->delPlatforms[index] = true;
    //updateDeletes();
    return true;
}

/**
	選択情報を更新
*/
void hpl::aleph::HPLStockManager::updateSelects(hpl::aleph::map::HPLSelectData& sel)
{
	//初期化
	this->selPoints.clear();
	this->selPoints.resize(EndpointList.size());
	this->selLines.clear();
	this->selLines.resize(LineList.size());
	this->selPolygons.clear();
	this->selPolygons.resize(PolygonList.size());
	this->selObjects.clear();
	this->selObjects.resize(SavedObjectList.size());
	this->selSides.clear();
	this->selSides.resize(SideList.size());

	//points
	for(int i = 0; i < (int)EndpointList.size(); i ++){
		this->selPoints[i] = sel.containsPoint(i);
	}

	//lines
	for(int i = 0; i < (int)LineList.size(); i ++){
		this->selLines[i] = sel.containsLine(i);
	}

	//polygons
	for(int i = 0; i < (int)PolygonList.size(); i ++){
		this->selPolygons[i] = sel.containsPolygon(i);
	}

	//objects
	for(int i = 0; i < (int)SavedObjectList.size(); i ++){
		this->selObjects[i] = sel.containsObject(i);
	}

	//sides
	for(int i = 0; i < (int)SideList.size(); i ++){
		this->selSides[i] = sel.containsSide(i);
	}
}
/**
	選択情報の取得
*/
bool hpl::aleph::HPLStockManager::isSelectPoint(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selPoints.size());
#endif
	return this->selPoints[index];
}
bool hpl::aleph::HPLStockManager::isSelectLine(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selLines.size());
#endif
	return this->selLines[index];
}
bool hpl::aleph::HPLStockManager::isSelectPolygon(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selPolygons.size());
#endif
	return this->selPolygons[index];
}
bool hpl::aleph::HPLStockManager::isSelectSide(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selSides.size());
#endif
	return this->selSides[index];
}
bool hpl::aleph::HPLStockManager::isSelectObject(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selObjects.size());
#endif
	return this->selObjects[index];
}
//設定
void hpl::aleph::HPLStockManager::setSelectPoint(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selPoints.size());
#endif
	this->selPoints[index] = sel;
}
void hpl::aleph::HPLStockManager::setSelectLine(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selLines.size());
#endif
	this->selLines[index] = sel;
}
void hpl::aleph::HPLStockManager::setSelectPolygon(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selPolygons.size());
#endif
	this->selPolygons[index] = sel;
}
void hpl::aleph::HPLStockManager::setSelectSide(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selSides.size());
#endif
	this->selSides[index] = sel;
}
void hpl::aleph::HPLStockManager::setSelectObject(int index, bool sel)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->selObjects.size());
#endif
	this->selObjects[index] = sel;
}

////////////////
bool hpl::aleph::HPLStockManager::isDeletePoint(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delPoints.size());
#endif
	return this->delPoints[index];
}
bool hpl::aleph::HPLStockManager::isDeleteLine(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delLines.size());
#endif
	return this->delLines[index];
}
bool hpl::aleph::HPLStockManager::isDeletePolygon(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delPolygons.size());
#endif
	return this->delPolygons[index];
}
bool hpl::aleph::HPLStockManager::isDeleteSide(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delSides.size());
#endif
	return this->delSides[index];
}
bool hpl::aleph::HPLStockManager::isDeleteObject(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index <(int) this->delObjects.size());
#endif
	return this->delObjects[index];
}
bool hpl::aleph::HPLStockManager::isDeletePlatform(int index)
{
#ifdef _WXDEBUG_
	wxASSERT(index >= 0 && index < (int)this->delPlatforms.size());
#endif
	return this->delPlatforms[index];
}

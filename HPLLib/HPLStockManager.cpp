#include "HPLStockManager.h"

#include "map.h"

hpl::aleph::HPLStockManagerHPLStockManager()
{
}
hpl::aleph::HPLStockManager~HPLStockManager()
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
    ・点削除→
        端点になっている線を消す
        （ポリゴンを消す←線の部分で行う）
        （Side、Objectは無関係）

        依存項目はない

    ・線削除→
        Sideも削除
        ポリゴンを消す
        （点はこれ以上消さない。オブジェクトは無関係）

        依存項目なし

    ・Side削除→
        存在としては他と独立しているので、他に消すものはない

        線のSideをNONEに
        ポリゴンのside_indexesの該当部分をNONEに
        
    ・ポリゴン削除→
        空間になるので、Sideも削除（line_data::clockwise_polygon_ownerなどで調べる）
        乗っているオブジェクトを削除
        
        点、線、Sideのポリゴン番号をNONEに

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

    //点関連の削除対象整理
    for(int i = 0; i < (int)delPoints.size(); i ++){
        if(delPoints[i]){
            //削除対象
            //所有している線も削除する
            std::vector<int> lineIndexes = hpl::aleph::map::getLineIndexesIncludePoint(i);
            for(int j = 0; j < (int)lineIndexes.size(); j ++){
                delLines[lineIndexes[i]] = true;
            }
        }else{
            //残る
            endpoint_data* ep = get_endpoint_data(i);
            if(ep->supporting_polygon_index != NONE && 
                get_polygon_data(ep->supporting_polygon_index) != NULL &&
                delPolygon[ep->supporting_polygon_index])
            {
                //関連ポリゴンが消されるならば対応を切っておく
                ep->supporting_polygon_index = NONE;
            }
        }
    }
    for(int i = 0; i < (int)delLines.size(); i ++){
        line_data* line = get_line_data(i);
        if(delLine[i]){
            //関連するポリゴンを削除する
            if(line->clockwise_polygon_owner != NONE){
                delPolygons[line->clockwise_polygon_owner] = true;
            }
            if(line->counterclockwise_polygon_owner != NONE){
                delPolygons[line->counterclockwise_polygon_owner] = true;
            }
        }else{
            //残る
            //点が消えていたら残っているわけがないので考慮しなくてよい
            //Sideが消えていたら関連を切る
            if(delSides.at(line->clockwise_polygon_side_index)){
                line->clockwise_polygon_side_index = NONE;
            }
            if(delSides[line->counterclockwise_polygon_side_index]){
                line->counterclockwise_polygon_side_index = NONE;
            }
        }
    }

    //Side
    for(int i = 0; i < (int)delSides.size(); i ++){
        side_data* side = get_side_data(i);
        if(delSides[i]){
            //消す
            //線からリンクを外させる
            //…のはすでに終わっている
        }else{
            //残る
            //関連するインデックスをNONEにする
            if(delLines[side->line_index]){
                side->line_index = NONE;
            }
            if(delPolygon[side->polygon_index]){
                //自身も削除する
                side->polygon_index = NONE;
            }
        }
    }
    //ポリゴン
    for(int i = 0; i < (int)delPolygons.size(); i ++){
        polygon_data* poly = get_polygon_data(i);
        if(delPolygons[i]){
            //削除対象
            //オブジェクトも消す
            
        }else{
            //残る
        }
    }
}

/**
    削除情報を初期化
    実際にはclearした後にdaupteDeletes()を呼んでるだけ
*/
void hpl::aleph::HPLStockManager::resetDeletes()
{
}

bool hpl::aleph::HPLStockManager::deletePoint(int index)
{
    if(get_endpoint_data(index) == NULL){
        return false;
    }
    this->delPoints[index] = true;
}
bool hpl::aleph::HPLStockManager::deleteLine(int index)
{
}
bool hpl::aleph::HPLStockManager::deletePolygon(int index)
{
}
bool hpl::aleph::HPLStockManager::deleteSide(int index)
{
}
bool hpl::aleph::HPLStockManager::deleteObject(int index)
{
}

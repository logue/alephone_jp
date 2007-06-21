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
*/
void hpl::aleph::HPLStockManager::updateDeletes()
{
    //points
    for(int i = delPoints.size(); i < dynamic_world->endpoint_count; i ++){

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

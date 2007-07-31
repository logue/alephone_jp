#include "HPLDoneHistory.h"
#include "HPLError.h"

const int DEFAULT_INDEX_MAX = 10;

hpl::aleph::map::HPLActionItem::HPLActionItem(int t, hpl::aleph::map::HPLSelectData& sel, hpl::aleph::map::HPLRealMapData& real)
{
    type = t;
	this->selectData = sel;
	this->realData = real;

	//現在位置を覚えておきます
	for(int i = 0; i < sel.getSelPoints()->size(); i ++){
		int index = sel.getSelPoints()->at(i).index;
		endpoint_data* ep = get_endpoint_data(index);
		this->pointVertexMap[index][0] = ep->vertex.x;
		this->pointVertexMap[index][1] = ep->vertex.y;
	}
	for(int i = 0; i < sel.getSelObjects()->size(); i ++){
		int index = sel.getSelObjects()->at(i).index;
		map_object* obj = &SavedObjectList[index];
		this->objectLocationMap[index][0] = obj->location.x;
		this->objectLocationMap[index][1] = obj->location.y;
		this->objectLocationMap[index][2] = obj->location.z;
	}
//    memcpy(&this->selectData, &sel, sizeof(hpl::aleph::map::HPLSelectData));
//    memcpy(&this->realData, &real, sizeof(hpl::aleph::map::HPLRealMapData));
}
hpl::aleph::map::HPLActionItem::~HPLActionItem()
{
	int a = 0;
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
hpl::aleph::map::HPLDoneHistory::HPLDoneHistory()
{
    index = -1;
	setIndexMax(DEFAULT_INDEX_MAX);
}
hpl::aleph::map::HPLDoneHistory::~HPLDoneHistory()
{
    actionList.clear();
}
/**
	最大数を設定します
*/
void hpl::aleph::map::HPLDoneHistory::setIndexMax(int m)
{
	this->indexMax = m;
}
int hpl::aleph::map::HPLDoneHistory::getIndexMax()
{
	return this->indexMax;
}

/**
    情報を追加します
*/
void hpl::aleph::map::HPLDoneHistory::push_back(int type, HPLSelectData& selData)
{
    //現在の位置(index)から後ろ部分を削除します
    if(index >= 0 && index < (int)actionList.size() - 1 && (int)actionList.size() > 1){
        std::vector<hpl::aleph::map::HPLActionItem>::iterator it = actionList.begin();
        it += (index);
        while(it != actionList.end()){
            it = actionList.erase(it);
        }
    }
	//全体の数がindexMax-1以下となるように最初の部分を削除します
	int imax = getIndexMax();
	for(int i = 0; (int)this->actionList.size() > 0 && i < (int)this->actionList.size() - imax + 1; i ++){
		actionList.erase(actionList.begin());
	}

    //実データを取得します
    hpl::aleph::map::HPLRealMapData realData;
    realData.set(selData);

    //追加
    hpl::aleph::map::HPLActionItem act = hpl::aleph::map::HPLActionItem(type, selData, realData);
    this->actionList.push_back(act);

    
    index = (int)actionList.size() - 1;
//	delete act;
}

/**
    index番目のものを取り出します。
    最大記憶量を超えていたらNULLが入り、falseが返ります
    取り出したとしても、selectDataは
    ・保存によって削除が実行された後
    にインデックス値が変化してしまうため、updateIndexes()を呼ぶ必要がある
    @return 取り出せなかった場合偽
*/
bool hpl::aleph::map::HPLDoneHistory::back(hpl::aleph::map::HPLActionItem* act)
{
    if(index < 0){
        return false;
    }
    *act = this->actionList[index];
    index --;
    return true;
}
bool hpl::aleph::map::HPLDoneHistory::forward(hpl::aleph::map::HPLActionItem* act)
{
    if(index >= (int)this->actionList.size()){
        return false;
    }
    *act = this->actionList[index];
    index ++;
    return true;
}

/**
	最新版の状態を取得します
	取得しても内容や位置は変化させません
*/
bool hpl::aleph::map::HPLDoneHistory::getTail(hpl::aleph::map::HPLActionItem* act)
{
	if(actionList.size() == 0){
		return false;
	}
	*act = this->actionList[actionList.size() - 1];
	return true;
}

/**
    インデックス番号を削除後のものに対応させます。
*/
void hpl::aleph::map::HPLDoneHistory::updateIndexes(hpl::aleph::HPLStockManager* smgr)
{
    //TODO
	//そんなもん保持するわけないだろう
	//常識的に考えて…
	hpl::error::halt("Invalid function you called :/");
}
int hpl::aleph::map::HPLDoneHistory::getIndex()
{
    return index;
}
int hpl::aleph::map::HPLDoneHistory::getRemainUndoCount()
{
    return index;
}
int hpl::aleph::map::HPLDoneHistory::getRemainRedoCount()
{
    return (int)actionList.size() - index;
}

/**
	初期化します
*/
void hpl::aleph::map::HPLDoneHistory::init()
{
	this->actionList.clear();
	index = 0;
}

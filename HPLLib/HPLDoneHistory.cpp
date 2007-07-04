#include "HPLDoneHistory.h"
#include "HPLError.h"

hpl::aleph::map::HPLActionItem::HPLActionItem(int t, hpl::aleph::map::HPLSelectData& sel, hpl::aleph::map::HPLRealMapData& real)
{
    type = t;
    memcpy(&this->selectData, &sel, sizeof(hpl::aleph::map::HPLSelectData));
    memcpy(&this->realData, &real, sizeof(hpl::aleph::map::HPLRealMapData));
}
hpl::aleph::map::HPLActionItem::~HPLActionItem()
{
}

//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
hpl::aleph::map::HPLDoneHistory::HPLDoneHistory()
{
    index = -1;
}
hpl::aleph::map::HPLDoneHistory::~HPLDoneHistory()
{
    actionList.clear();
}
/**
    情報を追加します
*/
void hpl::aleph::map::HPLDoneHistory::push_back(int type, HPLSelectData& selData)
{
    //現在の位置(index)から後ろ部分を削除します
    if(index >= 0){
        std::vector<hpl::aleph::map::HPLActionItem>::iterator it = actionList.begin();
        it += (index + 1);
        while(it != actionList.end()){
            it = actionList.erase(it);
        }
    }
    //実データを取得します
    hpl::aleph::map::HPLRealMapData realData;
    realData.set(&selData);

    //追加
    hpl::aleph::map::HPLActionItem act = hpl::aleph::map::HPLActionItem(type, selData, realData);
    this->actionList.push_back(act);

    
    index = (int)actionList.size() - 1;
}

/**
    index番目のものを取り出します。
    最大記憶量を超えていたらNULLが入り、falseが返ります
    取り出したとしても、selectDataは
    ・保存によって削除が実行された後
    にインデックス値が変化してしまうため、updateIndexes()を呼ぶ必要がある
    @return 取り出せなかった場合偽
*/
bool hpl::aleph::map::HPLDoneHistory::back(int *type, hpl::aleph::map::HPLSelectData* selectData,
                                           hpl::aleph::map::HPLRealMapData* realData)
{
    if(index < 0){
        return false;
    }
    hpl::aleph::map::HPLActionItem act = this->actionList[index];
    memcpy(selectData, &act.selectData, sizeof(hpl::aleph::map::HPLSelectData));
    memcpy(realData, &act.realData, sizeof(hpl::aleph::map::HPLRealMapData));
    *type = act.type;
    index --;
    return true;
}
bool hpl::aleph::map::HPLDoneHistory::forward(int *type, HPLSelectData* selectData, HPLRealMapData* realData)
{
    if(index >= (int)this->actionList.size()){
        return false;
    }
    hpl::aleph::map::HPLActionItem act = this->actionList[index];
    memcpy(selectData, &act.selectData, sizeof(hpl::aleph::map::HPLSelectData));
    memcpy(realData, &act.realData, sizeof(hpl::aleph::map::HPLRealMapData));
    *type = act.type;
    index ++;
    return true;
}


/**
    インデックス番号を削除後のものに対応させます。
*/
void hpl::aleph::map::HPLDoneHistory::updateIndexes(hpl::aleph::HPLStockManager* smgr)
{
    //TODO
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
    return actionList.size() - index;
}

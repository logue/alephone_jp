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
    ����ǉ����܂�
*/
void hpl::aleph::map::HPLDoneHistory::push_back(int type, HPLSelectData& selData)
{
    //���݂̈ʒu(index)�����땔�����폜���܂�
    if(index >= 0){
        std::vector<hpl::aleph::map::HPLActionItem>::iterator it = actionList.begin();
        it += (index + 1);
        while(it != actionList.end()){
            it = actionList.erase(it);
        }
    }
    //���f�[�^���擾���܂�
    hpl::aleph::map::HPLRealMapData realData;
    realData.set(&selData);

    //�ǉ�
    hpl::aleph::map::HPLActionItem act = hpl::aleph::map::HPLActionItem(type, selData, realData);
    this->actionList.push_back(act);

    
    index = (int)actionList.size() - 1;
}

/**
    index�Ԗڂ̂��̂����o���܂��B
    �ő�L���ʂ𒴂��Ă�����NULL������Afalse���Ԃ�܂�
    ���o�����Ƃ��Ă��AselectData��
    �E�ۑ��ɂ���č폜�����s���ꂽ��
    �ɃC���f�b�N�X�l���ω����Ă��܂����߁AupdateIndexes()���ĂԕK�v������
    @return ���o���Ȃ������ꍇ�U
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
    �C���f�b�N�X�ԍ����폜��̂��̂ɑΉ������܂��B
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

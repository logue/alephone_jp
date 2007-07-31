#include "HPLDoneHistory.h"
#include "HPLError.h"

const int DEFAULT_INDEX_MAX = 10;

hpl::aleph::map::HPLActionItem::HPLActionItem(int t, hpl::aleph::map::HPLSelectData& sel, hpl::aleph::map::HPLRealMapData& real)
{
    type = t;
	this->selectData = sel;
	this->realData = real;

	//���݈ʒu���o���Ă����܂�
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
	�ő吔��ݒ肵�܂�
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
    ����ǉ����܂�
*/
void hpl::aleph::map::HPLDoneHistory::push_back(int type, HPLSelectData& selData)
{
    //���݂̈ʒu(index)�����땔�����폜���܂�
    if(index >= 0 && index < (int)actionList.size() - 1 && (int)actionList.size() > 1){
        std::vector<hpl::aleph::map::HPLActionItem>::iterator it = actionList.begin();
        it += (index);
        while(it != actionList.end()){
            it = actionList.erase(it);
        }
    }
	//�S�̂̐���indexMax-1�ȉ��ƂȂ�悤�ɍŏ��̕������폜���܂�
	int imax = getIndexMax();
	for(int i = 0; (int)this->actionList.size() > 0 && i < (int)this->actionList.size() - imax + 1; i ++){
		actionList.erase(actionList.begin());
	}

    //���f�[�^���擾���܂�
    hpl::aleph::map::HPLRealMapData realData;
    realData.set(selData);

    //�ǉ�
    hpl::aleph::map::HPLActionItem act = hpl::aleph::map::HPLActionItem(type, selData, realData);
    this->actionList.push_back(act);

    
    index = (int)actionList.size() - 1;
//	delete act;
}

/**
    index�Ԗڂ̂��̂����o���܂��B
    �ő�L���ʂ𒴂��Ă�����NULL������Afalse���Ԃ�܂�
    ���o�����Ƃ��Ă��AselectData��
    �E�ۑ��ɂ���č폜�����s���ꂽ��
    �ɃC���f�b�N�X�l���ω����Ă��܂����߁AupdateIndexes()���ĂԕK�v������
    @return ���o���Ȃ������ꍇ�U
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
	�ŐV�ł̏�Ԃ��擾���܂�
	�擾���Ă����e��ʒu�͕ω������܂���
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
    �C���f�b�N�X�ԍ����폜��̂��̂ɑΉ������܂��B
*/
void hpl::aleph::map::HPLDoneHistory::updateIndexes(hpl::aleph::HPLStockManager* smgr)
{
    //TODO
	//����Ȃ���ێ�����킯�Ȃ����낤
	//�펯�I�ɍl���āc
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
	���������܂�
*/
void hpl::aleph::map::HPLDoneHistory::init()
{
	this->actionList.clear();
	index = 0;
}

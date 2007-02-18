#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCdialog.h>
#include <WSClist.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void CollectionBtnFunc(WSCbase* object){
  //do something...
	//�I���_�C�A���O��\��
	WSCbase* dlg = getObject("WSCdialog", "WndSelect");
	//���X�g�Ɍ�����
	//�R���N�V�������X�g
	WSClist* lst = (WSClist*)getChild(dlg, "ListSelect");
	lst->delAll();
	//
	for(int i = 0; i < (int)stockCollections.size(); i ++){
		lst->addItem((char*)stockCollections[i].c_str());
	}
	int type = selectedMonsterType;
	int16 collection = monster_definitions[type].collection;
	int16 col = GET_COLLECTION(collection);
	int16 clut = GET_COLLECTION_CLUT(collection);
	lst->setSelectPos(col);
	long ret = ((WSCdialog*)dlg)->popup();
	if(ret == WS_DIALOG_OK){
		//�l���擾
		int index = selectIndex;
		if(index != -1){
			col = index;
			collection = BUILD_COLLECTION(col, clut);
			monster_definitions[type].collection = collection;
		}
	}else{
	}
	setupDialog();
}
static WSCfunctionRegister  op("CollectionBtnFunc",(void*)CollectionBtnFunc);

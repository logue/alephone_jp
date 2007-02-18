#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void CaarryItemBtnFunc(WSCbase* object){
  //do something...
	//setup dialog
	WSCbase* dlg = getObject("WSCdialog", "WndSelect");
	WSClist* lst = (WSClist*)getChild(dlg, "ListSelect");
	lst->delAll();
	//setup list
	for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
		lst->addItem((char*)stockItemTypes[i].c_str());
	}
	int type = selectedMonsterType;
	int oldIndex = monster_definitions[type].carrying_item_type;
	lst->setSelectPos(oldIndex);
	long ret = ((WSCdialog*)dlg)->popup();
	if(ret == WS_DIALOG_OK){
		int index = selectIndex;
		if(index != -1){
			monster_definitions[type].carrying_item_type = index;
		}
	}else{
	}
	setupDialog();
}
static WSCfunctionRegister  op("CaarryItemBtnFunc",(void*)CaarryItemBtnFunc);

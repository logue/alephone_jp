#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void CaarryItemBtnFunc(WSCbase* object){
	int type = selectedMonsterType;
	int index = monster_definitions[type].carrying_item_type;
	bool isMax = true;
	long ret = selectFromDialog(&index, object, stockItemTypes, isMax);
	if(ret == WS_DIALOG_OK){
		monster_definitions[type].carrying_item_type = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("CaarryItemBtnFunc",(void*)CaarryItemBtnFunc);

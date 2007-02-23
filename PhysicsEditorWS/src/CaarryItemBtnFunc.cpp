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
	monster_definitions[type].carrying_item_type = index;
	bool isMax = true;
	selectFromDialog(&index, object, stockItemTypes, isMax);
	setupDialog();
}
static WSCfunctionRegister  op("CaarryItemBtnFunc",(void*)CaarryItemBtnFunc);

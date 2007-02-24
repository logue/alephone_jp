#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ShapnelTypeBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMax = true;
	int index = monster_definitions[type].shrapnel_damage.type;
	long ret = selectFromDialog(&index, object, stockDamages, isMax);
	if(ret == WS_DIALOG_OK){
		monster_definitions[type].shrapnel_damage.type = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("ShapnelTypeBtnDownFunc",(void*)ShapnelTypeBtnDownFunc);

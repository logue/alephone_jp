#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ClearSndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	int index = monster_definitions[type].clear_sound;
	selectFromDialog((int*)&index,
		object, stockSounds, isMaxNONE);
	monster_definitions[type].clear_sound = index;
	setupDialog();
}
static WSCfunctionRegister  op("ClearSndBtnDownFunc",(void*)ClearSndBtnDownFunc);

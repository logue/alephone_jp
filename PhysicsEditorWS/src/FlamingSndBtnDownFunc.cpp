#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FlamingSndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*�L��
	int index = monster_definitions[type].flaming_sound;
	long ret = selectFromDialog((int*)&index,
		object, stockSounds, isMaxNONE);
	if(ret == WS_DIALOG_OK){
		monster_definitions[type].flaming_sound = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("FlamingSndBtnDownFunc",(void*)FlamingSndBtnDownFunc);

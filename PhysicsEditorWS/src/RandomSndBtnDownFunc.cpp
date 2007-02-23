#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void RandomSndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	int index = monster_definitions[type].random_sound;
	selectFromDialog((int*)&index,
		object, stockSounds, isMaxNONE);
	monster_definitions[type].random_sound = index;
	setupDialog();
}
static WSCfunctionRegister  op("RandomSndBtnDownFunc",(void*)RandomSndBtnDownFunc);

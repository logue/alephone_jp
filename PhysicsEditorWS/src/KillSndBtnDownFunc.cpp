#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void KillSndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	int index = monster_definitions[type].kill_sound;
	long ret = selectFromDialog((int*)&index,
		object, stockSounds, isMaxNONE);
	if(ret == WS_DIALOG_OK){
		monster_definitions[type].kill_sound = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("KillSndBtnDownFunc",(void*)KillSndBtnDownFunc);

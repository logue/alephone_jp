#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FriendActSndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	int index = monster_definitions[type].friendly_activation_sound;
	selectFromDialog(&index,
		object, stockSounds, isMaxNONE);
	monster_definitions[type].friendly_activation_sound = index;
	setupDialog();
}
static WSCfunctionRegister  op("FriendActSndBtnDownFunc",(void*)FriendActSndBtnDownFunc);

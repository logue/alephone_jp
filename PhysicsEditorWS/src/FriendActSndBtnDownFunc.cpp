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
	long ret = selectFromDialog(&index,
		object, stockSounds, isMaxNONE);
	if(ret == WS_DIALOG_OK){
		monster_definitions[type].friendly_activation_sound = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("FriendActSndBtnDownFunc",(void*)FriendActSndBtnDownFunc);

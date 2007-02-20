#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FriendFireSndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	selectFromDialog(&monster_definitions[type].friendly_fire_sound,
		object, stockSounds, isMaxNONE);
}
static WSCfunctionRegister  op("FriendFireSndBtnDownFunc",(void*)FriendFireSndBtnDownFunc);

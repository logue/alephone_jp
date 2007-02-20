#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FriendActSndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	selectFromDialog(&monster_definitions[type].friendly_activation_sound,
		object, stockSounds, isMaxNONE);
}
static WSCfunctionRegister  op("FriendActSndBtnDownFunc",(void*)FriendActSndBtnDownFunc);

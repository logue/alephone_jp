#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ClearSndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	selectFromDialog(&monster_definitions[type].clear_sound,
		object, stockSounds, isMaxNONE);
}
static WSCfunctionRegister  op("ClearSndBtnDownFunc",(void*)ClearSndBtnDownFunc);

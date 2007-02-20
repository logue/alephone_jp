#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void RandomSndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	selectFromDialog(&monster_definitions[type].random_sound,
		object, stockSounds, isMaxNONE);
}
static WSCfunctionRegister  op("RandomSndBtnDownFunc",(void*)RandomSndBtnDownFunc);

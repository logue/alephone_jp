#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ApologySndBtnDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*—L‚è
	selectFromDialog(&monster_definitions[type].apology_sound,
		object, stockSounds, isMaxNONE);
}
static WSCfunctionRegister  op("ApologySndBtnDownFunc",(void*)ApologySndBtnDownFunc);

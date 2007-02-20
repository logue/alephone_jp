#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ActivationSndBtnDownFunc(WSCbase* object){
	//ëIëÇµÇƒílê›íË
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*óLÇË
	selectFromDialog(&monster_definitions[type].activation_sound,
		object, stockSounds, isMaxNONE);
}
static WSCfunctionRegister  op("ActivationSndBtnDownFunc",(void*)ActivationSndBtnDownFunc);

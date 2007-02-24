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
	int index = monster_definitions[type].activation_sound;
	long ret = selectFromDialog(&index, object, stockSounds, isMaxNONE);
	if(ret == WS_DIALOG_OK){
		monster_definitions[type].activation_sound = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("ActivationSndBtnDownFunc",(void*)ActivationSndBtnDownFunc);

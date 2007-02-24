#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnEffectDelaySoundDownFunc(WSCbase* object){
	int type = selectedEffectType;
	bool isMax = true;
	int index = effect_definitions[type].delay_sound;
	long ret = selectFromDialog(&index, object, stockSounds, isMax);
	if(ret == WS_DIALOG_OK){
		effect_definitions[type].delay_sound = index;
		setupDialog();
	}
}
static WSCfunctionRegister  op("BtnEffectDelaySoundDownFunc",(void*)BtnEffectDelaySoundDownFunc);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ActivationSndBtnDownFunc(WSCbase* object){
	//�I�����Ēl�ݒ�
	int type = selectedMonsterType;
	bool isMaxNONE = true;//*none*�L��
	selectFromDialog(&monster_definitions[type].activation_sound,
		object, stockSounds, isMaxNONE);
}
static WSCfunctionRegister  op("ActivationSndBtnDownFunc",(void*)ActivationSndBtnDownFunc);

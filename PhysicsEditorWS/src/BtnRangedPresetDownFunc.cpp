#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnRangedPresetDownFunc(WSCbase* object){
	const int TEMP = 999;
	int index = TEMP;
	bool isMax = false;
	//モンスターから選ぶ
	selectFromDialog(&index, object, stockMonsterTypes, isMax);
	if(index != TEMP){
		//コピー
		int type = selectedMonsterType;
		memcpy(&monster_definitions[type].ranged_attack,
			&monster_default_definitions[index].ranged_attack, sizeof(struct attack_definition));
		setupDialog();
	}
}
static WSCfunctionRegister  op("BtnRangedPresetDownFunc",(void*)BtnRangedPresetDownFunc);

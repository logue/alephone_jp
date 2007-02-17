#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnPresetThisAllEnemyOnDownFunc(WSCbase* object){
  //do something...
	//enemies & friends
	WSCcheckGroup* lstEnemies = (WSCcheckGroup*)getObject("WSCcheckGroup", "ListEnemies");
	WSCcheckGroup* lstFriends = (WSCcheckGroup*)getObject("WSCcheckGroup", "ListFriends");
	int type = selectedMonsterType;
	if(type >= 0 && type < NUMBER_OF_MONSTER_TYPES){
		int enemies = monster_definitions[type].enemies;
		int friends = monster_definitions[type].friends;
		for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
			WSCvtoggle* enemy = (WSCvtoggle*)lstEnemies->getItem(i);
			WSCvtoggle* _friend = (WSCvtoggle*)lstFriends->getItem(i);
			enemy->setStatus(True);
			_friend->setStatus(False);
		}
		//•ÏXŒÄ‚Ño‚µ
		lstEnemies->onValueChange();
		lstFriends->onValueChange();
	}
}
static WSCfunctionRegister  op("BtnPresetThisAllEnemyOnDownFunc",(void*)BtnPresetThisAllEnemyOnDownFunc);

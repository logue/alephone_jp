#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnSelPresetSeqDownFunc(WSCbase* object){
	int type = selectedMonsterType;
	int index = 1;
	bool isMax = false;
	selectFromDialog(&index, object, stockMonsterTypes, isMax);
	//copy sequences
	monster_definitions[type].stationary_shape =
		monster_default_definitions[index].stationary_shape;
	monster_definitions[type].moving_shape =
		monster_default_definitions[index].moving_shape;
	monster_definitions[type].soft_dying_shape =
		monster_default_definitions[index].soft_dying_shape;
	monster_definitions[type].soft_dead_shapes =
		monster_default_definitions[index].soft_dead_shapes;
	monster_definitions[type].hard_dying_shape =
		monster_default_definitions[index].hard_dying_shape;
	monster_definitions[type].hard_dead_shapes =
		monster_default_definitions[index].hard_dead_shapes;
	monster_definitions[type].hit_shapes =
		monster_default_definitions[index].hit_shapes;
	monster_definitions[type].teleport_in_shape =
		monster_default_definitions[index].teleport_in_shape;
	monster_definitions[type].teleport_out_shape =
		monster_default_definitions[index].teleport_out_shape;
	setupDialog();
}
static WSCfunctionRegister  op("BtnSelPresetSeqDownFunc",(void*)BtnSelPresetSeqDownFunc);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjDamageScaleVChF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("ProjDamageScaleVChF",(void*)ProjDamageScaleVChF);

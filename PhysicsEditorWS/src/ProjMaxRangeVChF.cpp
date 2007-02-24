#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjMaxRangeVChF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("ProjMaxRangeVChF",(void*)ProjMaxRangeVChF);

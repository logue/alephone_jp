#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WTicksPerRoundVChF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("WTicksPerRoundVChF",(void*)WTicksPerRoundVChF);

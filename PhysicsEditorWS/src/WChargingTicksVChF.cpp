#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WChargingTicksVChF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("WChargingTicksVChF",(void*)WChargingTicksVChF);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MeleedyVChFunc(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("MeleedyVChFunc",(void*)MeleedyVChFunc);

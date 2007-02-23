#include "General.h"
#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MeleedxVChFunc(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("MeleedxVChFunc",(void*)MeleedxVChFunc);

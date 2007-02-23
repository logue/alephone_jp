#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void RangeddyVChFunc(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("RangeddyVChFunc",(void*)RangeddyVChFunc);

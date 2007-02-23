#include "General.h"
#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MeleeSeqVChFunc(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("MeleeSeqVChFunc",(void*)MeleeSeqVChFunc);

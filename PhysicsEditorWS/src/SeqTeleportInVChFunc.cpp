#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void SeqTeleportInVChFunc(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("SeqTeleportInVChFunc",(void*)SeqTeleportInVChFunc);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WdxVChF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("WdxVChF",(void*)WdxVChF);

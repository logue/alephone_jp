#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WSdxVChF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("WSdxVChF",(void*)WSdxVChF);

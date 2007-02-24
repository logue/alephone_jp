#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjTicksBetContrailDownF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("ProjTicksBetContrailDownF",(void*)ProjTicksBetContrailDownF);

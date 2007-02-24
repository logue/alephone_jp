#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjRadiusVChF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("ProjRadiusVChF",(void*)ProjRadiusVChF);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WRoundPerMagVChF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("WRoundPerMagVChF",(void*)WRoundPerMagVChF);

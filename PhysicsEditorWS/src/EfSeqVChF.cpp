#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void EfSeqVChF(WSCbase* object){
	setValueByName(object);
}
static WSCfunctionRegister  op("EfSeqVChF",(void*)EfSeqVChF);

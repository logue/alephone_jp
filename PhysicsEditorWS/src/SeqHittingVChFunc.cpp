#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void SeqHittingVChFunc(WSCbase* object){
  //do something...
	setValueByName(object);
}
static WSCfunctionRegister  op("SeqHittingVChFunc",(void*)SeqHittingVChFunc);

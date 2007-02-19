#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void SeqStationalyValueChFunc(WSCbase* object){
  //do something...
	setValueByName(object);
}
static WSCfunctionRegister  op("SeqStationalyValueChFunc",(void*)SeqStationalyValueChFunc);

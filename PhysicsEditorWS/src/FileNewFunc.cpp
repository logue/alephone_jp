#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FileNewFunc(WSCbase* object){
  //do something...
	//set as default
	setDefinitionsToDefault();
	//çXêV
}
static WSCfunctionRegister  op("FileNewFunc",(void*)FileNewFunc);

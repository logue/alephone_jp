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
	//�X�V
}
static WSCfunctionRegister  op("FileNewFunc",(void*)FileNewFunc);

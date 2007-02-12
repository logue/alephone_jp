#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FileSaveFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("FileSaveFunc",(void*)FileSaveFunc);

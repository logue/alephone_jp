#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MainResizeFunc(WSCbase* object){
  //do something...
	//resize drawarea
	
}
static WSCfunctionRegister  op("MainResizeFunc",(void*)MainResizeFunc);

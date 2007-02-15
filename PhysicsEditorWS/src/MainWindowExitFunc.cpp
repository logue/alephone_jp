#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MainWindowExitFunc(WSCbase* object){
  //do something...
	exit(0);
}
static WSCfunctionRegister  op("MainWindowExitFunc",(void*)MainWindowExitFunc);

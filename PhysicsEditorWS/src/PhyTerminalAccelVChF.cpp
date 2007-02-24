#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyTerminalAccelVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyTerminalAccelVChF",(void*)PhyTerminalAccelVChF);

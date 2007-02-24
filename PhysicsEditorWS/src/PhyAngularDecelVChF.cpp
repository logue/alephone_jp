#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyAngularDecelVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyAngularDecelVChF",(void*)PhyAngularDecelVChF);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyAngularAccelVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyAngularAccelVChF",(void*)PhyAngularAccelVChF);

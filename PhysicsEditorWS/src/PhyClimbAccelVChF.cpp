#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyClimbAccelVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyClimbAccelVChF",(void*)PhyClimbAccelVChF);

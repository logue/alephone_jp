#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyGravAccelVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyGravAccelVChF",(void*)PhyGravAccelVChF);

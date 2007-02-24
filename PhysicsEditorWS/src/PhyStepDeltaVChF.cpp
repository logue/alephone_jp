#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyStepDeltaVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyStepDeltaVChF",(void*)PhyStepDeltaVChF);

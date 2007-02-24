#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyStepAmpVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyStepAmpVChF",(void*)PhyStepAmpVChF);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyRadiusVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyRadiusVChF",(void*)PhyRadiusVChF);

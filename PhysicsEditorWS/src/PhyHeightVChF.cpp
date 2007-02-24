#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyHeightVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyHeightVChF",(void*)PhyHeightVChF);

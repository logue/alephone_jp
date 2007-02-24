#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyMaxPerpendVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyMaxPerpendVChF",(void*)PhyMaxPerpendVChF);

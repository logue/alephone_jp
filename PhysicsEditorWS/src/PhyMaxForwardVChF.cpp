#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyMaxForwardVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyMaxForwardVChF",(void*)PhyMaxForwardVChF);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyAccelVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyAccelVChF",(void*)PhyAccelVChF);

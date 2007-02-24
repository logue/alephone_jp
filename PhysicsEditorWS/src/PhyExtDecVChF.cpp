#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhyExtDecVChF(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhyExtDecVChF",(void*)PhyExtDecVChF);

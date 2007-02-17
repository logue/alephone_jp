#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhysicsTypeOptChFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("PhysicsTypeOptChFunc",(void*)PhysicsTypeOptChFunc);

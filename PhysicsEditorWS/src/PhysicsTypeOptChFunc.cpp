#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PhysicsTypeOptChFunc(WSCbase* object){
  //do something...
	int index = ((WSCoption*)object)->getValue();
	selectedPhysicsType = index-1;
//	messageBox("index=%d", index);
	setupDialog();
}
static WSCfunctionRegister  op("PhysicsTypeOptChFunc",(void*)PhysicsTypeOptChFunc);
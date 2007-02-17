#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>


#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnPhysicsDownFunc(WSCbase* object){
	changeForm(Windows::Physics);
}
static WSCfunctionRegister  op("BtnPhysicsDownFunc",(void*)BtnPhysicsDownFunc);

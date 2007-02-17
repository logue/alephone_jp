#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnProjectileDownFunc(WSCbase* object){
  //do something...
	changeForm(Windows::Projectile);
}
static WSCfunctionRegister  op("BtnProjectileDownFunc",(void*)BtnProjectileDownFunc);

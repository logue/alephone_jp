#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnWeaponDownFunc(WSCbase* object){
	changeForm(Windows::Weapon);
}
static WSCfunctionRegister  op("BtnWeaponDownFunc",(void*)BtnWeaponDownFunc);

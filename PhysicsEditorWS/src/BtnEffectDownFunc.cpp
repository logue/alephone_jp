#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>


#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnEffectDownFunc(WSCbase* object){
  //do something...
	changeForm(Windows::Effect);
}
static WSCfunctionRegister  op("BtnEffectDownFunc",(void*)BtnEffectDownFunc);

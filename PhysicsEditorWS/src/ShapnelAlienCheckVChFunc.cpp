#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ShapnelAlienCheckVChFunc(WSCbase* object){
  //do something...
	WSCbool status = ((WSCvradio*)object)->getStatus();
	int flag = 0;
	if(status == True){
		flag |= _alien_damage;
	}else{
	}
	monster_definitions[type].shrapnel_damage.flags = flag;
}
static WSCfunctionRegister  op("ShapnelAlienCheckVChFunc",(void*)ShapnelAlienCheckVChFunc);

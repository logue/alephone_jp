#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ProjDamageFlagsVChF(WSCbase* object){
	int type = selectedProjectileType;
	WSCbool status = ((WSCvradio*)object)->getStatus();
	int flags = 0;
	if(status == True){
		flags |= _alien_damage;
	}
	projectile_definitions[type].damage.flags = flags;
}
static WSCfunctionRegister  op("ProjDamageFlagsVChF",(void*)ProjDamageFlagsVChF);

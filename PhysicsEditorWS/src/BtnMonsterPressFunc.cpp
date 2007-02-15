#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"
#include <WSCwindow.h>

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnMonsterPressFunc(WSCbase* object){
  //do something...
	getObject("WSCform", "FrmEffect")->setVisible(false);
	getObject("WSCform", "FrmProjectile")->setVisible(false);
	getObject("WSCform", "FrmPhysics")->setVisible(false);
	getObject("WSCform", "FrmWeapon")->setVisible(false);
	WSCbase* obj = getObject("WSCform", "FrmMonster");
	obj->setVisible(true);
	windowType = Windows::Monster;
	setupDialog(obj);
}
static WSCfunctionRegister  op("BtnMonsterPressFunc",(void*)BtnMonsterPressFunc);

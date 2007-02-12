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
	//他のダイアログを閉じる
	{
		WSCwindow* obj = (WSCwindow*)getObject("WSCwindow", "WndEffect");
		obj->setVisible(false);
	}
	{
		WSCwindow* obj = (WSCwindow*)getObject("WSCwindow", "WndProjectile");
		obj->setVisible(false);
	}
	{
		WSCwindow* obj = (WSCwindow*)getObject("WSCwindow", "WndPhysics");
		obj->setVisible(false);
	}
	{
		WSCwindow* obj = (WSCwindow*)getObject("WSCwindow", "WndWeapon");
		obj->setVisible(false);
	}
	//モンスターダイアログの表示
	{
		WSCwindow* obj = (WSCwindow*)getObject("WSCwindow", "WndMonster");
		obj->setVisible(true);
		windowType = Windows::Monster;
		//モンスターウインドウ更新
		setupDialog(obj);
	}
}
static WSCfunctionRegister  op("BtnMonsterPressFunc",(void*)BtnMonsterPressFunc);

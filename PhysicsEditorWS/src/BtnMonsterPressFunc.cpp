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
	//���̃_�C�A���O�����
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
	//�����X�^�[�_�C�A���O�̕\��
	{
		WSCwindow* obj = (WSCwindow*)getObject("WSCwindow", "WndMonster");
		obj->setVisible(true);
		windowType = Windows::Monster;
		//�����X�^�[�E�C���h�E�X�V
		setupDialog(obj);
	}
}
static WSCfunctionRegister  op("BtnMonsterPressFunc",(void*)BtnMonsterPressFunc);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCbaseList.h>
#include <WSCwindow.h>

#include "General.h"

int windowType = Windows::Monster;

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MainInitFunc(WSCbase* object){
  //do something...
	//�q�E�C���h�E�̕\��
	char* class_name = "WSCwindow"; //���x���N���X
	char* obj_name   = "WndMonster";     //newvlab_001 �Ƃ�������
	WSCwindow* obj = (WSCwindow*)WSGIappObjectList()->getInstance(class_name,obj_name);
	obj->setVisible(true);
}
static WSCfunctionRegister  op("MainInitFunc",(void*)MainInitFunc);

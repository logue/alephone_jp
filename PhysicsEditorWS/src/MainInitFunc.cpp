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
	//子ウインドウの表示
	char* class_name = "WSCwindow"; //ラベルクラス
	char* obj_name   = "WndMonster";     //newvlab_001 という名称
	WSCwindow* obj = (WSCwindow*)WSGIappObjectList()->getInstance(class_name,obj_name);
	obj->setVisible(true);
}
static WSCfunctionRegister  op("MainInitFunc",(void*)MainInitFunc);

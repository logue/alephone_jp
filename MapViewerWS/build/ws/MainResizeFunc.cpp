#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCvdrawingArea.h>
#include <WSCbaseList.h>
#include <WSCmenuArea.h>

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MainResizeFunc(WSCbase* object){
  //do something...
	
	//get draw area
	WSCvdrawingArea* darea;
	{
		char* class_name = "WSCvdrawingArea"; //ラベルクラス
		char* obj_name   = "MainDrawArea";     //newvlab_001 という名称
		darea = (WSCvdrawingArea*)WSGIappObjectList()->getInstance(class_name,obj_name);
	}
	
	//get menu area
	WSCmenuArea* menuArea;
	{
		char* class_name = "WSCmenuArea"; //ラベルクラス
		char* obj_name   = "Maimenu_006";     //newvlab_001 という名称
		menuArea = (WSCmenuArea*)WSGIappObjectList()->getInstance(class_name,obj_name);
	}

	long wndWidth = object->getProperty(WSNwidth);
	long wndHeight = object->getProperty(WSNheight);
	long menuHeight = menuArea->getProperty(WSNheight);
	long dareaWidth = wndWidth;
	long dareaHeight = wndHeight - menuHeight;
	//resize drawarea
	darea->setProperty(WSNwidth, dareaWidth);
	darea->setProperty(WSNheight, dareaHeight);
}
static WSCfunctionRegister  op("MainResizeFunc",(void*)MainResizeFunc);

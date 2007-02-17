#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ListEffectDownFunc(WSCbase* object){
	selectedEffectType = ((WSClist*)object)->getSelectedPos();
//	messageBox("ListEffectDownFunc");
	//WSCbase* wnd = getObject("WSCform", "FrmEffect");
	setupDialog();
}
static WSCfunctionRegister  op("ListEffectDownFunc",(void*)ListEffectDownFunc);

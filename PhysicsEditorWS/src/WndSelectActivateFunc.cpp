#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCdialog.h>

#include "General.h"
#include <cassert>

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void WndSelectActivateFunc(WSCbase* object){
  //do something...
	WSCdialog* dlg = (WSCdialog*)object->cast("WSCdialog");
	if(dlg == NULL){
		messageBox("cannot cast");
		assert(false);
	}
	if(dlg->getStatus() != WS_DIALOG_OK){
		object->setVisible(False);
		return;
	}else{
		//‘I‘ğ€–Ú‚ğ”Ô†‚Éİ’è?
		//
	}
}
static WSCfunctionRegister  op("WndSelectActivateFunc",(void*)WndSelectActivateFunc);

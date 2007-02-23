#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FileSaveFunc(WSCbase* object){
	//保存ダイアログ
	//アプリケーションに1つあらかじめ用意されています。
	//ファイル選択ダイアログのインスタンスにアクセスします。
	WSCfileSelect* fs = WSGIappFileSelect(); //(C)
	fs->setProperty(WSNmaskFileName,"");  //(D)
	fs->setProperty(WSNdefaultPosition,True); //(E)
	long ret = fs->popup();                  //(F)
	if(ret == WS_DIALOG_OK){
		//保存
		WSCstring str = fs->getFileName();
		char buf[1024];
		strcpy(buf, str.getString());
		
		export_definition_structures(str);
	}
}
static WSCfunctionRegister  op("FileSaveFunc",(void*)FileSaveFunc);

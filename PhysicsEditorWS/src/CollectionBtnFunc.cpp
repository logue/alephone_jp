#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCdialog.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void CollectionBtnFunc(WSCbase* object){
  //do something...
	//選択ダイアログを表示
	WSCbase* dlg = getObject("WSCwindow", "WndSelect");
	//リストに候補を代入
	//コレクションリスト
	
	long ret = ((WSCdialog*)dlg)->popup();
	if(ret == WS_DIALOG_OK){
		//値を取得
		int index = selectIndex;
		
	}else{
	}
}
static WSCfunctionRegister  op("CollectionBtnFunc",(void*)CollectionBtnFunc);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCfileSelect.h>
#include <WSCbaseList.h>
#include <WSCmessageDialog.h>

#include "General.h"
#include "map.h"
#include "FileHandler.h"
#include "game_wad.h"
#include "extensions.h"

void importPhysicsFile(const char *filename){
	//物理ファイル名設定
	FileSpecifier phy = FileSpecifier(filename);
	set_physics_file(phy);
    //読み込み
	import_definition_structures();
}

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void open1(WSCbase* object){
  //do something...
	
	//init params
	selectedMonsterType = 0;
	selectedEffectType = 0;
	selectedProjectileType = 0;
	selectedPhysicsType = 0;
	selectedWeaponType = 0;
	
	//using file select dialog
	//アプリケーションに1つあらかじめ用意されています。
	//ファイル選択ダイアログのインスタンスにアクセスします。
	WSCfileSelect* fs = WSGIappFileSelect(); //(C)
	fs->setProperty(WSNmaskFileName,"");	//(D)
	fs->setProperty(WSNdefaultPosition,True); //(E)
	long ret = fs->popup();									 //(F)
	
	//アプリケーションに1つあらかじめ用意されている
	//メッセージダイアログのインスタンスを取得する。
	WSCmessageDialog* msg = WSGIappMessageDialog(); //(G)
	msg->setProperty(WSNwidth,500);									//(H)
	msg->setProperty(WSNheight,120);								//(I)
	msg->setProperty(WSNdefaultPosition,True);			//(J)
	
	if(ret == WS_DIALOG_OK){
		WSCstring str = fs->getFileName();
		char* path = str.getString();
		importPhysicsFile(path);
		//更新
		setupDialog();
	}

}
static WSCfunctionRegister  op("open1",(void*)open1);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void ShapnelTypeBtnDownFunc(WSCbase* object){
	//選択ダイアログを表示
	WSCbase* dlg = getObject("WSCdialog", "WndSelect");
	//リストに候補を代入
	//コレクションリスト
	WSClist* lst = (WSClist*)getChild(dlg, "ListSelect");
	lst->delAll();
	//
	for(int i = 0; i < (int)stockDamages.size(); i ++){
		lst->addItem((char*)stockDamages[i].c_str());
	}
	int type = selectedMonsterType;
	int shrapnelDamageType = monster_definitions[type].shrapnel_damage.type
	lst->setSelectPos(col);
	long ret = ((WSCdialog*)dlg)->popup();
	if(ret == WS_DIALOG_OK){
		//値を取得
		int index = selectIndex;
		if(index != -1){
			if(index == stockDamages.size() - 1){
				index = -1;
			}
			shrapnelDamageType = index;
			monster_definitions[type].shrapnel_damage.type = shrapnelDamageType;
		}
	}else{
	}
	setupDialog();
}
static WSCfunctionRegister  op("ShapnelTypeBtnDownFunc",(void*)ShapnelTypeBtnDownFunc);

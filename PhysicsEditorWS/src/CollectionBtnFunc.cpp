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
	//�I���_�C�A���O��\��
	WSCbase* dlg = getObject("WSCwindow", "WndSelect");
	//���X�g�Ɍ�����
	//�R���N�V�������X�g
	
	long ret = ((WSCdialog*)dlg)->popup();
	if(ret == WS_DIALOG_OK){
		//�l���擾
		int index = selectIndex;
		
	}else{
	}
}
static WSCfunctionRegister  op("CollectionBtnFunc",(void*)CollectionBtnFunc);

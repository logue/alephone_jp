#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCbaseList.h>
//#include <WSCmessageDialog.h>
#include <WSDkeyboard.h>
#include <WSDMouse.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MouseButtonDownFunc(WSCbase* object){
  //do something...
  //
/*  char* class_name = "WSCmessageDialog"; //���x���N���X
  char* obj_name   = "Messages";     //newvlab_001 �Ƃ�������
  WSCmessageDialog* obj = (WSCmessageDialog*)WSGIappObjectList()->getInstance(class_name,obj_name);

  long ret = obj->popup();
  if(ret == WS_DIALOG_OK){
  }
  */
  //MessageBox(NULL,"piyo","hoge",MB_OK);
	//�}�E�X�J�[�\���ʒu
	WSGIappMouse()->getMousePosition((short*)&nowMousePointX, (short*)&nowMousePointY, object);
	oldMousePointX = nowMousePointX;
	oldMousePointY = nowMousePointY;
	//�ꏏ�ɉ�����Ă���L�[
	long key = WSGIappKeyboard()->getKey();
	if(key == WSK_Control_L || key == WSK_Control_R){
		
	}else{
		//�h��Ԃ�
		WSGIappKeyboard()->setKey(0);
	}
}
static WSCfunctionRegister  op("MouseButtonDownFunc",(void*)MouseButtonDownFunc);

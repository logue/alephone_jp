#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCfileSelect.h>
#include <WSCbaseList.h>
#include <WSCmessageDialog.h>
#include <WSCvdrawingArea.h>

#include <General.h>
#include "map.h"
#include "FileHandler.h"
#include "game_wad.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FileOpenFunc(WSCbase* object){
	//do something...
	//�A�v���P�[�V������1���炩���ߗp�ӂ���Ă��܂��B
	//�t�@�C���I���_�C�A���O�̃C���X�^���X�ɃA�N�Z�X���܂��B
	WSCfileSelect* fs = WSGIappFileSelect(); //(C)
	fs->setProperty(WSNmaskFileName,"");	//(D)
	fs->setProperty(WSNdefaultPosition,True); //(E)
	long ret = fs->popup();									 //(F)

	//�A�v���P�[�V������1���炩���ߗp�ӂ���Ă���
	//���b�Z�[�W�_�C�A���O�̃C���X�^���X���擾����B
	WSCmessageDialog* msg = WSGIappMessageDialog(); //(G)
	msg->setProperty(WSNwidth,500);									//(H)
	msg->setProperty(WSNheight,120);								//(I)
	msg->setProperty(WSNdefaultPosition,True);			//(J)

	if(ret == WS_DIALOG_OK){
		WSCstring str = fs->getFileName();
		char* path = str.getString();
		//load Map
		FileSpecifier fspec = FileSpecifier(path);
		set_map_file(fspec);
		
		initialize_map_for_new_level();
		selectLevel = 0;
		
		bool check = load_level_from_map(selectLevel);
		if(!check){
			msg->setProperty(WSNlabelString,WSCstring("load filure"));
			msg->popup();
		}else{
			msg->setProperty(WSNlabelString,WSCstring("succeeded"));
			msg->popup();
			//redraw
			char* class_name = "WSCvdrawingArea"; //���x���N���X
			char* obj_name   = "MainDrawArea";     //newvlab_001 �Ƃ�������
			WSCvdrawingArea* obj = (WSCvdrawingArea*)WSGIappObjectList()->getInstance(class_name,obj_name);
			obj->redraw();
			//obj->setAbsoluteDraw(True); 
			//obj->draw(); 
		}
	}
}
static WSCfunctionRegister	op("FileOpenFunc",(void*)FileOpenFunc);

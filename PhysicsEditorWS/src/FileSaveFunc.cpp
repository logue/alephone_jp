#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FileSaveFunc(WSCbase* object){
	//�ۑ��_�C�A���O
	//�A�v���P�[�V������1���炩���ߗp�ӂ���Ă��܂��B
	//�t�@�C���I���_�C�A���O�̃C���X�^���X�ɃA�N�Z�X���܂��B
	WSCfileSelect* fs = WSGIappFileSelect(); //(C)
	fs->setProperty(WSNmaskFileName,"");  //(D)
	fs->setProperty(WSNdefaultPosition,True); //(E)
	long ret = fs->popup();                  //(F)
	if(ret == WS_DIALOG_OK){
		//�ۑ�
		WSCstring str = fs->getFileName();
		char buf[1024];
		strcpy(buf, str.getString());
		
		export_definition_structures(str);
	}
}
static WSCfunctionRegister  op("FileSaveFunc",(void*)FileSaveFunc);

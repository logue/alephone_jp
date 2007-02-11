#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCmessageDialog.h>

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FileExitEp(WSCbase* object){
  //do something...
  //exit now
  
 // MessageBox(NULL,"","",MB_OK);
  //�m�F�_�C�A���O
  WSCmessageDialog* msg = WSGIappMessageDialog(); //A
  msg->setProperty(WSNwidth,500);
  msg->setProperty(WSNno,True);
  msg->setProperty(WSNdefaultPosition,True);
  msg->setProperty(WSNlabelString,
    "Exit and save data?\n If you do not want to save and exit,push NO...");
  //�_�C�A���O�̕\��
  long ret = msg->popup(); //B

  if (ret == WS_DIALOG_OK){ //OK�{�^���������ꂽ�ꍇ C
    //saving some data ...
    exit(0);
  }else if( ret == WS_DIALOG_NO){
    exit(0);
  }

}
static WSCfunctionRegister  op("FileExitEp",(void*)FileExitEp);

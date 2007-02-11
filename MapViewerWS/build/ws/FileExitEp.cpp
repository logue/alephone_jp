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
  //確認ダイアログ
  WSCmessageDialog* msg = WSGIappMessageDialog(); //A
  msg->setProperty(WSNwidth,500);
  msg->setProperty(WSNno,True);
  msg->setProperty(WSNdefaultPosition,True);
  msg->setProperty(WSNlabelString,
    "Exit and save data?\n If you do not want to save and exit,push NO...");
  //ダイアログの表示
  long ret = msg->popup(); //B

  if (ret == WS_DIALOG_OK){ //OKボタンがおされた場合 C
    //saving some data ...
    exit(0);
  }else if( ret == WS_DIALOG_NO){
    exit(0);
  }

}
static WSCfunctionRegister  op("FileExitEp",(void*)FileExitEp);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void BtnDefaultMonster01DownFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("BtnDefaultMonster01DownFunc",(void*)BtnDefaultMonster01DownFunc);

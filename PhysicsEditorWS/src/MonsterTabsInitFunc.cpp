#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MonsterTabsInitFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("MonsterTabsInitFunc",(void*)MonsterTabsInitFunc);

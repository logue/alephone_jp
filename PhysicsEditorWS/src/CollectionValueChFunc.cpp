#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void CollectionValueChFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("CollectionValueChFunc",(void*)CollectionValueChFunc);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>
//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void CaarryItemValueChFunc(WSCbase* object){
  //do something...
}
static WSCfunctionRegister  op("CaarryItemValueChFunc",(void*)CaarryItemValueChFunc);

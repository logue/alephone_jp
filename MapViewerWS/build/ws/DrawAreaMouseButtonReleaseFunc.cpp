#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSDkeyboard.h>

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void DrawAreaMouseButtonReleaseFunc(WSCbase* object){
  //do something...
	//“h‚è‚Â‚Ô‚µ
	WSGIappKeyboard()->setKey(0);

}
static WSCfunctionRegister  op("DrawAreaMouseButtonReleaseFunc",(void*)DrawAreaMouseButtonReleaseFunc);

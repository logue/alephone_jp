#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void FileNewEp(WSCbase* object){
  //do something...
  //new file(clear)
  mapNameList.clear();
}
static WSCfunctionRegister  op("FileNewEp",(void*)FileNewEp);

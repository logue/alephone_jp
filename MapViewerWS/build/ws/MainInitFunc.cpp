#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "map.h"
#include "General.h"

std::vector<std::string> mapNameList;
int selectLevel = 0;
int zoomDivision, offsetx, offsety;
int nowMousePointX, nowMousePointY, oldMousePointX, oldMousePointY;

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void MainInitFunc(WSCbase* object){
  //do something...
  //if(dynamic_world == NULL){
    build_trig_tables();
    allocate_map_memory();
  //}
	
	selectLevel = 0;
	mapNameList.clear();
	zoomDivision = ZOOM_DIVISION_DEFAULT;
	offsetx = 0;
	offsety = 0;

	nowMousePointX = 0;
	nowMousePointY = 0;
	oldMousePointX = 0;
	oldMousePointY = 0;
}
static WSCfunctionRegister  op("MainInitFunc",(void*)MainInitFunc);

#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCvdrawingArea.h>

#include <map.h>

#include <HPLLib/HPLAlephLib.h>

#include "General.h"

void getViewPointFromWorldPoint2D(world_point2d& src, int* dest)
{
	hpl::aleph::map::getViewPointFromWorldPoint2D(src, dest,
		OFFSET_X_WORLD, OFFSET_Y_WORLD, zoomDivision, offsetx, offsety);
}

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void OnExpose(WSCbase* object){
	//do something...
	WSCvdrawingArea* drawing_a =
				 (WSCvdrawingArea*)object->cast("WSCvdrawingArea");
	if(drawing_a == NULL){
		return;
	}
	//draw
	drawing_a->setForeColor("#ff0000");
	//drawing_a->drawLine(0,0,100,100);
	
	//lines
	for(int i = 0; i < (int)LineList.size(); i ++){
		line_data* ldata = get_line_data(i);
		endpoint_data* begin = get_endpoint_data(ldata->endpoint_indexes[0]);
		endpoint_data* end = get_endpoint_data(ldata->endpoint_indexes[1]);
		//convert world to view
		int beginPoint[2], endPoint[2];
		getViewPointFromWorldPoint2D(begin->vertex, beginPoint);
		getViewPointFromWorldPoint2D(end->vertex, endPoint);
		
		drawing_a->drawLine(beginPoint[0], beginPoint[1],
			endPoint[0], endPoint[1]);
	}
}
static WSCfunctionRegister	op("OnExpose",(void*)OnExpose);

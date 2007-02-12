#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSDkeyboard.h>
#include <WSDMouse.h>

#include "General.h"

void moveMapOffset(int px, int py){
    int deltaX = px - oldMousePointX;
    int deltaY = py - oldMousePointY;
    offsetx += deltaX;
    offsety += deltaY;
}


//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void DrawAreaMouseMoveFunc(WSCbase* object){
	//マウスカーソル位置
	WSDmouse* mouse = WSGIappMouse();
	
	long status = mouse->getMouseStatus();
	mouse->getMousePosition((short*)&nowMousePointX, (short*)&nowMousePointY, object);
	
	//左ボタンを押している
	if(status & WS_MOUSE_BTN1){
		long key = WSGIappKeyboard()->getKey();
		if(key == WSK_Control_L || key == WSK_Control_R){
			//with control
			//-> move view offset
			moveMapOffset(nowMousePointX, nowMousePointY);
			oldMousePointX = nowMousePointX;
			oldMousePointY = nowMousePointY;
			object->redraw();
		}else{
			WSGIappKeyboard()->setKey(0);
		}
	}else{
	}
}
static WSCfunctionRegister  op("DrawAreaMouseMoveFunc",(void*)DrawAreaMouseMoveFunc);

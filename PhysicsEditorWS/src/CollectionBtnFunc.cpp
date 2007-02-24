#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include <WSCdialog.h>
#include <WSClist.h>

#include "General.h"

//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void CollectionBtnFunc(WSCbase* object){
	int type = selectedMonsterType;
	bool isMax = false;
	int16 collection = monster_definitions[type].collection;
	int16 col = GET_COLLECTION(collection);
	int16 clut = GET_COLLECTION_CLUT(collection);
	int ncol = (int)col;
	long ret = selectFromDialog(&ncol, object, stockCollections, isMax);
	if(ret == WS_DIALOG_OK){
		col = (int16)ncol;
		collection = BUILD_COLLECTION(col, clut);
		monster_definitions[type].collection = collection;
		setupDialog();
	}
}
static WSCfunctionRegister  op("CollectionBtnFunc",(void*)CollectionBtnFunc);

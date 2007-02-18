#include <WScom.h>
#include <WSCfunctionList.h>
#include <WSCbase.h>

#include "General.h"


//----------------------------------------------------------
//Function for the event procedure
//----------------------------------------------------------
void PalletEditValuChFunc(WSCbase* object){
  //do something...
	int type = selectedMonsterType;
	if(type >= 0 && type < NUMBER_OF_MONSTER_TYPES){
		long val = getInteger(object);
		//set
		int16 collection = monster_definitions[type].collection;
		int16 col = GET_COLLECTION(collection);
		int16 clut = GET_COLLECTION_CLUT(collection);
		clut = val;
		monster_definitions[type].collection = BUILD_COLLECTION(col, clut);
		
	}
	//setupDialog();
}
static WSCfunctionRegister  op("PalletEditValuChFunc",(void*)PalletEditValuChFunc);

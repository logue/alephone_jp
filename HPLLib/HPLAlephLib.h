#ifndef _HPL_ALEPH_LIB_
#define _HPL_ALEPH_LIB_

//just for AlephOne
#include "HPLMapTool.h"
#include "HPLSelectData.h"
#include "HPLDoneHistory.h"
#include "HPLViewGridManager.h"

//一般向け
#include "HPLMath.h"
#include "HPLStringModifier.h"
#include "HPLQuickSort.h"
#include "HPLSurfaceModifier.h"

//分類できないもの
namespace hpl{
namespace aleph{
	/**
		vectorの第index番目の要素を削除します
		＊注意！index+1番目以降が全てずれる！
	*/
	template<class T>
	void removeIndexInVector(std::vector<T>* items, int index)
	{
		if(index < 0 || index >= items.size()){
			return;
		}
		std::vector<T>::iterator it = items.begin();
		it += index;
		items.erase(it);
	}
};
};
#endif

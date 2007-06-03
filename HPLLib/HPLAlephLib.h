#ifndef _HPL_ALEPH_LIB_
#define _HPL_ALEPH_LIB_

//just for AlephOne
#include "HPLMapTool.h"
#include "HPLSelectData.h"
#include "HPLDoneHistory.h"
#include "HPLViewGridManager.h"

//��ʌ���
#include "HPLMath.h"
#include "HPLStringModifier.h"
#include "HPLQuickSort.h"
#include "HPLSurfaceModifier.h"

//���ނł��Ȃ�����
namespace hpl{
namespace aleph{
	/**
		vector�̑�index�Ԗڂ̗v�f���폜���܂�
		�����ӁIindex+1�Ԗڈȍ~���S�Ă����I
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

#ifndef _HPL_QUICK_SORT_
#define _HPL_QUICK_SORT_

namespace hpl{
namespace math{
namespace qsort{
    template<class T>
    struct Pair{
        int index;
        T data;
    };
    template<class T>
    void quickSort(Pair<T>* dataArray, int max);
};
};
};
#endif

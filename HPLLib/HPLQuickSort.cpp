#include "HPLQuickSort.h"
#include "HPLMath.h"

/////////////////////////////////////////////////////////////////////////////
//////////////  Static Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/**
    ピボットで得たアクシス数より大きいもの、以下のものをより分けます
    divide [more than axis] and [less than axis]
    -smaller is left, bigger is right
    -return offset of start of biggers
*/
template<class T>
int partition(struct hpl::math::qsort::Pair<T> *dataArray, int start, int end, T axis)
{
    int left = start, right = end;
    while( left <= right){
        while(left <= end && dataArray[left].data < axis)left ++;
        while(right >= start && dataArray[right].data >= axis)right --;
        if(left > right)break;
        //交換
        hpl::math::exchange<struct hpl::math::qsort::Pair<T> >(&dataArray[left], &dataArray[right]);
    }
    return left;
}

/**
    クイックソート用。ピボット交換を行います
    返り値は左から見て異なる数値のうち大きいもののある位置
    select axis-num 
    -find two different nums from indexes' left
    -return bigger one
    -if all nums are equal, return -1
*/
template<class T>
int pivot(struct hpl::math::qsort::Pair<T> *dataArray, int start, int end)
{
    int k = start + 1;
    while( k <= end && dataArray[start].data == dataArray[k].data)k ++;
    //all are same
    if(k > end) return -1;
    //if not
    if(dataArray[start].data >= dataArray[k].data){
        return start;
    }else{
        return k;
    }
}

/**
    クイックソートを求める再起処理部分です
    @param indexes データ
    @param start,end ソート範囲
*/
template<class T>
void repeatbleQuickSort(struct hpl::math::qsort::Pair<T> *dataArray, int start, int end)
{
    if( start == end){
        return;
    }
    int p = pivot(dataArray, start, end);
    if(p != -1){
        int offset = partition(dataArray, start, end, dataArray[p].data);
        repeatbleQuickSort(dataArray, start, offset - 1);
        repeatbleQuickSort(dataArray, offset, end);
    }
}

/////////////////////////////////////////////////////////////////////////////
//////////////  Global Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template<class T>
void hpl::math::qsort::quickSort(struct hpl::math::qsort::Pair<T> *dataArray, int max)
{
    if(max == 1){
        dataArray[0].index = 0;
    }else{
        //init indexes
        for(int i = 0; i < max; i ++){
            dataArray[i].index = i;
        }
        //sort it
        repeatbleQuickSort(dataArray, 0, max);
    }
}

template void hpl::math::qsort::quickSort(struct hpl::math::qsort::Pair<int> *dataArray, int max);
template void hpl::math::qsort::quickSort(struct hpl::math::qsort::Pair<double> *dataArray, int max);

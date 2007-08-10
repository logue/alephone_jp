#include "HPLQuickSort.h"
#include "HPLMath.h"

/////////////////////////////////////////////////////////////////////////////
//////////////  Static Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template<class T>
void exchangePair(struct hpl::math::qsort::Pair<T> *data1, 
                  struct hpl::math::qsort::Pair<T> *data2)
{
    struct hpl::math::qsort::Pair<T> temp;
    temp.index = data1->index;
    temp.data = data1->data;
}
/**
    指定した基準値より大きい物、小さい物で分割します
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
    左から見たとき、最初の値より大きい物がくるか、小さい物が来るかを判定します
    大きい物が来た場合は最初の位置、
    小さい物が来た場合はその場所を基準値のインデックスとします。
    select axis-num 
    -find two different nums from indexes' left
    -return bigger one
    -if all nums are equal, return -1
*/
template<class T>
int pivot(struct hpl::math::qsort::Pair<T> *dataArray, int start, int end)
{
    //startの右隣から始める。startの数値を基準値とする。
    int k = start + 1;

    //startと異なる数値が出るまで調べる
    while( k <= end && dataArray[start].data == dataArray[k].data){
        k ++;
    }
    //全て同じ数字である場合（あるいは要素が一つしかない(end == start)場合）
    if(k > end){
        return -1;
    }

    if(dataArray[start].data >= dataArray[k].data){
        //k番目の値が基準値より大きい場合
        //→基準値の場所を返す（基準値～kは大）
        return start;
    }else{
        //基準値より小さい場合はその場所とする
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
    //ぶつかったら終了
    if( start == end){
        return;
    }
    int p = pivot(dataArray, start, end);

    //pが-1（全て同じ数値か、）
    if(p != -1){
        //指定された基準値を元に分割します
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
        //ソート開始 <en> sort it
        repeatbleQuickSort(dataArray, 0, max - 1);
    }
}

template void hpl::math::qsort::quickSort(struct hpl::math::qsort::Pair<int> *dataArray, int max);
template void hpl::math::qsort::quickSort(struct hpl::math::qsort::Pair<double> *dataArray, int max);

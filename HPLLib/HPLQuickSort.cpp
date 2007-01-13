#include "HPLQuickSort.h"
#include "HPLMath.h"

/**
    クイックソート用。ピボット交換を行います
    返り値は左から見て異なる数値のうち大きいもの
    select axis-num 
    -find two different nums from indexes' left
    -return bigger one
    -if all nums are equal, return -1
*/
static int pivot(int *indexes, int start, int end);

/**
    ピボットで得たアクシス数より大きいもの、以下のものをより分けます
    divide [more than axis] and [less than axis]
    -smaller is left, bigger is right
    -return offset of start of biggers
*/
static int partition(int *indexes, int start, int end, int axis);

/**
    クイックソートを求める再起処理部分です
    @param indexes データ
    @param start,end ソート範囲
*/
static void repeatbleQuickSort(int *indexes, int start, int end);

/////////////////////////////////////////////////////////////////////////////
//////////////  Static Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int partition(int *indexes, int start, int end, int axis)
{
    int left = start, right = end;
    while( left <= right){
        while(left <= end && indexes[left] < axis)left ++;
        while(right >= start && indexes[right] >= axis)right --;
        if(left > right)break;
        hpl::math::exchange(&indexes[left], &indexes[right]);
    }
    return left;
}

int pivot(int *indexes, int start, int end)
{
    int k = start + 1;
    while( k <= end && indexes[start] == indexes[k])k ++;
    //all are same
    if(k > end) return -1;
    //if not
    if(indexes[start] >= indexes[k]){
        return start;
    }else{
        return k;
    }
}

void repeatbleQuickSort(int *indexes, int start, int end)
{
    if( start == end){
        return;
    }
    int p = pivot(indexes, start, end);
    if(p != -1){
        int offset = partition(indexes, start, end, indexes[p]);
        repeatbleQuickSort(indexes, start, offset - 1);
        repeatbleQuickSort(indexes, offset, end);
    }
}

/////////////////////////////////////////////////////////////////////////////
//////////////  Global Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

void hpl::math::qsort::quickSort(int *indexes, int max)
{
    int *temp = new int[max];
    if(max == 1){
        indexes[0] = 0;
    }else{
        //sort it
        repeatbleQuickSort(indexes, 0, max);
    }
    delete temp;
}

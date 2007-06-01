#include "HPLQuickSort.h"
#include "HPLMath.h"

/////////////////////////////////////////////////////////////////////////////
//////////////  Static Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

/**
    �s�{�b�g�œ����A�N�V�X�����傫�����́A�ȉ��̂��̂���蕪���܂�
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
        //����
        hpl::math::exchange<struct hpl::math::qsort::Pair<T> >(&dataArray[left], &dataArray[right]);
    }
    return left;
}

/**
    �N�C�b�N�\�[�g�p�B�s�{�b�g�������s���܂�
    �Ԃ�l�͍����猩�ĈقȂ鐔�l�̂����傫�����̂̂���ʒu
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
    �N�C�b�N�\�[�g�����߂�ċN���������ł�
    @param indexes �f�[�^
    @param start,end �\�[�g�͈�
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

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
        while(left <= end && dataArray[left] < axis)left ++;
        while(right >= start && dataArray[right] >= axis)right --;
        if(left > right)break;
        //����
        hpl::math::exchange<struct hpl::math::qsort::Pair<T>>(&dataArray[left], &dataArray[right]);
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
    while( k <= end && dataArray[start] == dataArray[k])k ++;
    //all are same
    if(k > end) return -1;
    //if not
    if(dataArray[start] >= dataArray[k]){
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
    int p = pivot(dataArray, start, end, destIndexes);
    if(p != -1){
        int offset = partition(dataArray, start, end, dataArray[p]);
        repeatbleQuickSort(dataArray, start, offset - 1, destIndexes);
        repeatbleQuickSort(dataArray, offset, end, destIndexes);
    }
}

/////////////////////////////////////////////////////////////////////////////
//////////////  Global Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

template<class T>
void hpl::math::qsort::quickSort(struct hpl::math::qsort::Pair<T> *dataArray, int max)
{
    if(max == 1){
        destIndexes[0] = (T)0;
    }else{
        //init indexes
        for(int i = 0; i < max; i ++){
            destIndexes[i] = i;
        }
        //sort it
        repeatbleQuickSort(dataArray, 0, max);
    }
}

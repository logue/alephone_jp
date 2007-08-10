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
    �w�肵����l���傫�����A���������ŕ������܂�
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
    �����猩���Ƃ��A�ŏ��̒l���傫���������邩�A�������������邩�𔻒肵�܂�
    �傫�����������ꍇ�͍ŏ��̈ʒu�A
    ���������������ꍇ�͂��̏ꏊ����l�̃C���f�b�N�X�Ƃ��܂��B
    select axis-num 
    -find two different nums from indexes' left
    -return bigger one
    -if all nums are equal, return -1
*/
template<class T>
int pivot(struct hpl::math::qsort::Pair<T> *dataArray, int start, int end)
{
    //start�̉E�ׂ���n�߂�Bstart�̐��l����l�Ƃ���B
    int k = start + 1;

    //start�ƈقȂ鐔�l���o��܂Œ��ׂ�
    while( k <= end && dataArray[start].data == dataArray[k].data){
        k ++;
    }
    //�S�ē��������ł���ꍇ�i���邢�͗v�f��������Ȃ�(end == start)�ꍇ�j
    if(k > end){
        return -1;
    }

    if(dataArray[start].data >= dataArray[k].data){
        //k�Ԗڂ̒l����l���傫���ꍇ
        //����l�̏ꏊ��Ԃ��i��l�`k�͑�j
        return start;
    }else{
        //��l��菬�����ꍇ�͂��̏ꏊ�Ƃ���
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
    //�Ԃ�������I��
    if( start == end){
        return;
    }
    int p = pivot(dataArray, start, end);

    //p��-1�i�S�ē������l���A�j
    if(p != -1){
        //�w�肳�ꂽ��l�����ɕ������܂�
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
        //�\�[�g�J�n <en> sort it
        repeatbleQuickSort(dataArray, 0, max - 1);
    }
}

template void hpl::math::qsort::quickSort(struct hpl::math::qsort::Pair<int> *dataArray, int max);
template void hpl::math::qsort::quickSort(struct hpl::math::qsort::Pair<double> *dataArray, int max);

/*
    <jp> UNDO�̂��߂̍�ƋL�^�ł�
        ���ӓ_�Ƃ��āA������폜�ł͌������f�[�^������ւ��܂�
        NULL�������菇�Ԃ��߂��Ⴍ����ɂȂ�̂��l�����܂��傤
    <en> history of actions you did. this class will be used 
        for undoing

*/
#ifndef _HPL_DONE_HISTORY_
#define _HPL_DONE_HISTORY_

#include <vector>
#include "HPLSelectData.h"
#include "HPLRealMapData.h"

namespace hpl{
namespace aleph{
namespace map{
    namespace ActionType{
        enum{
            Add,
            Delete,
            Modify,
        };
    };
    
    class HPLDoneHistory{
    private:
        //�G�����f�[�^���
        std::vector<HPLSelectData> dataList;

        //�G�������f�[�^�̍T��
        std::vector<HPLRealMapData> realList;
    public:
        HPLDoneHistory();
        ~HPLDoneHistory();

    public:
        /**
            ����ǉ����܂�
        */
        void push_back(HPLSelectData selectData);

        /**
            �Ōォ��index�Ԗڂ̗v�f�����o���܂��B
            �ő�L���ʂ𒴂��Ă�����NULL������Afalse���Ԃ�܂�
        */
        bool getLastIndexOf(int index,
            HPLSelectData* selectData, HPLRealMapData* realData);
    private:
    };
};
};
};

#endif

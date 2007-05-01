/*
    <jp> UNDO�̂��߂̍�ƋL�^�ł�
        ���ӓ_�Ƃ��āA������폜�ł͌������f�[�^������ւ��܂�
        NULL�������菇�Ԃ��߂��Ⴍ����ɂȂ�̂��l�����܂��傤
    <en> history of actions you did. this class will be used 
        for undoing

*/
#ifndef _HPL_DONE_HISTORY_
#define _HPL_DONE_HISTORY_

#include <list>
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
        list<HPLSelectData> dataList;

        //�G�������f�[�^�̍T��
        list<HPLRealMapData> realList;
    public:
        HPLDoneHistory();
        ~HPLDoneHistory();
    };
};
};
};

#endif

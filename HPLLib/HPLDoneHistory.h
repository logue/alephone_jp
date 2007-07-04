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
#include "HPLStockManager.h"

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
    
    /**
        ���[�U�̍s�����s���̂܂Ƃ�
    */
    class HPLActionItem{
    private:
        HPLActionItem(){}
    public:
        HPLActionItem(int t, hpl::aleph::map::HPLSelectData& sel, hpl::aleph::map::HPLRealMapData& real);
        ~HPLActionItem();
        int type;
        hpl::aleph::map::HPLSelectData selectData;
        hpl::aleph::map::HPLRealMapData realData;
    };

    class HPLDoneHistory{
    private:
        std::vector<HPLActionItem> actionList;

        int index;
    public:
        HPLDoneHistory();
        ~HPLDoneHistory();

    public:
        /**
            ����ǉ����܂�
            @param type ActionType�Œ�`���Ă���A���[�U��������s��
        */
        void push_back(int type, HPLSelectData& selectData);

        /**
            index�Ԗڂ̂��̂����o���܂��B
            �ő�L���ʂ𒴂��Ă�����false���Ԃ�܂��B�|�C���^�͖�������܂�
            ���o�����Ƃ��Ă��AselectData��
            �E�ۑ��ɂ���č폜�����s���ꂽ��
            �ɃC���f�b�N�X�l���ω����Ă��܂����߁AupdateIndexes()���ĂԕK�v������
        */
        bool back(int *type, hpl::aleph::map::HPLSelectData* selectData, hpl::aleph::map::HPLRealMapData* realData);

        void forward(int *type, hpl::aleph::map::HPLSelectData* selectData,
            hpl::aleph::map::HPLRealMapData* realData);
        /**
            �C���f�b�N�X�ԍ����폜��̂��̂ɑΉ������܂��B
        */
        void updateIndexes(hpl::aleph::HPLStockManager* smgr);

        int getIndex();
        int getRemainUndoCount();
        int getRemainRedoCount();
    private:
    };
};
};
};

#endif

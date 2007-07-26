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
	/**
		�s���^�C�v
	*/
    namespace ActionType{
        enum{
			//�������Ă��Ȃ����
			//�ړ��O�̏������Ă���
			None,
			//�V�K�쐬
			//�I�u�W�F�N�g�������̂܂ܕێ��B�����ۑ��Ȃǂ��s���C���f�b�N�X����������Ă��܂����ꍇ��
			//�Ō�ɐV�K�ō쐬���꒼�����ƂɂȂ�B
            Add,
			//�폜
			//Add�Ɠ��l
            Delete,
			//�ړ�
			//�ړ��݂̂������A����ɔ��������f�[�^��ێ�
			Move,
			//���̕ύX
			//�����f�[�^�̕ύX�݂̂��s���A�ړ��E�ǉ��E�폜�ɂ��Ă͖���
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
		/**
			@param t �^�C�v ActionType::
			@param sel �I�����Ă�����(�C���f�b�N�X�̂�)
			@param real �I�����Ă��镨�̂̐^�̏��(memcpy�̎Y��)
		*/
        HPLActionItem(int t, hpl::aleph::map::HPLSelectData& sel,
			hpl::aleph::map::HPLRealMapData& real);
        ~HPLActionItem();
        int type;
        hpl::aleph::map::HPLSelectData selectData;
        hpl::aleph::map::HPLRealMapData realData;
    };

    class HPLDoneHistory{
    private:
        std::vector<HPLActionItem> actionList;

        int index;
		int indexMax;
    public:
        HPLDoneHistory();
        ~HPLDoneHistory();

    public:
		/**
			�ő吔��ݒ肵�܂�
		*/
		void setIndexMax(int m);
		int getIndexMax();
        /**
            ����ǉ����܂�
        */
        void push_back(int type, HPLSelectData& selData);

        /**
            index�Ԗڂ̂��̂����o���܂��B
            �ő�L���ʂ𒴂��Ă�����false���Ԃ�܂��B�|�C���^�͖�������܂�
            ���o�����Ƃ��Ă��AselectData��
            �E�ۑ��ɂ���č폜�����s���ꂽ��
            �ɃC���f�b�N�X�l���ω����Ă��܂����߁AupdateIndexes()���ĂԕK�v������
        */
        bool back(int *type, hpl::aleph::map::HPLSelectData* selectData, hpl::aleph::map::HPLRealMapData* realData);

		/**
			���h�D
		*/
        bool forward(int *type, HPLSelectData* selectData, HPLRealMapData* realData);

		/**
			�ŐV�ł̏�Ԃ��擾���܂�
			�擾���Ă����e��ʒu�͕ω������܂���
		*/
		bool getTail(int *type, HPLSelectData* sel, HPLRealMapData* real);

        /**
            �C���f�b�N�X�ԍ����폜��̂��̂ɑΉ������܂��B
        */
        void updateIndexes(hpl::aleph::HPLStockManager* smgr);

		/**
			���������܂�
		*/
		void init();

        int getIndex();
        int getRemainUndoCount();
        int getRemainRedoCount();
    private:
    };
};
};
};

#endif

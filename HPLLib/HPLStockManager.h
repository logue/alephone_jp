/***************************************************
	�}�b�v�f�[�^�ɂ��Ă̏���~���Ă����N���X
	�E�|���S���̐��������
	�E�폜�\��̃}�b�v�A�C�e��
	�ETODO �I������Ă���A�C�e�� NEW!
***************************************************/
#ifndef _HPL_STOCK_MANAGER_
#define _HPL_STOCK_MANAGER_

#include <vector>
//#include <set>

#include "HPLSelectData.h"

namespace hpl{
namespace aleph{
    class HPLStockManager{
    public:
        /**�|���S���̐�����*/
        std::vector<bool> polygonValidity;

        //�|���S�����������ɕ\������ۂ̏���
        //TODO poly height order
        std::vector<int> polygonDrawOrderByHeight;

        //���̏��Ԃ��������ɂ�������
        //TODO
		std::vector<int> lineDrawOrderByHeight;

		//�v�f�̍폜���
        std::vector<bool> delPoints;
        std::vector<bool> delLines;
        std::vector<bool> delPolygons;
        std::vector<bool> delSides;
        std::vector<bool> delObjects;
		//platform
		std::vector<bool> delPlatforms;
		//light/media

		//�I�������v�f�̏��
		std::vector<bool> selPoints;
        std::vector<bool> selLines;
        std::vector<bool> selPolygons;
        std::vector<bool> selSides;
        std::vector<bool> selObjects;
    public:
        HPLStockManager();
        ~HPLStockManager();

        //////////////////////////
        // �|���S��������
        //�|���S�������������ǂ������������܂�(������)
        bool isPolygonValidityStored(int polyIndex);

        //�|���S�������������X�V���܂�
        void updatePolygonValidityStored();

        /**
            �T�C�Y�����ۂ̂��̂ɍ��킹�܂�
        */
        void resizeDeletes();

        //�폜�Ώۂ̊o������
        //hpl::aleph::map::HPLSelectData toDeleteList;

        /**
            �폜�����X�V���܂��B
            ��̓I�ɂ�dynamic_world�̒l�ɍ��킹�ėv�f���𑝉������܂�
            �������͍폜�Ώۂł͂Ȃ��̂ł��ׂ�false�ł��B
        */
        void updateDeletes();
        
        /**
            �폜����������
            ���ۂɂ�clear�������daupteDeletes()���Ă�ł邾��
        */
        void resetDeletes();

		/**
			�I�������X�V
		*/
		void updateSelects(hpl::aleph::map::HPLSelectData& sel);

		/**
			�w�肵���A�C�e�����폜
		*/
        bool deletePoint(int index);
        bool deleteLine(int index);
        bool deletePolygon(int index);
        bool deleteSide(int index);
        bool deleteObject(int index);
		bool deletePlatform(int index);

		/**
			�I�����̎擾
		*/
		bool isSelectPoint(int index);
		bool isSelectLine(int index);
		bool isSelectPolygon(int index);
		bool isSelectSide(int index);
		bool isSelectObject(int index);
    };
};
};

#endif

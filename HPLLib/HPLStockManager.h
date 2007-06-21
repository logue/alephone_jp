#ifndef _HPL_STOCK_MANAGER_
#define _HPL_STOCK_MANAGER_

#include <vector>
//#include <set>

#include "HPLSelectData.h"

namespace hpl{
namespace aleph{
    /**
        �}�b�v�f�[�^�ɂ��Ă̏���~���Ă����N���X
        �E�|���S���̐��������
        �E�폜�\��̃}�b�v�A�C�e��
    */
    class HPLStockManager{
    private:
        /**�|���S���̐�����*/
        std::vector<bool> polygonValidity;

        //�|���S�����������ɕ\������ۂ̏���
        //TODO poly height order
        std::vector<int> polygonDrawOrderByHeight;

        //���̏��Ԃ��������ɂ�������
        //TODO

        std::vector<bool> delPoints;
        std::vector<bool> delLines;
        std::vector<bool> delPolygons;
        std::vector<bool> delSides;
        std::vector<bool> delObjects;
    public:
        HPLStockManager();
        ~HPLStockManager();

        //////////////////////////
        // �|���S��������
        //�|���S�������������ǂ������������܂�(������)
        bool isPolygonValidityStored(int polyIndex);

        //�|���S�������������X�V���܂�
        void updatePolygonValidityStored();

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

        bool deletePoint(int index);
        bool deleteLine(int index);
        bool deletePolygon(int index);
        bool deleteSide(int index);
        bool deleteObject(int index);

    };
};
};

#endif

/*
    ���f�[�^�̍T���ł��B
    UNDO�p�ł�

*/
#ifndef _HPL_REAL_MAP_DATA_
#define _HPL_REAL_MAP_DATA_

#include <map>

#include "map.h"

#include "HPLSelectData.h"

namespace hpl{
namespace aleph{
namespace map{
    class HPLRealMapData{
    private:
        //���O�����Ԃ�܂���̂ň����ɒ��ӁB
        //<en> names of field are all duplicated to 
        // ones in AlephOne's original codes.
        //�_�f�[�^<index, data_structure>
        std::map<int, endpoint_data> realPoints;
        //�I�u�W�F�N�g�f�[�^
        std::map<int, map_object> realObjects;
        //���f�[�^
        std::map<int, line_data> realLines;
        //�T�C�h�f�[�^
        std::map<int, side_data> realSides;
        //�|���S���f�[�^
        std::map<int, polygon_data> realPolygons;
    public:
        HPLRealMapData();
        ~HPLRealMapData();

    public:
        //�R�s�[�Ώۂ̃}�b�v�f�[�^(�I�𕔕�)
        void set(hpl::aleph::map::HPLSelectData* copyTargetData);
        std::map<int, map_object>* getObjects();
        std::map<int, endpoint_data>* getPoints();
        std::map<int, line_data>* getLines();
        std::map<int, polygon_data>* getPolygons();
        std::map<int, side_data>* getSides();

    private:
        void addObject(int index);
        void addPoint(int index);
        void addLine(int index);
        void addSide(int index);
        void addPolygon(int index);
        //��������f�[�^�������܂�
        void removeAll();

    };


};
};
};
#endif

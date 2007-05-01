/*
    ���f�[�^�̍T���ł��B
    UNDO�p�ł�

*/
#ifndef _HPL_REAL_MAP_DATA_
#define _HPL_REAL_MAP_DATA_

#include <map>

namespace hpl{
namespace aleph{
namespace map{
    class HPLRealMapData{
    private:
        //���O�����Ԃ�܂���̂ň����ɒ��ӁB
        //<en> names of field are all duplicated to 
        // ones in AlephOne's original codes.
        //�_�f�[�^<index, data_structure>
        std::map<int, endpoint_data> points;
        //�I�u�W�F�N�g�f�[�^
        std::map<int, map_object> objects;
        //���f�[�^
        std::map<int, line_data> lines;
        //�T�C�h�f�[�^
        std::map<int, side_date> sides;
        //�|���S���f�[�^
        std::map<int, polygon_data> polygons;
    public:
        HPLRealMapData();
        ~HPLRealMapData();
    };
};
};
};
#endif

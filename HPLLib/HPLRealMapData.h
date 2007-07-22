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
        //�_�f�[�^<data_structure>
        std::vector<endpoint_data> realPoints;
        //�I�u�W�F�N�g�f�[�^
        std::vector<map_object> realObjects;
        //���f�[�^
        std::vector<line_data> realLines;
        //�T�C�h�f�[�^
        std::vector<side_data> realSides;
        //�|���S���f�[�^
        std::vector<polygon_data> realPolygons;
    public:
        HPLRealMapData();
        ~HPLRealMapData();

    public:
        //�R�s�[�Ώۂ̃}�b�v�f�[�^(�I�𕔕�)
        void set(hpl::aleph::map::HPLSelectData& copyTargetData);
        std::vector<map_object>* getObjects();
        std::vector<endpoint_data>* getPoints();
        std::vector<line_data>* getLines();
        std::vector<polygon_data>* getPolygons();
        std::vector<side_data>* getSides();

		//�f�[�^�����݂��邩�m���߂܂�
		bool isEmpty();
        //��������f�[�^�������܂�
        void removeAll();

	private:
        void addObject(int index, std::map<int, int>& objectIndexMap);
        void addPoint(int index, std::map<int, int>& pointIndexMap);
        void addLine(int index, std::map<int, int>& lineIndexMap
											  , std::map<int, int>& pointIndexMap);
        void addPolygon(int index, std::map<int, int>& polygonIndexMap,
												 std::map<int, int>& lineIndexMap,
												 std::map<int, int>& pointIndexMap,
												 std::map<int, int>& sideIndexMap);
        void addSide(int index, std::map<int, int>& sideIndexMap);

/*		bool containsPoint(int index);
		bool containsLine(int index);
		*/
    };


};
};
};
#endif

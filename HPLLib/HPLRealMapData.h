/*
    実データの控えです。
    UNDO用です

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
        //点データ<data_structure>
        std::vector<endpoint_data> realPoints;
        //オブジェクトデータ
        std::vector<map_object> realObjects;
        //線データ
        std::vector<line_data> realLines;
        //サイドデータ
        std::vector<side_data> realSides;
        //ポリゴンデータ
        std::vector<polygon_data> realPolygons;
    public:
        HPLRealMapData();
        ~HPLRealMapData();

    public:
        //コピー対象のマップデータ(選択部分)
        void set(hpl::aleph::map::HPLSelectData& copyTargetData);
        std::vector<map_object>* getObjects();
        std::vector<endpoint_data>* getPoints();
        std::vector<line_data>* getLines();
        std::vector<polygon_data>* getPolygons();
        std::vector<side_data>* getSides();

		//データが存在するか確かめます
		bool isEmpty();
        //所持するデータを消します
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

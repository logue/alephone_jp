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
        //名前がかぶりまくるので扱いに注意。
        //<en> names of field are all duplicated to 
        // ones in AlephOne's original codes.
        //点データ<index, data_structure>
        std::map<int, endpoint_data> realPoints;
        //オブジェクトデータ
        std::map<int, map_object> realObjects;
        //線データ
        std::map<int, line_data> realLines;
        //サイドデータ
        std::map<int, side_data> realSides;
        //ポリゴンデータ
        std::map<int, polygon_data> realPolygons;
    public:
        HPLRealMapData();
        ~HPLRealMapData();

    public:
        //コピー対象のマップデータ(選択部分)
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
        //所持するデータを消します
        void removeAll();

    };


};
};
};
#endif

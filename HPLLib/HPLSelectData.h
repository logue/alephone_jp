/****************************************
    <jp>選択情報。コピー＆ペーストにも利用可能？
    <en>select
****************************************/
#ifndef _HPL_SELECT_DATA_
#define _HPL_SELECT_DATA_

#include "AlephOne/map.h"
#include "AlephOne/wad.h"
#include <vector>

namespace hpl{
namespace aleph{
namespace map{
    struct SelPoint{
        int index;
        int offset[2];
    };
    struct SelLine{
        int index;
        int offset[2][2];
    };
    struct SelPolygon{
        int index;
        int offset[8][2];
        int num;
    };
    struct SelObject{
        int index;
        int offset[2];
    };
    struct SelSide{
        int index;
    };
    class HPLSelectData{
    private:
        std::vector<struct SelPoint> selpoints;
        std::vector<struct SelLine> sellines;
        std::vector<struct SelPolygon> selpolygons;
        std::vector<struct SelObject> selobjects;
        struct SelSide side;
        bool _isSelected;
    public:
        HPLSelectData();
        ~HPLSelectData();
    public:
        //中身をそのまま取得。あまり使わないほうが良い
        std::vector<struct SelPoint>* getSelPoints();
        std::vector<struct SelLine>* getSelLines();
        std::vector<struct SelPolygon>* getSelPolygons();
        std::vector<struct SelObject>* getSelObjects();
        struct SelSide* getSelSide();

        bool containsPoint(int index);
        bool containsLine(int index);
        bool containsPolygon(int index);
        bool containsObject(int index);
        bool isSelectSide(int index);

        bool isSelected();
        void setSelected(bool sel);

        //clear all selecting informatins
        void clear();
        
        bool isSelectOnePoint();
        bool isSelectOneLine();
        bool isSelectOnePolygon();
        bool isSelectOneObject();
        bool isSelectOneSide();

        void addSelPoint(int index, int offset[2]);
        void addSelLine(int index, int offset[2][2]);
        void addSelPolygon(int index, int offset[8][2], int num);
        void addSelObject(int index, int offset[2]);
        void addSelSide(int index);
    };
};
};
};
#endif

/****************************************
    <jp>選択情報。コピー＆ペーストにも利用可能？
    <en>select
****************************************/
#ifndef _HPL_SELECT_DATA_
#define _HPL_SELECT_DATA_

#include "map.h"
#include "wad.h"
#include <vector>
//#include <set>

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
	struct SelAnnotation{
		int index;
		int offset[2];
	};
    class HPLSelectData{
    private:
        std::vector<struct SelPoint> selpoints;
        std::vector<struct SelLine> sellines;
        std::vector<struct SelPolygon> selpolygons;
        std::vector<struct SelObject> selobjects;
        std::vector<struct SelSide> selsides;
		std::vector<struct SelAnnotation> selannotations;
        struct SelSide side;
        bool _isSelected;
		int mx, my;
    public:
        HPLSelectData();
        ~HPLSelectData();
    public:
		//マウス座標
		void setMousePosition(int x, int y);
		void getMousePosition(int point[2]);

        //中身をそのまま取得。あまり使わないほうが良い
        std::vector<struct SelPoint>* getSelPoints();
        std::vector<struct SelLine>* getSelLines();
        std::vector<struct SelPolygon>* getSelPolygons();
        std::vector<struct SelObject>* getSelObjects();
        std::vector<struct SelSide>* getSelSides();
        std::vector<struct SelAnnotation>* getSelAnnotations();
        struct SelSide* getSelSide();

        bool containsPoint(int index);
        bool containsLine(int index);
        bool containsPolygon(int index);
        bool containsObject(int index);
        bool containsSide(int index);
        bool containsAnnotation(int index);
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
        bool isSelectOneAnnotation();

        void addSelPoint(int index, int offset[2]);
        void addSelLine(int index, int offset[2][2]);
        void addSelPolygon(int index, int offset[8][2], int num);
        void addSelObject(int index, int offset[2]);
        void addSelSide(int index);
        void addSelAnnotation(int index, int offset[2]);
    };
};
};
};
#endif

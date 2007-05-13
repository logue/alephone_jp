/**
    標準で準備されたポリゴン情報
    a polygon information which is preset
*/
#ifndef _PRESET_POLYGON_
#define _PRESET_POLYGON_

namespace mapeditorone{
    class PresetPolygon{
    private:

        /**
            頂点の数
            the number of edges
        */
        int num;

    public:
        /**
            頂点の数を指定して生成
            @param n the number of edges
        */
        PresetPolygon(int n);
        ~PresetPolygon();

        /**
            範囲指定からポリゴン座標を得ます
        */
        void getPoints(int x0, int y0, int x1, int y1, int *dest);
    };
};
#endif

#ifndef _HPL_MAP_TOOL_
#define _HPL_MAP_TOOL_

#include <math.h>
#include <vector>
#include <map>

#include "map.h"
#include "wad.h"

//#include "HPLMath.h"
#include "HPLSelectData.h"

namespace hpl{
namespace aleph{
namespace map{

    ///////////////////////////////////////////////////////////////////////
    ///////////  Points  //////////////////////////////////////////////////
    /**
        <jp>指定した点をクリックできているかの判定を行います。
        <en>is view-point near world-point?
        @param viewPX   point(mouse/view)       ビュー座標（スクリーン座標）
        @param worldPX  point(world)            対象とする点（実座標）
        @param offsetViewX offset of view       ビュー座標のズレ
        @param offsetWorldX offset of world     実座標のズレ
        @param distance check distance          閾値
    */
    bool isSelectPoint(int viewPX, int viewPY, 
                       int worldPX, int worldPY,
                       int offsetViewX, int offsetViewY,
                       int offsetWorldX, int offsetWorldY,
                       int div,
                       int distance);
    bool isSelectPoint(world_point2d &point0, world_point2d &point1,
                       int distance);

    ///////////////////////  Lines  ////////////////////////////////////////////
    /**
        指定した点を用いたときに線を選択できているかを判定
        is view-point near world-line?
        @param viewPX   point(mouse/view)
        @param worldPX0 line's point(world)
        @param offsetViewX offset of view
        @param offsetWorldX offset of world
        @param distance check distance
    */
    bool isSelectLine(int viewPX, int viewPY,
                       int worldPX0, int worldPY0,
                       int worldPX1, int worldPY1,
                       int offsetViewX, int offsetViewY,
                       int offsetWorldX, int offsetWorldY,
                       int div,
                       int distance);

    bool isSelectLine(world_point2d &point,
                      world_point2d &linePoint0, world_point2d &linePoint1,
                      int distance);

    /**
        線の長さを取得
        @param index 線データのインデックス
    */
    double getLineLength(int index);
    /*
        線の長さを得る
    */
    double getLength(world_point2d& pointA, world_point2d& pointB);

    ///////////////////////////////////////////////////////////////////////
    ///////////  Groups  //////////////////////////////////////////////////
    /**
        マウスが既に選択されているアイテムをクリックしているか確かめます
        <en>is point in select groups?
        @param px point locatin(view)               マウス位置（ビュー座標）
        @param offsetViewX offset(view)             ビュー座標ズレ
        @param offsetWorldX offset(world)           実座標
        @param pointDistance distance as nearby     点用閾値
        @param lineDistance distance as nearby      線用閾値
        @param selectInfo select group for check    グループクラス
    */
    bool isPointInSelection(int px, int py,
                            int offsetViewX, int offsetViewY,
                            int offsetWorldX, int offsetWorldY,
                            int pointDistance,
                            int lineDistance,
                            int objectDistance,
                            hpl::aleph::map::HPLSelectData* selectInfo,
                            int heightMax, int heightMin, int div);

};
};
};
#endif

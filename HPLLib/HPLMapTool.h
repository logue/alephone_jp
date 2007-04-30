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
	///////////	 Points	 //////////////////////////////////////////////////
	/**
		<jp>指定した点をクリックできているかの判定を行います。
		<en>is view-point near world-point?
		@param viewPX	point(mouse/view)		ビュー座標（スクリーン座標）
		@param worldPX	point(world)			対象とする点（実座標）
		@param offsetViewX offset of view		ビュー座標のズレ
		@param offsetWorldX offset of world		実座標のズレ
		@param distance check distance			閾値
	*/
	bool isSelectPoint(int viewPX, int viewPY, 
					   int worldPX, int worldPY,
					   int offsetViewX, int offsetViewY,
					   int offsetWorldX, int offsetWorldY,
					   int div,
					   int distance);
	bool isSelectPoint(world_point2d &point0, world_point2d &point1,
					   int distance);
	
	/**
		<jp>指定した点をグリッドに合わせ、その座標を得ます
		<en>snap point to grid
		@param srcPoint
		@param destPoint snapped point			グリッドに合わされた点座標
		@param gridInterval interval of grids	グリッド間隔
	*/
	void getSnapedPointToGrid(world_point2d &srcPoint, world_point2d* destPoint,
		int gridInterval);

	/**
		<jp>指定した点、および点を所有する線とポリゴンが正しいかどうか判定?
	*/
//	  bool isValidPoint(int index);

	//convert view <-> world point
	world_point2d getWorldPoint2DFromViewPoint(int viewPX, int viewPY,
	int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety);
	void getViewPointFromWorldPoint2D(world_point2d& point, int *dest,
	int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety);

	///////////////////////	 Lines	////////////////////////////////////////////
	/**
		指定した点を用いたときに線を選択できているかを判定
		is view-point near world-line?
		@param viewPX	point(mouse/view)
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
	double getPointsDistance(world_point2d& pointA, world_point2d& pointB);

	/**
		<jp>線情報を更新する
		<en>Fix line_data up
		@param isDeleteOldSide descide which deletes or not 使われていない壁情報を削除するか
	*/
	void fixLine(int index, bool isDeleteOldSide);

	////////////////////////////////////////////////////////////////////////
	///////////	 Sides	////////////////////////////////////////////////////

	void fixSide(int leftPolyIndex, int rightPolyIndex, int sideIndex,
		int lineIndex, bool isDeleteOldSide);

	///////////////////////////////////////////////////////////////////////
	///////////	 Groups	 //////////////////////////////////////////////////
	/**
		マウスが既に選択されているアイテムをクリックしているか確かめます
		<en>is point in select groups?
		@param px point locatin(view)				マウス位置（ビュー座標）
		@param offsetViewX offset(view)				ビュー座標ズレ
		@param offsetWorldX offset(world)			実座標
		@param pointDistance distance as nearby		点用閾値
		@param lineDistance distance as nearby		線用閾値
		@param selectInfo select group for check	グループクラス
	*/
	bool isPointInSelection(int px, int py,
							int offsetViewX, int offsetViewY,
							int offsetWorldX, int offsetWorldY,
							int pointDistance,
							int lineDistance,
							int objectDistance,
							hpl::aleph::map::HPLSelectData* selectInfo,
							int heightMax, int heightMin, int div);

    ///////////////////////////////////////////////////////////////////////////////
    ////// Polygon ////////////////////////////////////////////////////////////////

    /**
        ポリゴンが存在として正しいかどうかを判定します
        @param index index of polygon which is checked 検査対象のポリゴンインデックス
    */
    bool isValidPolygon(int index);

    /**
        ポリゴンをセットアップします
        具体的には、
        ・点の順番、線の順番を時計回りに整えます
        ・Sideデータ等を設定します
        ・
    */
    //void setupPolygon(int index);
};
};
};
#endif

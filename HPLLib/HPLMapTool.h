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
		<jp>指定した点をクリックしたかどうかの判定を行います
		<en>is view-point near world-point?
		@param viewPX	point(mouse/view)		    ビュー座標（スクリーン座標）
		@param worldPX	point(world)			    検査対象とする点（実座標）
		@param offsetViewX offset of view		    ビュー座標のズレ
		@param offsetWorldX offset of world		    実座標のズレ
		@param distance check distance threshold    閾値
	*/
	bool isSelectPoint(int viewPX, int viewPY, 
					   int worldPX, int worldPY,
					   int offsetViewX, int offsetViewY,
					   int offsetWorldX, int offsetWorldY,
					   int div,
					   int distance);
    /**
        <jp>指定した点(point1)をマウスの座標(point0)がクリックしたかどうかを判定します
        <en>check which two world-points are near or not
        @param point0 world-point0  点
        @param point1 world-point1  点
        @param distance threshold   閾値
    */
	bool isSelectPoint(world_point2d &point0, world_point2d &point1,
					   int distance);
	
	/**
		<jp>指定した点をグリッドに合わせ、その座標を得ます
		<en>snap point to grid
		@param srcPoint                         元の座標
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
		@param offsetViewX offset of view                       view座標のズレ
		@param offsetWorldX offset of world                     world座標のズレ（中心位置）
		@param distance distance threshold which grab or not    近いかどうかの閾値
        @return true when mouse can grab line                   線を選択できていればtrue
	*/
	bool isSelectLine(int viewPX, int viewPY,
					   int worldPX0, int worldPY0,
					   int worldPX1, int worldPY1,
					   int offsetViewX, int offsetViewY,
					   int offsetWorldX, int offsetWorldY,
					   int div,
					   int distance);

    /**
        <jp>線を選択できているか判断
        <en>check which mouse grob line
        @param point mouse location in view
        @param linePoint0
        @param linePoint1 line's location in world
        @param distance distance threshold which grab or not
        @return true when mouse can grab line
    */
	bool isSelectLine(world_point2d &point,
					  world_point2d &linePoint0, world_point2d &linePoint1,
					  int distance);

	/**
		線の長さを取得
        get line's length (calc length, not get from its structure::length)
		@param index 線データのインデックス
        @return line(index)'s length
	*/
	double getLineLength(int index);

	/*
		線の長さを得る
        get line's length from two world points
        
	*/
	double getPointsDistance(world_point2d& pointA, world_point2d& pointB);

	/**
		<jp>線情報を更新する
		<en>Fix line_data up
        1:calc length
        2:set side
		@param isDeleteOldSide descide which deletes or not 使われていない壁情報を削除するか
	*/
	void fixLine(int index, bool isDeleteOldSide);

    /**
        線情報を線を構成する点によって取得します
        get line index with two point indexes
        @return 線が存在しない場合NONE
    */
    int getLineIndexFromTwoLPoints(int pindex0, int pindex1);

	/**
		点を共有する線インデックスのリストを取得します
	*/
	std::vector<int> getLineIndexesIncludePoint(int endpointIndex);

	/**
		線を共有するポリゴンのリストを取得します
		line_dataには右側ポリゴンと左側ポリゴンのインデックスが入ってるのでそれを活用してもいい
		** それ使えば良いじゃん…
	*
	std::vector<int> getPolygonIndexesIncludeLine(int lineIndex);
	*/
	/**
		点を共有するポリゴンのリストを取得します
	*/
	std::vector<int> getPolygonIndexesIncludePoint(int endpointIndex);
	////////////////////////////////////////////////////////////////////////
	///////////	 Sides	////////////////////////////////////////////////////

    /**
        <jp>壁情報をセットアップします
        <en>
    */
	void fixSide(int sideIndex);

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
        座標を取り囲むポリゴンのうち、ポリゴンとして成立しているものをさがします
        すでにポリゴンが存在している場合は無視します
        @param wpoint 探索基点。ここを囲むポリゴンを探す
        @return ポリゴンの実データ候補。これを元に生成すると良い。データはcreatePolygonで生成すべし
    */
    std::vector<polygon_data> searchValidPolygon(world_point2d wpoint);

    /**
        二つの線が織り成す角度を求めます
        @param pIndexA1,2 線分A1-A2の点インデックス
        @param pIndexB1,2 線分B1-B2の点インデックス
    */
    double getTwoLinesDegree(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);
    double getTwoLinesRadian(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);

    /**
        ポリゴンデータを作ります
        TODO
    */
    polygon_data createPolygon(int epindexes[8]);

    /**
        世界座標からポリゴンデータを作ります
        TODO 整合性
        @param points 世界座標
        @param ep 生成された点データ
        @param ld 生成された線データ
        @param n n角形
    */
    polygon_data createPolygon(world_point2d points[], endpoint_data epd[], line_data ld[],
        int n);

//    void addNewPoint(endpoint_data point);


    /**
        ポリゴンをセットアップします
        具体的には、
        ・点の順番、線の順番を時計回りに整えます
        ・Sideデータ等を設定します
        ・
    */
    //void setupPolygon(int index);

    /**
        指定した点がポリゴンの中に存在するかどうかを確かめます
        @
    */
    bool isPointInPolygon(int viewPX, int viewPY, int polygonIndex,
        int offsetXWorld, int offsetYWorld, int zoomDivision, int offsetx, int offsety);
    bool isPointInPolygon(world_point2d& wpoint, int polygonIndex);

    ///////////////////////////////////////////////////////////////////////////////
    ////////// add delete modify it /////////////////////////////////////////////////
	/**
		点情報を追加します
		@param ep 追加する点データ（値渡しなのでコピーされます）
		@return 追加された点のインデックス値
	*/
	int addEndpoint(endpoint_data ep);
	int addLine(line_data line);
	int addSide(side_data side);
	int addPolygon(polygon_data polygon);
	int addMapSavedObject(map_object object);
	int addAnnotation(map_annotation annotation);

	/**
		点情報を削除します
		@param index 削除対象のインデックス
		@return 削除失敗時に偽。インデックスが正しくない場合など
	*/
	bool deleteEndpoint(int index);
	bool deleteLine(int index);
	bool deleteSide(int index);
	bool deletePolygon(int index);
	bool deleteMapSavedObject(int index);

    /**
        ポリゴン情報を修正します
        TODO
    */
    void fixPolygon(int pindex);

    /**
        独立したポリゴンデータを追加します
		ポリゴンデータやポイントデータなどから実際に追加します
    */
    void addNewPolygon(polygon_data& pdata, endpoint_data epd[], line_data ld[], int n);
    void addNewPolygon(world_distance points[][2], int n);
    void addNewPolygon(world_point2d points[], int n);

	////////////////////////////////////////////////
	////// objects ////////////////////////////////
	/**
		初期配置数の設定
		@param objectType オブジェクトタイプ
			_saved_item
			_saved_monster
		@param index どのオブジェクトの初期は位置をいじるか
		@param num 増減させる値
		@return 増減の結果の数。配置情報が得られない場合NONE(負数)
	*/
	int addInitialPlacementNum(int objectType, int index, int num);
	/**
		配置情報を取得
		@param objectType オブジェクトタイプ
			_saved_item
			_saved_monster
		@param index どのオブジェクトの初期は位置をいじるか
		@return 配置情報。配置数やランダムマックスなど
			取得できない場合はNULLが返されます
	*/
	struct object_frequency_definition* getPlacementData(int objectType, int index);

};
};
};
#endif

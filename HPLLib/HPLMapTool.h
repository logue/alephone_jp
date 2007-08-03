#ifndef _HPL_MAP_TOOL_
#define _HPL_MAP_TOOL_

#include <math.h>
#include <vector>
#include <map>
#include <string>
#include <set>

#include "map.h"
#include "wad.h"

//#include "HPLMath.h"
#include "HPLSelectData.h"
//#include "HPLStockManager.h"
#include "HPLError.h"


#ifdef __WXDEBUG__
#include <wx/defs.h>
#include <wx/debug.h>
#endif

namespace hpl{namespace aleph{
class HPLStockManager;
}};

/*
const int NUMBER_OF_POLYGON_TYPE = 24;
const int NUMBER_OF_ZOOM_DIVISION = 3;
const int NUMBER_OF_OBJECT_TYPES = 6;
const int NUMBER_OF_ACTIVATE_TYPES = 4;
const int NUMBER_OF_MAP_OBJECT_TYPES = 6;
*/


//分類できないもの
namespace hpl{
namespace aleph{
    //名称
    typedef struct Information_tag{
        std::string jname;
    }Information;

    //値つき名称
    typedef struct InformationBinded_tag{
        std::string jname;
        int bind;
    }InformationBinded;

    /**
        タグデータ文字列を取得します
        load data strings from file
        @param filePath ファイルパス file path
        @param maxLines 最大行数
        @param infos 出力
    */
    void loadInformation(const char* filePath, int maxLines, hpl::aleph::Information infos[]);

	/**
		指定した値に相当するインデックス値を取得します
		存在しないなどの理由により失敗した場合は、負数が返されます
	*/
	int getIndexFromInformationBinded(int value, hpl::aleph::InformationBinded infos[], int max);
	/**
		バインド型の文字列だけをファイルから読み込みます。
		割り当て番号は設定されません
	*/
	void loadInformation(const char* filePath, int maxLines, hpl::aleph::InformationBinded infos[]);

    /**
        カラーデータをファイルから読み込みます
        @return 失敗時に偽
    */
    bool loadColorSetting(const char* filePath, int colors[][3], int max);

    /**
		vectorの第index番目の要素を削除します
		＊注意！index+1番目以降が全てずれる！
	*/
	template<class T>
	void removeIndexInVector(std::vector<T>* items, int index)
	{
		if(index < 0 || index >= (int)items->size()){
			return;
		}
		std::vector<T>::iterator it = items->begin();
		it += index;
		items->erase(it);
	}
};
};

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

    /**
        指定した場所に点があるかどうかを得ます
        @param wpoint ワールド座標の点
        @param threshold 点との距離がこれ以下ならば近いと見なす。View座標系の距離を指定する
        @param zMin, zMax 高さチェック用
        @return その場所に点があればそのインデックスがかえります。
            なければNONE
    */
    int getSelectPointIndex(world_point2d& wpoint, int threshold,
        int zMin, int zMax, int div,
                                        hpl::aleph::HPLStockManager* smgr);
    int getSelectPointIndex(int viewX, int viewY, int threshold, int zMin, int zMax,
        int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
                                        hpl::aleph::HPLStockManager* smgr);

    /**
        ある高さが規定範囲内にあるかを確かめます
        @return ある高度の範囲が規定範囲と共有する部分を持たない場合負
    */
    bool isValidHeight(int checkMin, int checkMax, int validMin, int validMax);

    /**
        指定した点が線を踏んでいる場合、その線番号を返します
    */
    int getSelectLineIndex(world_point2d& wpoint, int threshold, int zMin, int zMax, int div,
                                        hpl::aleph::HPLStockManager* smgr);
    int getSelectLineIndex(int viewX, int viewY, int threshold, int zMin, int zMax,
        int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
                                        hpl::aleph::HPLStockManager* smgr);

	/**
		指定した点がポリゴンを踏んでいる場合、そのポリゴンを返します
	*/
	int getSelectPolygonIndex(int viewX, int viewY, int zMin, int zMax,
		int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
		hpl::aleph::HPLStockManager* smgr);

	/**
		選択できたアノテーションのインデックスを取得します
	*/
	int getSelectAnnotationIndex(int viewX, int viewY, int threshold, int zMin, int zMax,
        int voffsetX, int voffsetY, int offsetXW, int offsetYW, int div,
                                        hpl::aleph::HPLStockManager* smgr);
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
					  int distance, int div);

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
	void fixLine(int index,// bool isDeleteOldSide,
		hpl::aleph::HPLStockManager* smgr);
	/**
        ポリゴン情報を修正します
    */
    void fixPolygon(int pindex,
		hpl::aleph::HPLStockManager* smgr);

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

    /**
        ポリゴンに乗っているオブジェクトのインデックスを取得します
    */
    std::vector<int> getObjectIndexesOnPolygon(int polygonIndex);

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
    std::vector<polygon_data> searchValidPolygon(world_point2d wpoint,
                                              hpl::aleph::HPLStockManager* smgr,
                                              int zMin, int zMax);

    /**
        二つの線が織り成す角度を求めます
        @param pIndexA1,2 線分A1-A2の点インデックス
        @param pIndexB1,2 線分B1-B2の点インデックス
    */
    double getTwoLinesDegree(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);
    double getTwoLinesRadian(int pIndexA1, int pIndexA2, int pIndexB1, int pIndexB2);

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
	int addSide(side_data side, bool isClockwise);
	int addPolygon(polygon_data polygon);
	int addMapSavedObject(map_object object);
	int addAnnotation(map_annotation annotation);

    //TODO
    //int getEndpointIndexFromAddress(endpoint_data* ep);

    /**
        簡略バージョン
    */
    void createPoint(world_point2d& wpoint, endpoint_data* ep);
    /**
        @param polyIndex 載せるポリゴンのインデックス
    */
    void createObject(world_point2d& wpoint, int polyIndex, map_object* obj,
                                   int flags, int type, int index);

    /**
        既存の点を用いて線やポリゴンを作成します
        <en> create new line and polygon with points already exist
    */
    void createLine(int beginPointIndex, int endPointIndex, line_data* line);
    void createPolygon(int pointIndexes[], int n, polygon_data* poly);

	/**
		点情報を削除します
		@param index 削除対象のインデックス
		@return 削除失敗時に偽。インデックスが正しくない場合など
	*/
    /*
	bool deleteEndpoint(int index);
	bool deleteLine(int index);
	bool deleteSide(int index);
	bool deletePolygon(int index);
	bool deleteMapSavedObject(int index);
    */
    /**
        マップアイテム（点・線・Side・ポリゴン・オブジェクト）
        を削除します
        手法としては、
        １：線の端点など、参照元が削除対象となっている場合、
            ・参照をNONEにする
            ・自分自身も削除対象とする
        ２：削除対象を削除していく
            ・削除番号の列を作る
            ・後ろ側から消していく

        @param 
    */
    bool deleteMapItems(std::vector<bool>& delPoints, std::vector<bool>& delLines,
        std::vector<bool>& delPolygons, std::vector<bool>& delSides,
		std::vector<bool>& delObjects);

	/**
		マップアイテムのインデックスを指定したテーブルに従って変更します。
		グローバルデータであるEndpointListなどもそのまま使う点に注意。
		<en> change map items' indexes with prepared index map
		@param *List 元のマップインデックスで構成されたオブジェクトデータ
		@param *IndexMap <originalIndex, newIndex>
	*/
	void changeIndexMapping(
		std::vector<endpoint_data>& endpointList, std::vector<line_data>& lineList, 
		std::vector<polygon_data>& polygonList, std::vector<side_data>& sideList,
		std::vector<map_object>& objectList,
		int endpointIndexStart, int endpointIndexEnd,
		int lineIndexStart, int lineIndexEnd,
		int polygonIndexStart, int polygonIndexEnd,
		int sideIndexStart, int sideIndexEnd,
		int objectIndexStart, int objectIndexEnd,
		std::map<int, int>& endpointIndexMap, std::map<int, int>& lineIndexMap, 
		std::map<int, int>& polygonIndexMap, std::map<int, int>& sideIndexMap, 
		std::map<int, int>& objectIndexMap);

	/*
		対象はEndpointListなど、直接いじるタイプ
		@param *IndexStart *IndexEndを参照
		@param *IndexEnd [*IndexStart, *IndexEnd)の範囲のデータに対して調整を行います
	*
	void changeIndexMappingRaw(
		int endpointIndexStart, int endpointIndexEnd,
		int lineIndexStart, int lineIndexEnd,
		int polygonIndexStart, int polygonIndexEnd,
		int sideIndexStart, int sideIndexEnd,
		int objectIndexStart, int objectIndexEnd,
		std::map<int, int>& endpointIndexMap, std::map<int, int>& lineIndexMap, 
		std::map<int, int>& polygonIndexMap, std::map<int, int>& sideIndexMap, 
		std::map<int, int>& sideIndexMap);
		*/

    /**
        独立したポリゴンデータを追加します
		ポリゴンデータやポイントデータなどから実際に追加します
    */
    void addNewPolygon(polygon_data& pdata, endpoint_data epd[], line_data ld[], int n);
    void addNewPolygon(world_distance points[][2], int n);
    void addNewPolygon(world_point2d points[], int n);

    /**
        選択データにオフセットを設定します。
        @param mx, my マウス座標
        @param sel 選択データ
    */
    void setupSelectDataGroupOffsets(int mx, int my, 
        hpl::aleph::map::HPLSelectData* sel, 
        int voffsetX, int voffsetY, int woffsetX, int woffsetY, int div);

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
//	int addInitialPlacementNum(int objectType, int index, int num);
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

	/**
		指定したType/Indexの数を求めます
	*/
	int getObjectCount(int type, int index);

	/**
		特定のType/Indexの数を調べ、initial値が存在数より少ない場合は合わせる
		存在数がinitial数より少なくても別に困らない
		@return 何か変化が生じた場合真
	*/
	bool updateObjectInitialPlacement(int type, int index);

	///////////////////////////////////
	//	Platform
	int getPlatformIndexFromPolygonIndex(int polyIndex,
		hpl::aleph::HPLStockManager* smgr);

	/**
		Check map items' validity
		valid:		[0,n)
		invalid:	-1], [n
		-1ならばNONEなのでInvalid。
		-2],[nの場合そもそもIndexの設定がおかしいのでアサーションをとばす
		削除確認は行わないので注意
		@return -1なら偽。正しい値なら真。
	*/
	template<class T>
	bool isValidIndex(int index, T numMax);
};
};
};

int getKeyByValue(std::map<int, int>& indexMap, int targetValue);
#endif

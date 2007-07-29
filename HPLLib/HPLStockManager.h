/***************************************************
	マップデータについての情報を蓄えておくクラス
	・ポリゴンの整合性情報
	・削除予定のマップアイテム
	・TODO 選択されているアイテム NEW!
***************************************************/
#ifndef _HPL_STOCK_MANAGER_
#define _HPL_STOCK_MANAGER_

#include <vector>
//#include <set>

#include "HPLSelectData.h"

namespace hpl{
namespace aleph{
    class HPLStockManager{
    public:
        /**ポリゴンの整合性*/
        std::vector<bool> polygonValidity;

        //ポリゴンを高さ順に表示する際の順番
        //TODO poly height order
        std::vector<int> polygonDrawOrderByHeight;

        //線の順番を高さ順にしたもの
        //TODO
		std::vector<int> lineDrawOrderByHeight;

		//要素の削除情報
        std::vector<bool> delPoints;
        std::vector<bool> delLines;
        std::vector<bool> delPolygons;
        std::vector<bool> delSides;
        std::vector<bool> delObjects;
		//platform
		std::vector<bool> delPlatforms;
		//light/media

		//選択した要素の情報
		std::vector<bool> selPoints;
        std::vector<bool> selLines;
        std::vector<bool> selPolygons;
        std::vector<bool> selSides;
        std::vector<bool> selObjects;
    public:
        HPLStockManager();
        ~HPLStockManager();

        //////////////////////////
        // ポリゴン整合性
        //ポリゴンが正しいかどうかを検査します(高速版)
        bool isPolygonValidityStored(int polyIndex);

        //ポリゴン整合性情報を更新します
        void updatePolygonValidityStored();

        /**
            サイズを実際のものに合わせます
        */
        void resizeDeletes();

        //削除対象の覚え書き
        //hpl::aleph::map::HPLSelectData toDeleteList;

        /**
            削除情報を更新します。
            具体的にはdynamic_worldの値に合わせて要素数を増加させます
            増加分は削除対象ではないのですべてfalseです。
        */
        void updateDeletes();
        
        /**
            削除情報を初期化
            実際にはclearした後にdaupteDeletes()を呼んでるだけ
        */
        void resetDeletes();

		/**
			選択情報を更新
		*/
		void updateSelects(hpl::aleph::map::HPLSelectData& sel);

		/**
			指定したアイテムを削除
		*/
        bool deletePoint(int index);
        bool deleteLine(int index);
        bool deletePolygon(int index);
        bool deleteSide(int index);
        bool deleteObject(int index);
		bool deletePlatform(int index);

		/**
			選択情報の取得
		*/
		bool isSelectPoint(int index);
		bool isSelectLine(int index);
		bool isSelectPolygon(int index);
		bool isSelectSide(int index);
		bool isSelectObject(int index);
    };
};
};

#endif

#ifndef _HPL_STOCK_MANAGER_
#define _HPL_STOCK_MANAGER_

#include <vector>
//#include <set>

#include "HPLSelectData.h"

namespace hpl{
namespace aleph{
    /**
        マップデータについての情報を蓄えておくクラス
        ・ポリゴンの整合性情報
        ・削除予定のマップアイテム
    */
    class HPLStockManager{
    private:
        /**ポリゴンの整合性*/
        std::vector<bool> polygonValidity;

        //ポリゴンを高さ順に表示する際の順番
        //TODO poly height order
        std::vector<int> polygonDrawOrderByHeight;

        //線の順番を高さ順にしたもの
        //TODO

        std::vector<bool> delPoints;
        std::vector<bool> delLines;
        std::vector<bool> delPolygons;
        std::vector<bool> delSides;
        std::vector<bool> delObjects;
    public:
        HPLStockManager();
        ~HPLStockManager();

        //////////////////////////
        // ポリゴン整合性
        //ポリゴンが正しいかどうかを検査します(高速版)
        bool isPolygonValidityStored(int polyIndex);

        //ポリゴン整合性情報を更新します
        void updatePolygonValidityStored();

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

        bool deletePoint(int index);
        bool deleteLine(int index);
        bool deletePolygon(int index);
        bool deleteSide(int index);
        bool deleteObject(int index);

    };
};
};

#endif

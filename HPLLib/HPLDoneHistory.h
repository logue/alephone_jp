/*
    <jp> UNDOのための作業記録です
        注意点として、復元や削除では激しくデータが入れ替わります
        NULLだったり順番がめちゃくちゃになるのを考慮しましょう
    <en> history of actions you did. this class will be used 
        for undoing

*/
#ifndef _HPL_DONE_HISTORY_
#define _HPL_DONE_HISTORY_

#include <vector>
#include "HPLSelectData.h"
#include "HPLRealMapData.h"
#include "HPLStockManager.h"

namespace hpl{
namespace aleph{
namespace map{
    namespace ActionType{
        enum{
            Add,
            Delete,
            Modify,
        };
    };
    
    /**
        ユーザの行った行動のまとめ
    */
    class HPLActionItem{
    private:
        HPLActionItem(){}
    public:
        HPLActionItem(int t, hpl::aleph::map::HPLSelectData& sel, hpl::aleph::map::HPLRealMapData& real);
        ~HPLActionItem();
        int type;
        hpl::aleph::map::HPLSelectData selectData;
        hpl::aleph::map::HPLRealMapData realData;
    };

    class HPLDoneHistory{
    private:
        std::vector<HPLActionItem> actionList;

        int index;
    public:
        HPLDoneHistory();
        ~HPLDoneHistory();

    public:
        /**
            情報を追加します
            @param type ActionTypeで定義している、ユーザが取った行動
        */
        void push_back(int type, HPLSelectData& selectData);

        /**
            index番目のものを取り出します。
            最大記憶量を超えていたらfalseが返ります。ポインタは無視されます
            取り出したとしても、selectDataは
            ・保存によって削除が実行された後
            にインデックス値が変化してしまうため、updateIndexes()を呼ぶ必要がある
        */
        bool back(int *type, hpl::aleph::map::HPLSelectData* selectData, hpl::aleph::map::HPLRealMapData* realData);

        void forward(int *type, hpl::aleph::map::HPLSelectData* selectData,
            hpl::aleph::map::HPLRealMapData* realData);
        /**
            インデックス番号を削除後のものに対応させます。
        */
        void updateIndexes(hpl::aleph::HPLStockManager* smgr);

        int getIndex();
        int getRemainUndoCount();
        int getRemainRedoCount();
    private:
    };
};
};
};

#endif

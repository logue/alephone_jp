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
    
    class HPLDoneHistory{
    private:
        //触ったデータ情報
        std::vector<HPLSelectData> dataList;

        //触った実データの控え
        std::vector<HPLRealMapData> realList;
    public:
        HPLDoneHistory();
        ~HPLDoneHistory();

    public:
        /**
            情報を追加します
        */
        void push_back(HPLSelectData selectData);

        /**
            最後からindex番目の要素を取り出します。
            最大記憶量を超えていたらNULLが入り、falseが返ります
        */
        bool getLastIndexOf(int index,
            HPLSelectData* selectData, HPLRealMapData* realData);
    private:
    };
};
};
};

#endif

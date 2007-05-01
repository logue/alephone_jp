/*
    <jp> UNDOのための作業記録です
        注意点として、復元や削除では激しくデータが入れ替わります
        NULLだったり順番がめちゃくちゃになるのを考慮しましょう
    <en> history of actions you did. this class will be used 
        for undoing

*/
#ifndef _HPL_DONE_HISTORY_
#define _HPL_DONE_HISTORY_

#include <list>
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
        list<HPLSelectData> dataList;

        //触った実データの控え
        list<HPLRealMapData> realList;
    public:
        HPLDoneHistory();
        ~HPLDoneHistory();
    };
};
};
};

#endif

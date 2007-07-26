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
	/**
		行動タイプ
	*/
    namespace ActionType{
        enum{
			//何もしていない状態
			//移動前の情報を入れておく
			None,
			//新規作成
			//オブジェクト情報をそのまま保持。もし保存などを行いインデックスが整理されてしまった場合は
			//最後に新規で作成され直すことになる。
            Add,
			//削除
			//Addと同様
            Delete,
			//移動
			//移動のみを扱い、それに伴う特性データを保持
			Move,
			//情報の変更
			//特徴データの変更のみを行い、移動・追加・削除については無視
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
		/**
			@param t タイプ ActionType::
			@param sel 選択している情報(インデックスのみ)
			@param real 選択している物体の真の情報(memcpyの産物)
		*/
        HPLActionItem(int t, hpl::aleph::map::HPLSelectData& sel,
			hpl::aleph::map::HPLRealMapData& real);
        ~HPLActionItem();
        int type;
        hpl::aleph::map::HPLSelectData selectData;
        hpl::aleph::map::HPLRealMapData realData;
    };

    class HPLDoneHistory{
    private:
        std::vector<HPLActionItem> actionList;

        int index;
		int indexMax;
    public:
        HPLDoneHistory();
        ~HPLDoneHistory();

    public:
		/**
			最大数を設定します
		*/
		void setIndexMax(int m);
		int getIndexMax();
        /**
            情報を追加します
        */
        void push_back(int type, HPLSelectData& selData);

        /**
            index番目のものを取り出します。
            最大記憶量を超えていたらfalseが返ります。ポインタは無視されます
            取り出したとしても、selectDataは
            ・保存によって削除が実行された後
            にインデックス値が変化してしまうため、updateIndexes()を呼ぶ必要がある
        */
        bool back(int *type, hpl::aleph::map::HPLSelectData* selectData, hpl::aleph::map::HPLRealMapData* realData);

		/**
			リドゥ
		*/
        bool forward(int *type, HPLSelectData* selectData, HPLRealMapData* realData);

		/**
			最新版の状態を取得します
			取得しても内容や位置は変化させません
		*/
		bool getTail(int *type, HPLSelectData* sel, HPLRealMapData* real);

        /**
            インデックス番号を削除後のものに対応させます。
        */
        void updateIndexes(hpl::aleph::HPLStockManager* smgr);

		/**
			初期化します
		*/
		void init();

        int getIndex();
        int getRemainUndoCount();
        int getRemainRedoCount();
    private:
    };
};
};
};

#endif

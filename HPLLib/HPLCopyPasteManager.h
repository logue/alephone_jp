#ifndef _HPL_COPY_PASTE_MANAGER_
#define _HPL_COPY_PASTE_MANAGER_

#include "HPLRealMapData.h"

/**
	コピー＆ペーストの管理と処理を行います
*/
//コピペの時のずらし間隔
const int COPY_AND_PASTE_DELTA_X = 10;
const int COPY_AND_PASTE_DELTA_Y = COPY_AND_PASTE_DELTA_X;

namespace hpl{
namespace aleph{
	class HPLCopyPasteManager{
		//コピペで保持するデータ
		hpl::aleph::map::HPLRealMapData storedMapData;
		//ずらす位置
		int storedDataDiffPointDelta[2];
	public:
		HPLCopyPasteManager();
		~HPLCopyPasteManager();

		/**
			保持しているデータを初期化します
		*/
		void clear();

		/**
			コピーします
			数値の対応は一旦内部インデックスに変換します
			存在しないものはNONEになりますが、
			線のみのコピーの場合、新たに点情報を付け加えます
			@param sel コピー元の選択データ
		*/
		void copy(hpl::aleph::map::HPLSelectData& sel);

		/**
			保持している内容をペーストします
			@return ペーストに失敗した場合（何も保持していないとき）に偽
		*/
		bool paste(int div);
	};
};
};
#endif

#include "HPLStringModifier.h"

/////////////////////////////////////////////////////////////////////////////
//////////////  Global Methods  /////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
std::vector<std::string> hpl::string::Split( std::string src, const char* key){
	//結果用
	std::vector<std::string> vList;

	int index = 0;
	//用意された文字列srcの長さ分だけ調べる。
	//また、1週するごとにindexに検索結果が出るので、検索結果が無かった場合に終了する。
	while( index < static_cast<int>(src.size()) && index != static_cast<int>(std::string::npos)){
		//前に検索した場所を覚えておく
		int oldindex = index;
		//指定文字列で前から検索する
		index = (int)src.find( key,index);
		if( index != (int)std::string::npos){
			//見つかった
			//→前に検索した場所からindexまで((index-oldindex)個分)を取得
			std::string str = src.substr( oldindex, index-oldindex);
			//結果に追加。
			vList.push_back(str);
			//検索位置を記憶
			index += (int)strlen(key);//key.size();
		}else{
			//見つからなかった
			//→その場所から最後までを最後の要素として追加。次のwhileでループから抜ける
			std::string str = src.substr(oldindex);
			vList.push_back(str);
		}
	}
	return vList;
}

/*
    文字列の先頭に指定数の文字を付加
    @param src 対象
    @param power 最大文字列長
    @param appender 付加する文字列
*/
std::string hpl::string::appendFrontString(std::string &src,
                                           int power,
                                           std::string& appender)
{
    std::string result = src;
    //すでにオーバーしている場合何もしせずコピーを返す
    if((int)(src.size()) > power){
        return result;
    }
    //文字列長がオーバーするまで
    while((int)(result.size()) <= power){
        result = appender + result;
    }
    //オーバーしたらカット
    if((int)(result.size()) > power){
        result = result.substr(result.size() - power);
    }
    return result;
}

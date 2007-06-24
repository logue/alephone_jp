#pragma once
//#ifndef _MAP_DEMERGER_ONE_WX_
//#define _MAP_DEMERGER_ONE_WX_

//プリコンパイルを使いたい場合に使用
#include <wx/wxprec.h>

//ボーランドC/C++用のおまじない
#ifdef __BORLANDC__
#pragma hdrstop
#endif

//必要なインクルード
#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
#include "wx/settings.h"

class MapDemergerOneWX: public wxApp{
public:
//    MapDemergerOneWX();
//    ~MapDemergerOneWX();
    virtual bool OnInit();
};
DECLARE_APP(MapDemergerOneWX)

//#endif

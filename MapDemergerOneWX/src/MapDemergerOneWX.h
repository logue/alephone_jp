#pragma once
//#ifndef _MAP_DEMERGER_ONE_WX_
//#define _MAP_DEMERGER_ONE_WX_

//�v���R���p�C�����g�������ꍇ�Ɏg�p
#include <wx/wxprec.h>

//�{�[�����hC/C++�p�̂��܂��Ȃ�
#ifdef __BORLANDC__
#pragma hdrstop
#endif

//�K�v�ȃC���N���[�h
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

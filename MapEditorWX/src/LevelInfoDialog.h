#ifndef _LEVEL_INFO_DIALOG_
#define _LEVEL_INFO_DIALOG_

#include "DlgCommon.h"

class LevelInfoDialog: public wxDialog{
public:
    LevelInfoDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~LevelInfoDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

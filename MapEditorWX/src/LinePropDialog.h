#ifndef _LINE_PROP_DIALOG_
#define _LINE_PROP_DIALOG_

#include "DlgCommon.h"

class LinePropDialog: public wxDialog{
public:
    LinePropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~LinePropDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

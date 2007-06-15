#ifndef _SIDE_PROP_DIALOG_
#define _SIDE_PROP_DIALOG_

#include "DlgCommon.h"

class SidePropDialog: public wxDialog{
public:
    SidePropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~SidePropDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

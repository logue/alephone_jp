#ifndef _SELECT_LEVEL_DIALOG_
#define _SELECT_LEVEL_DIALOG_

#include <wx/dialog.h>

class SelectLevelDialog: public wxDialog{
public:
    SelectLevelDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~SelectLevelDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

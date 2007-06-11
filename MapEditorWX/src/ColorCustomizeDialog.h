#ifndef _COLOR_CUSTOMIZE_DIALOG_
#define _COLOR_CUSTOMIZE_DIALOG_

#include <wx/dialog.h>

class ColorCustomizeDialog: public wxDialog{
public:
    ColorCustomizeDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~ColorCustomizeDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

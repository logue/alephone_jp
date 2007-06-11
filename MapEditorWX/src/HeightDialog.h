#ifndef _HEIGHT_DIALOG_
#define _HEIGHT_DIALOG_

#include <wx/dialog.h>

class HeightDialog: public wxDialog{
public:
    HeightDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual  ~HeightDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

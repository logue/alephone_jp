#ifndef _PLATFORM_DIALOG_
#define _PLATFORM_DIALOG_

#include <wx/dialog.h>

class PlatformDialog: public wxDialog{
public:
    PlatformDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~PlatformDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

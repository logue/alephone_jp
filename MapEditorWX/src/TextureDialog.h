#ifndef _TEXTURE_DIALOG_
#define _TEXTURE_DIALOG_

#include <wx/dialog.h>

class TextureDialog: public wxDialog{
public:
    TextureDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~TextureDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

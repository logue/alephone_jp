#ifndef _LINE_PROP_DIALOG_
#define _LINE_PROP_DIALOG_

#include <wx/dialog.h>

class LinePropDialog: public wxDialog{
public:
    LinePropDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~LinePropDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

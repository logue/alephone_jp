#ifndef _SIDE_PROP_DIALOG_
#define _SIDE_PROP_DIALOG_

#include <wx/dialog.h>

class SidePropDialog: public wxDialog{
public:
    SidePropDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~SidePropDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

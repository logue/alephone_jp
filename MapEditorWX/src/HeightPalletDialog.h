#ifndef _HEIGHT_PALLET_DIALOG_
#define _HEIGHT_PALLET_DIALOG_

#include <wx/dialog.h>

class HeightPalletDialog: public wxDialog{
public:
    HeightPalletDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~HeightPalletDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

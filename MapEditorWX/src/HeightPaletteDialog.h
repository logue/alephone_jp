#ifndef _HEIGHT_PALLET_DIALOG_
#define _HEIGHT_PALLET_DIALOG_

#include "DlgCommon.h"

class HeightPaletteDialog: public wxDialog{
public:
    HeightPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~HeightPaletteDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

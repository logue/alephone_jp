#ifndef _COLOR_CUSTOMIZE_DIALOG_
#define _COLOR_CUSTOMIZE_DIALOG_

#include "DlgCommon.h"

class ColorCustomizeDialog: public wxDialog{
public:
    ColorCustomizeDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~ColorCustomizeDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

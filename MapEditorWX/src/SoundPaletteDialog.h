#ifndef _SOUND_PALETTE_DIALOG_
#define _SOUND_PALETTE_DIALOG_

#include "DlgCommon.h"

class SoundPaletteDialog: public wxDialog{
public:
    SoundPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~SoundPaletteDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

#ifndef _MEDIA_PALETTE_DIALOG_
#define _MEDIA_PALETTE_DIALOG_

#include "DlgCommon.h"

class MediaPaletteDialog: public wxDialog{
public:
    MediaPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~MediaPaletteDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

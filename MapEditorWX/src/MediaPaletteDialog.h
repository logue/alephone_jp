#ifndef _MEDIA_PALETTE_DIALOG_
#define _MEDIA_PALETTE_DIALOG_

#include "DlgCommon.h"

class MediaPaletteDialog: public wxDialog{
public:
    MediaPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~MediaPaletteDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

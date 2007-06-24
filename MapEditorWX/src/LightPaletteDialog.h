#ifndef _LIGHT_PALETTE_DIALOG_
#define _LIGHT_PALETTE_DIALOG_

#include "DlgCommon.h"

class LightPaletteDialog: public wxDialog{
public:
    LightPaletteDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~LightPaletteDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

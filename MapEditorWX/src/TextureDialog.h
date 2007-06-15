#ifndef _TEXTURE_DIALOG_
#define _TEXTURE_DIALOG_

#include "DlgCommon.h"

class TextureDialog: public wxDialog{
public:
    TextureDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~TextureDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

#ifndef _VISUAL_DIALOG_
#define _VISUAL_DIALOG_

#include "DlgCommon.h"

class VisualDialog: public wxDialog{
public:
    VisualDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~VisualDialog();

    void OnClose();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

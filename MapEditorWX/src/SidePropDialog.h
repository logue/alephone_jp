#ifndef _SIDE_PROP_DIALOG_
#define _SIDE_PROP_DIALOG_

#include "DlgCommon.h"

class SidePropDialog: public wxDialog{
    int index;
public:
    void setIndex(int ind);
    int getIndex();
    SidePropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~SidePropDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

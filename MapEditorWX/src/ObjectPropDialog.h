#ifndef _OBJECT_PROP_DIALOG_
#define _OBJECT_PROP_DIALOG_

#include "DlgCommon.h"

class ObjectPropDialog: public wxDialog{
public:
    ObjectPropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~ObjectPropDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

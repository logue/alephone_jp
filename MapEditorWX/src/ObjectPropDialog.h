#ifndef _OBJECT_PROP_DIALOG_
#define _OBJECT_PROP_DIALOG_

#include "DlgCommon.h"

class ObjectPropDialog: public wxDialog{
    int objIndex;
public:
    ObjectPropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~ObjectPropDialog();

    void setObjIndex(int index);
    int getObjIndex();
private:
    void setupDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

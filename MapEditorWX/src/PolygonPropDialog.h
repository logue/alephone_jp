#ifndef _POLYGON_PROP_DIALOG_
#define _POLYGON_PROP_DIALOG_

#include "DlgCommon.h"

class PolygonPropDialog: public wxDialog{
public:
    PolygonPropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~PolygonPropDialog();

    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

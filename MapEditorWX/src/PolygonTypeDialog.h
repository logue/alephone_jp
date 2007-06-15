#ifndef _POLYGON_TYPE_DIALOG_
#define _POLYGON_TYPE_DIALOG_

#include "DlgCommon.h"

class PolygonTypeDialog: public wxDialog{
public:
    PolygonTypeDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~PolygonTypeDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

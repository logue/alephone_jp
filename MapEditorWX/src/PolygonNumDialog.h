#ifndef _POLYGON_NUM_DIALOG_
#define _POLYGON_NUM_DIALOG_

#include "DlgCommon.h"

class PolygonNumDialog: public wxDialog{
public:
    PolygonNumDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~PolygonNumDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};
#endif

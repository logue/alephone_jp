#ifndef _POLYGON_TYPE_DIALOG_
#define _POLYGON_TYPE_DIALOG_

#include "DlgCommon.h"

class PolygonTypeDialog: public wxDialog{
    wxListCtrl* list_ctrl_2;
public:
    PolygonTypeDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~PolygonTypeDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnSel(wxListEvent &event); // wxGlade: <event_handler>

};

#endif

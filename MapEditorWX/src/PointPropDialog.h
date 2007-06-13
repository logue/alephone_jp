#ifndef _POINT_PROP_DIALOG_
#define _POINT_PROP_DIALOG_

#include <wx/dialog.h>

class PointPropDialog: public wxDialog{
public:
    PointPropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~PointPropDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

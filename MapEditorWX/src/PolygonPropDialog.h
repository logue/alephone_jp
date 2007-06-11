#ifndef _POLYGON_PROP_DIALOG_
#define _POLYGON_PROP_DIALOG_

#include <wx/dialog.h>

class PolygonPropDialog: public wxDialog{
public:
    PolygonPropDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~PolygonPropDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()

#endif

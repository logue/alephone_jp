#ifndef _OBJECT_PROP_DIALOG_
#define _OBJECT_PROP_DIALOG_
#include <wx/dialog.h>

class ObjectPropDialog: public wxDialog{
public:
    ObjectPropDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~ObjectPropDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

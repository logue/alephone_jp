#ifndef _POLYGON_TYPE_DIALOG_
#define _POLYGON_TYPE_DIALOG_

#include <wx/dialog.h>

class PolygonTypeDialog: public wxDialog{
public:
    PolygonTypeDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~PolygonTypeDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

#ifndef _POLYGON_NUM_DIALOG_
#define _POLYGON_NUM_DIALOG_

#include <wx/dialog.h>

class PolygonNumDialog: public wxDialog{
public:
    PolygonNumDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~PolygonNumDialog();
    //�C�x���g�e�[�u���쐬<en>declare
    DECLARE_EVENT_TABLE()
};
#endif

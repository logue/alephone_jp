#ifndef _ANNOTATION_DIALOG_
#define _ANNOTATION_DIALOG_

#include <wx/dialog.h>

class AnnotationDialog: public wxDialog{
private:
/*    wxBoxSizer* boxSizer;
    wxTextCtrl* textArea*/
public:
    AnnotationDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~AnnotationDialog();
    void OnClose();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

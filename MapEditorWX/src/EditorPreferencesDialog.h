#ifndef _EDITOR_PREFERENCES_DIALOG_
#define _EDITOR_PREFERENCES_DIALOG_

#include <wx/dialog.h>

class EditorPreferencesDialog: public wxDialog{
public:
    EditorPreferencesDialog();
    bool Create(wxWindow* parent, wxWindowID id, const wxString& title);
    virtual ~EditorPreferencesDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

#ifndef _EDITOR_PREFERENCES_DIALOG_
#define _EDITOR_PREFERENCES_DIALOG_

#include "DlgCommon.h"

class EditorPreferencesDialog: public wxDialog{
public:
    EditorPreferencesDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~EditorPreferencesDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
};

#endif

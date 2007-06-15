#ifndef _EDITOR_PREFERENCES_DIALOG_
#define _EDITOR_PREFERENCES_DIALOG_

#include "DlgCommon.h"

class EditorPreferencesDialog: public wxDialog{
public:
    wxStaticText* label_19;
    wxChoice* choice_9;
    wxCheckBox* checkbox_27;
    wxCheckBox* checkbox_28;
    wxCheckBox* checkbox_31;
    wxCheckBox* checkbox_30;
    wxCheckBox* checkbox_32;
    wxCheckBox* checkbox_33;
    wxCheckBox* checkbox_34;
    wxCheckBox* checkbox_35;
    wxCheckBox* checkbox_36;
    wxCheckBox* checkbox_29;
    wxStaticText* label_20;
    wxChoice* choice_10;
    wxCheckBox* checkbox_37;
    wxCheckBox* checkbox_38;
    wxButton* button_15;
    wxButton* button_13;
    wxButton* button_14;
    EditorPreferencesDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~EditorPreferencesDialog();
    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnDefault(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnOk(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCancel(wxCommandEvent &event); // wxGlade: <event_handler>
};

#endif

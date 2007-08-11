#ifndef _EDITOR_PREFERENCES_DIALOG_
#define _EDITOR_PREFERENCES_DIALOG_

#include "DlgCommon.h"

class EditorPreferencesDialog: public wxDialog{
    wxStaticText* label_19;
    wxChoice* choice_9;
    wxCheckBox* checkbox[NUMBER_OF_EDITOR_FLAGS];
    wxStaticText* label_20;
    wxChoice* choice_10;
    wxButton* button_15;
    wxButton* button_13;
    wxButton* button_14;

	wxTextCtrl* text_ctrl_shapesFilePath;

    ColorSettings colorSetting;
public:
    EditorPreferencesDialog();
    bool Create(wxWindow* parent, wxWindowID id);
    virtual ~EditorPreferencesDialog();

private:
    void setupDialog(MapEditorOneSetting* setting);

    //イベントテーブル作成<en>declare
    DECLARE_EVENT_TABLE()
    void OnDefault(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnOk(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnCancel(wxCommandEvent &event); // wxGlade: <event_handler>
    void OnColor(wxCommandEvent &event);
};

#endif

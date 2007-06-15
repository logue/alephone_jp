#include "EditorPreferencesDialog.h"
#include "MapEditorWX.h"
enum{
    ID_DEFAULT,
};

BEGIN_EVENT_TABLE(EditorPreferencesDialog, wxDialog)
    // begin wxGlade: EditorPreferences::event_table
    EVT_BUTTON(wxID_DEFAULT, EditorPreferencesDialog::OnDefault)
    EVT_BUTTON(wxID_OK, EditorPreferencesDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, EditorPreferencesDialog::OnCancel)
    // end wxGlade
END_EVENT_TABLE();
EditorPreferencesDialog::EditorPreferencesDialog()
{
}
EditorPreferencesDialog::~EditorPreferencesDialog()
{
}
bool EditorPreferencesDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Editor Preferences"));
    label_19 = new wxStaticText(this, wxID_ANY, wxT("Grid size"));
    choice_9 = new wxChoice(this, wxID_ANY);
    checkbox_27 = new wxCheckBox(this, wxID_ANY, wxT("Show grid"));
    checkbox_28 = new wxCheckBox(this, wxID_ANY, wxT("Fit to grid"));
    checkbox_31 = new wxCheckBox(this, wxID_ANY, wxT("Show monsters"));
    checkbox_30 = new wxCheckBox(this, wxID_ANY, wxT("Show items"));
    checkbox_32 = new wxCheckBox(this, wxID_ANY, wxT("Show scenery"));
    checkbox_33 = new wxCheckBox(this, wxID_ANY, wxT("Show players"));
    checkbox_34 = new wxCheckBox(this, wxID_ANY, wxT("Show goals"));
    checkbox_35 = new wxCheckBox(this, wxID_ANY, wxT("Show sounds"));
    checkbox_36 = new wxCheckBox(this, wxID_ANY, wxT("Show annotations"));
    checkbox_29 = new wxCheckBox(this, wxID_ANY, wxT("Visual mode-Crossfair"));
    label_20 = new wxStaticText(this, wxID_ANY, wxT("Color set"));
    choice_10 = new wxChoice(this, wxID_ANY);
    checkbox_37 = new wxCheckBox(this, wxID_ANY, wxT("Show polygons"));
    checkbox_38 = new wxCheckBox(this, wxID_ANY, wxT("Show lines"));
    button_15 = new wxButton(this, wxID_ANY, wxT("Set as default"));
    button_13 = new wxButton(this, wxID_ANY, wxT("OK"));
    button_14 = new wxButton(this, wxID_ANY, wxT("Cancel"));

    wxFlexGridSizer* sizer_45 = new wxFlexGridSizer(3, 1, 0, 0);
    wxBoxSizer* sizer_48 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_47 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* sizer_50 = new wxFlexGridSizer(3, 1, 0, 0);
    wxBoxSizer* sizer_51 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_49 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_46 = new wxBoxSizer(wxHORIZONTAL);
    sizer_46->Add(label_19, 0, 0, 0);
    sizer_46->Add(choice_9, 0, 0, 0);
    sizer_45->Add(sizer_46, 1, wxEXPAND, 0);
    sizer_49->Add(checkbox_27, 0, 0, 0);
    sizer_49->Add(checkbox_28, 0, 0, 0);
    sizer_49->Add(checkbox_31, 0, 0, 0);
    sizer_49->Add(checkbox_30, 0, 0, 0);
    sizer_49->Add(checkbox_32, 0, 0, 0);
    sizer_49->Add(checkbox_33, 0, 0, 0);
    sizer_49->Add(checkbox_34, 0, 0, 0);
    sizer_49->Add(checkbox_35, 0, 0, 0);
    sizer_49->Add(checkbox_36, 0, 0, 0);
    sizer_49->Add(checkbox_29, 0, 0, 0);
    sizer_47->Add(sizer_49, 1, wxEXPAND, 0);
    sizer_51->Add(label_20, 0, 0, 0);
    sizer_51->Add(choice_10, 0, 0, 0);
    sizer_50->Add(sizer_51, 1, wxEXPAND, 0);
    sizer_50->Add(checkbox_37, 0, 0, 0);
    sizer_50->Add(checkbox_38, 0, 0, 0);
    sizer_50->Add(button_15, 0, 0, 0);
    sizer_47->Add(sizer_50, 1, wxEXPAND, 0);
    sizer_45->Add(sizer_47, 1, wxEXPAND, 0);
    sizer_48->Add(button_13, 0, 0, 0);
    sizer_48->Add(button_14, 0, 0, 0);
    sizer_45->Add(sizer_48, 1, wxEXPAND, 0);
    SetSizer(sizer_45);
    sizer_45->Fit(this);
    Layout();
    return result;
}
void EditorPreferencesDialog::OnOk(wxCommandEvent& wv)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void EditorPreferencesDialog::OnCancel(wxCommandEvent &ev)
{
    SetReturnCode(wxID_CANCEL);
    Destroy();
}
void EditorPreferencesDialog::OnDefault(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (EditorPreferences::OnDefault) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}

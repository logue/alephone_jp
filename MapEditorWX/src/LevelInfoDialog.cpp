#include "LevelInfoDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(LevelInfoDialog, wxDialog)
END_EVENT_TABLE()
LevelInfoDialog::LevelInfoDialog()
{
}
LevelInfoDialog::~LevelInfoDialog()
{
}
bool LevelInfoDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Level Information"));
    sizer_58_staticbox = new wxStaticBox(this, -1, wxT("Env Type"));
    sizer_59_staticbox = new wxStaticBox(this, -1, wxT("Mission Type"));
    sizer_60_staticbox = new wxStaticBox(this, -1, wxT("Game Type"));
    label_65 = new wxStaticText(this, wxID_ANY, wxT("Level lavel"));
    text_ctrl_44 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_73 = new wxStaticText(this, wxID_ANY, wxT("Environment"));
    choice_28 = new wxChoice(this, wxID_ANY);
    label_74 = new wxStaticText(this, wxID_ANY, wxT("Landscape"));
    choice_29 = new wxChoice(this, wxID_ANY);
    checkbox_60 = new wxCheckBox(this, wxID_ANY, wxT("Single Player"));
    checkbox_62 = new wxCheckBox(this, wxID_ANY, wxT("Cooperation (COOP)"));
    checkbox_66 = new wxCheckBox(this, wxID_ANY, wxT("Capture The Flags (CTF)"));
    checkbox_63 = new wxCheckBox(this, wxID_ANY, wxT("King Of The Hill (KOTH)"));
    checkbox_64 = new wxCheckBox(this, wxID_ANY, wxT("Kill Man With Ball (BALL)"));
    checkbox_65 = new wxCheckBox(this, wxID_ANY, wxT("Defense"));
    checkbox_67 = new wxCheckBox(this, wxID_ANY, wxT("Rugby"));
    checkbox_61 = new wxCheckBox(this, ID_TAG, wxT("Tag"));
    checkbox_41 = new wxCheckBox(this, wxID_ANY, wxT("Vacuum"));
    checkbox_42 = new wxCheckBox(this, wxID_ANY, wxT("Rebellion"));
    checkbox_43 = new wxCheckBox(this, wxID_ANY, wxT("LowGravity"));
    checkbox_44 = new wxCheckBox(this, wxID_ANY, wxT("Magnetic"));
    checkbox_55 = new wxCheckBox(this, wxID_ANY, wxT("Extermination"));
    checkbox_56 = new wxCheckBox(this, wxID_ANY, wxT("Exploration"));
    checkbox_57 = new wxCheckBox(this, wxID_ANY, wxT("Retrieval"));
    checkbox_58 = new wxCheckBox(this, wxID_ANY, wxT("Repair"));
    checkbox_59 = new wxCheckBox(this, wxID_ANY, wxT("Rescue"));
    button_28 = new wxButton(this, wxID_OK, wxEmptyString);
    button_29 = new wxButton(this, wxID_CANCEL, wxEmptyString);

    text_ctrl_44->SetMinSize(wxSize(250, -1));
    wxFlexGridSizer* grid_sizer_32 = new wxFlexGridSizer(3, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_35 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_34 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_36 = new wxFlexGridSizer(2, 1, 0, 0);
    wxStaticBoxSizer* sizer_59 = new wxStaticBoxSizer(sizer_59_staticbox, wxVERTICAL);
    wxStaticBoxSizer* sizer_58 = new wxStaticBoxSizer(sizer_58_staticbox, wxVERTICAL);
    wxFlexGridSizer* grid_sizer_37 = new wxFlexGridSizer(3, 1, 0, 0);
    wxStaticBoxSizer* sizer_60 = new wxStaticBoxSizer(sizer_60_staticbox, wxVERTICAL);
    wxFlexGridSizer* grid_sizer_39 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_38 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_33 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_33->Add(label_65, 0, 0, 0);
    grid_sizer_33->Add(text_ctrl_44, 0, wxEXPAND, 0);
    grid_sizer_32->Add(grid_sizer_33, 1, wxEXPAND, 0);
    grid_sizer_38->Add(label_73, 0, 0, 0);
    grid_sizer_38->Add(choice_28, 0, 0, 0);
    grid_sizer_37->Add(grid_sizer_38, 1, wxEXPAND, 0);
    grid_sizer_39->Add(label_74, 0, 0, 0);
    grid_sizer_39->Add(choice_29, 0, 0, 0);
    grid_sizer_37->Add(grid_sizer_39, 1, wxEXPAND, 0);
    sizer_60->Add(checkbox_60, 0, 0, 0);
    sizer_60->Add(checkbox_62, 0, 0, 0);
    sizer_60->Add(checkbox_66, 0, 0, 0);
    sizer_60->Add(checkbox_63, 0, 0, 0);
    sizer_60->Add(checkbox_64, 0, 0, 0);
    sizer_60->Add(checkbox_65, 0, 0, 0);
    sizer_60->Add(checkbox_67, 0, 0, 0);
    sizer_60->Add(checkbox_61, 0, 0, 0);
    grid_sizer_37->Add(sizer_60, 1, wxEXPAND, 0);
    grid_sizer_34->Add(grid_sizer_37, 1, wxEXPAND, 0);
    sizer_58->Add(checkbox_41, 0, 0, 0);
    sizer_58->Add(checkbox_42, 0, 0, 0);
    sizer_58->Add(checkbox_43, 0, 0, 0);
    sizer_58->Add(checkbox_44, 0, 0, 0);
    grid_sizer_36->Add(sizer_58, 1, wxEXPAND, 0);
    sizer_59->Add(checkbox_55, 0, 0, 0);
    sizer_59->Add(checkbox_56, 0, 0, 0);
    sizer_59->Add(checkbox_57, 0, 0, 0);
    sizer_59->Add(checkbox_58, 0, 0, 0);
    sizer_59->Add(checkbox_59, 0, 0, 0);
    grid_sizer_36->Add(sizer_59, 1, wxEXPAND, 0);
    grid_sizer_34->Add(grid_sizer_36, 1, wxEXPAND, 0);
    grid_sizer_32->Add(grid_sizer_34, 1, wxEXPAND, 0);
    grid_sizer_35->Add(button_28, 0, 0, 0);
    grid_sizer_35->Add(button_29, 0, 0, 0);
    grid_sizer_32->Add(grid_sizer_35, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_32);
    grid_sizer_32->Fit(this);
    Layout();
    return result;
}

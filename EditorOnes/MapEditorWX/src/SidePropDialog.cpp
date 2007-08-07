#include "SidePropDialog.h"
#include "MapEditorWX.h"
BEGIN_EVENT_TABLE(SidePropDialog, wxDialog)
END_EVENT_TABLE()
SidePropDialog::SidePropDialog()
{
}
SidePropDialog::~SidePropDialog()
{
}
bool SidePropDialog::Create(wxWindow* parent, wxWindowID id, int sideIndex)
{
    bool result = wxDialog::Create(parent, id, _T("Side Properties"));
	wxASSERT(result);

    // begin wxGlade: SidePropDialog::SidePropDialog
    sizer_56_staticbox = new wxStaticBox(this, -1, wxT("Exclusion (Impassible) zone"));
    sizer_57_staticbox = new wxStaticBox(this, -1, wxT("Primary texture"));
    sizer_57_copy_staticbox = new wxStaticBox(this, -1, wxT("Secondary texture"));
    sizer_57_copy_1_staticbox = new wxStaticBox(this, -1, wxT("Transparent texture"));
    sizer_55_staticbox = new wxStaticBox(this, -1, wxT("Flags"));
    label_80 = new wxStaticText(this, wxID_ANY, wxT("id"));
    text_ctrl_55 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_81 = new wxStaticText(this, wxID_ANY, wxT("type"));
    const wxString choice_27_choices[] = {
        
    };
    choice_27 = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, choice_27_choices, 0);
    checkbox_68 = new wxCheckBox(this, wxID_ANY, wxT("control panel"));
    checkbox_69 = new wxCheckBox(this, wxID_ANY, wxT("repair switch"));
    checkbox_70 = new wxCheckBox(this, wxID_ANY, wxT("status"));
    label_87 = new wxStaticText(this, wxID_ANY, wxT("type"));
    choice_25 = new wxChoice(this, wxID_ANY, wxDefaultPosition);
    label_88 = new wxStaticText(this, wxID_ANY, wxT("permutation"));
    choice_26 = new wxChoice(this, wxID_ANY, wxDefaultPosition);
    checkbox_71 = new wxCheckBox(this, wxID_ANY, wxT("dirty"));
    checkbox_72 = new wxCheckBox(this, wxID_ANY, wxT("destructive"));
    checkbox_73 = new wxCheckBox(this, wxID_ANY, wxT("must be lighted to use"));
    checkbox_74 = new wxCheckBox(this, wxID_ANY, wxT("projectile destroies this"));
    checkbox_75 = new wxCheckBox(this, wxID_ANY, wxT("only projectile toggles"));
    label_89 = new wxStaticText(this, wxID_ANY, wxT("e0 ("));
    text_ctrl_61 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_93 = new wxStaticText(this, wxID_ANY, wxT(","));
    text_ctrl_65 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_97 = new wxStaticText(this, wxID_ANY, wxT(")"));
    label_90 = new wxStaticText(this, wxID_ANY, wxT("e1 ("));
    text_ctrl_62 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_94 = new wxStaticText(this, wxID_ANY, wxT(","));
    text_ctrl_66 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_98 = new wxStaticText(this, wxID_ANY, wxT(")"));
    label_91 = new wxStaticText(this, wxID_ANY, wxT("e2 ("));
    text_ctrl_63 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_95 = new wxStaticText(this, wxID_ANY, wxT(","));
    text_ctrl_67 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_99 = new wxStaticText(this, wxID_ANY, wxT(")"));
    label_92 = new wxStaticText(this, wxID_ANY, wxT("e3 ("));
    text_ctrl_64 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_96 = new wxStaticText(this, wxID_ANY, wxT(","));
    text_ctrl_68 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_100 = new wxStaticText(this, wxID_ANY, wxT(")"));
    label_102 = new wxStaticText(this, wxID_ANY, wxT("polygon index"));
    text_ctrl_70 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_82 = new wxStaticText(this, wxID_ANY, wxT("line index"));
    text_ctrl_57 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_101 = new wxStaticText(this, wxID_ANY, wxT("ambient delta"));
    text_ctrl_69 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_83 = new wxStaticText(this, wxID_ANY, wxT("x"));
    text_ctrl_58 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_84 = new wxStaticText(this, wxID_ANY, wxT("y"));
    text_ctrl_59 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    panel_14 = new wxPanel(this, wxID_ANY);
    label_85 = new wxStaticText(this, wxID_ANY, wxT("transfer mode"));
    text_ctrl_60 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_86 = new wxStaticText(this, wxID_ANY, wxT("light"));
    choice_24 = new wxChoice(this, wxID_ANY);
    label_83_copy = new wxStaticText(this, wxID_ANY, wxT("x"));
    text_ctrl_58_copy = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_84_copy = new wxStaticText(this, wxID_ANY, wxT("y"));
    text_ctrl_59_copy = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    panel_14_copy = new wxPanel(this, wxID_ANY);
    label_85_copy = new wxStaticText(this, wxID_ANY, wxT("transfer mode"));
    text_ctrl_60_copy = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_86_copy = new wxStaticText(this, wxID_ANY, wxT("light"));
    choice_24_copy = new wxChoice(this, wxID_ANY);
    label_83_copy_1 = new wxStaticText(this, wxID_ANY, wxT("x"));
    text_ctrl_58_copy_1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_84_copy_1 = new wxStaticText(this, wxID_ANY, wxT("y"));
    text_ctrl_59_copy_1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    panel_14_copy_1 = new wxPanel(this, wxID_ANY);
    label_85_copy_1 = new wxStaticText(this, wxID_ANY, wxT("transfer mode"));
    text_ctrl_60_copy_1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_86_copy_1 = new wxStaticText(this, wxID_ANY, wxT("light"));
    choice_24_copy_1 = new wxChoice(this, wxID_ANY);
    button_38 = new wxButton(this, wxID_OK, wxEmptyString);
    button_39 = new wxButton(this, wxID_CANCEL, wxEmptyString);

    choice_26->SetMinSize(wxSize(50, 22));
    text_ctrl_61->SetMinSize(wxSize(50, -1));
    text_ctrl_65->SetMinSize(wxSize(50, -1));
    text_ctrl_62->SetMinSize(wxSize(50, -1));
    text_ctrl_66->SetMinSize(wxSize(50, -1));
    text_ctrl_63->SetMinSize(wxSize(50, -1));
    text_ctrl_67->SetMinSize(wxSize(50, -1));
    text_ctrl_64->SetMinSize(wxSize(50, -1));
    text_ctrl_68->SetMinSize(wxSize(50, -1));
    text_ctrl_70->SetMinSize(wxSize(50, -1));
    text_ctrl_57->SetMinSize(wxSize(50, -1));
    panel_14->SetMinSize(wxSize(45,45));
    panel_14_copy->SetMinSize(wxSize(45,45));
    panel_14_copy_1->SetMinSize(wxSize(45,45));

    wxFlexGridSizer* grid_sizer_47 = new wxFlexGridSizer(2, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_48 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_49 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_50 = new wxFlexGridSizer(6, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_50_copy = new wxFlexGridSizer(6, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_50_copy_1 = new wxFlexGridSizer(6, 1, 0, 0);
    wxStaticBoxSizer* sizer_57_copy_1 = new wxStaticBoxSizer(sizer_57_copy_1_staticbox, wxVERTICAL);
    wxFlexGridSizer* grid_sizer_62_copy_1 = new wxFlexGridSizer(2, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_60_copy_1 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_61_copy_1 = new wxFlexGridSizer(2, 2, 0, 0);
    wxStaticBoxSizer* sizer_57_copy = new wxStaticBoxSizer(sizer_57_copy_staticbox, wxVERTICAL);
    wxFlexGridSizer* grid_sizer_62_copy = new wxFlexGridSizer(2, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_60_copy = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_61_copy = new wxFlexGridSizer(2, 2, 0, 0);
    wxStaticBoxSizer* sizer_57 = new wxStaticBoxSizer(sizer_57_staticbox, wxVERTICAL);
    wxFlexGridSizer* grid_sizer_62 = new wxFlexGridSizer(2, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_60 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_61 = new wxFlexGridSizer(2, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_51 = new wxFlexGridSizer(6, 1, 0, 0);
    wxFlexGridSizer* grid_sizer_54 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_59 = new wxFlexGridSizer(1, 2, 0, 0);
    wxStaticBoxSizer* sizer_56 = new wxStaticBoxSizer(sizer_56_staticbox, wxVERTICAL);
    wxFlexGridSizer* grid_sizer_58 = new wxFlexGridSizer(1, 5, 0, 0);
    wxFlexGridSizer* grid_sizer_57 = new wxFlexGridSizer(1, 5, 0, 0);
    wxFlexGridSizer* grid_sizer_56 = new wxFlexGridSizer(1, 5, 0, 0);
    wxFlexGridSizer* grid_sizer_55 = new wxFlexGridSizer(1, 5, 0, 0);
    wxStaticBoxSizer* sizer_55 = new wxStaticBoxSizer(sizer_55_staticbox, wxVERTICAL);
    wxFlexGridSizer* grid_sizer_65 = new wxFlexGridSizer(1, 3, 0, 0);
    wxFlexGridSizer* grid_sizer_64 = new wxFlexGridSizer(1, 3, 0, 0);
    wxFlexGridSizer* grid_sizer_63 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_53 = new wxFlexGridSizer(1, 2, 0, 0);
    wxFlexGridSizer* grid_sizer_52 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_52->Add(label_80, 0, 0, 0);
    grid_sizer_52->Add(text_ctrl_55, 0, 0, 0);
    grid_sizer_51->Add(grid_sizer_52, 1, wxEXPAND, 0);
    grid_sizer_53->Add(label_81, 0, 0, 0);
    grid_sizer_53->Add(choice_27, 0, 0, 0);
    grid_sizer_51->Add(grid_sizer_53, 1, wxEXPAND, 0);
    sizer_55->Add(checkbox_68, 0, 0, 0);
    sizer_55->Add(checkbox_69, 0, 0, 0);
    grid_sizer_63->Add(20, 20, 0, 0, 0);
    grid_sizer_63->Add(checkbox_70, 0, 0, 0);
    sizer_55->Add(grid_sizer_63, 1, wxEXPAND, 0);
    grid_sizer_64->Add(20, 20, 0, 0, 0);
    grid_sizer_64->Add(label_87, 0, 0, 0);
    grid_sizer_64->Add(choice_25, 0, 0, 0);
    sizer_55->Add(grid_sizer_64, 1, wxEXPAND, 0);
    grid_sizer_65->Add(20, 20, 0, 0, 0);
    grid_sizer_65->Add(label_88, 0, 0, 0);
    grid_sizer_65->Add(choice_26, 0, 0, 0);
    sizer_55->Add(grid_sizer_65, 1, wxEXPAND, 0);
    sizer_55->Add(checkbox_71, 0, 0, 0);
    sizer_55->Add(checkbox_72, 0, 0, 0);
    sizer_55->Add(checkbox_73, 0, 0, 0);
    sizer_55->Add(checkbox_74, 0, 0, 0);
    sizer_55->Add(checkbox_75, 0, 0, 0);
    grid_sizer_51->Add(sizer_55, 1, wxEXPAND, 0);
    grid_sizer_55->Add(label_89, 0, 0, 0);
    grid_sizer_55->Add(text_ctrl_61, 0, 0, 0);
    grid_sizer_55->Add(label_93, 0, 0, 0);
    grid_sizer_55->Add(text_ctrl_65, 0, 0, 0);
    grid_sizer_55->Add(label_97, 0, 0, 0);
    sizer_56->Add(grid_sizer_55, 1, wxEXPAND, 0);
    grid_sizer_56->Add(label_90, 0, 0, 0);
    grid_sizer_56->Add(text_ctrl_62, 0, 0, 0);
    grid_sizer_56->Add(label_94, 0, 0, 0);
    grid_sizer_56->Add(text_ctrl_66, 0, 0, 0);
    grid_sizer_56->Add(label_98, 0, 0, 0);
    sizer_56->Add(grid_sizer_56, 1, wxEXPAND, 0);
    grid_sizer_57->Add(label_91, 0, 0, 0);
    grid_sizer_57->Add(text_ctrl_63, 0, 0, 0);
    grid_sizer_57->Add(label_95, 0, 0, 0);
    grid_sizer_57->Add(text_ctrl_67, 0, 0, 0);
    grid_sizer_57->Add(label_99, 0, 0, 0);
    sizer_56->Add(grid_sizer_57, 1, wxEXPAND, 0);
    grid_sizer_58->Add(label_92, 0, 0, 0);
    grid_sizer_58->Add(text_ctrl_64, 0, 0, 0);
    grid_sizer_58->Add(label_96, 0, 0, 0);
    grid_sizer_58->Add(text_ctrl_68, 0, 0, 0);
    grid_sizer_58->Add(label_100, 0, 0, 0);
    sizer_56->Add(grid_sizer_58, 1, wxEXPAND, 0);
    grid_sizer_51->Add(sizer_56, 1, wxEXPAND, 0);
    grid_sizer_59->Add(label_102, 0, 0, 0);
    grid_sizer_59->Add(text_ctrl_70, 0, 0, 0);
    grid_sizer_51->Add(grid_sizer_59, 1, wxEXPAND, 0);
    grid_sizer_54->Add(label_82, 0, 0, 0);
    grid_sizer_54->Add(text_ctrl_57, 0, 0, 0);
    grid_sizer_54->Add(label_101, 0, 0, 0);
    grid_sizer_54->Add(text_ctrl_69, 0, 0, 0);
    grid_sizer_51->Add(grid_sizer_54, 1, wxEXPAND, 0);
    grid_sizer_47->Add(grid_sizer_51, 1, wxEXPAND, 0);
    grid_sizer_61->Add(label_83, 0, 0, 0);
    grid_sizer_61->Add(text_ctrl_58, 0, 0, 0);
    grid_sizer_61->Add(label_84, 0, 0, 0);
    grid_sizer_61->Add(text_ctrl_59, 0, 0, 0);
    grid_sizer_60->Add(grid_sizer_61, 1, wxEXPAND, 0);
    grid_sizer_60->Add(panel_14, 1, wxEXPAND, 0);
    sizer_57->Add(grid_sizer_60, 1, wxEXPAND, 0);
    grid_sizer_62->Add(label_85, 0, 0, 0);
    grid_sizer_62->Add(text_ctrl_60, 0, 0, 0);
    grid_sizer_62->Add(label_86, 0, 0, 0);
    grid_sizer_62->Add(choice_24, 0, 0, 0);
    sizer_57->Add(grid_sizer_62, 1, wxEXPAND, 0);
    grid_sizer_50->Add(sizer_57, 1, wxEXPAND, 0);
    grid_sizer_61_copy->Add(label_83_copy, 0, 0, 0);
    grid_sizer_61_copy->Add(text_ctrl_58_copy, 0, 0, 0);
    grid_sizer_61_copy->Add(label_84_copy, 0, 0, 0);
    grid_sizer_61_copy->Add(text_ctrl_59_copy, 0, 0, 0);
    grid_sizer_60_copy->Add(grid_sizer_61_copy, 1, wxEXPAND, 0);
    grid_sizer_60_copy->Add(panel_14_copy, 1, wxEXPAND, 0);
    sizer_57_copy->Add(grid_sizer_60_copy, 1, wxEXPAND, 0);
    grid_sizer_62_copy->Add(label_85_copy, 0, 0, 0);
    grid_sizer_62_copy->Add(text_ctrl_60_copy, 0, 0, 0);
    grid_sizer_62_copy->Add(label_86_copy, 0, 0, 0);
    grid_sizer_62_copy->Add(choice_24_copy, 0, 0, 0);
    sizer_57_copy->Add(grid_sizer_62_copy, 1, wxEXPAND, 0);
    grid_sizer_50_copy->Add(sizer_57_copy, 1, wxEXPAND, 0);
    grid_sizer_61_copy_1->Add(label_83_copy_1, 0, 0, 0);
    grid_sizer_61_copy_1->Add(text_ctrl_58_copy_1, 0, 0, 0);
    grid_sizer_61_copy_1->Add(label_84_copy_1, 0, 0, 0);
    grid_sizer_61_copy_1->Add(text_ctrl_59_copy_1, 0, 0, 0);
    grid_sizer_60_copy_1->Add(grid_sizer_61_copy_1, 1, wxEXPAND, 0);
    grid_sizer_60_copy_1->Add(panel_14_copy_1, 1, wxEXPAND, 0);
    sizer_57_copy_1->Add(grid_sizer_60_copy_1, 1, wxEXPAND, 0);
    grid_sizer_62_copy_1->Add(label_85_copy_1, 0, 0, 0);
    grid_sizer_62_copy_1->Add(text_ctrl_60_copy_1, 0, 0, 0);
    grid_sizer_62_copy_1->Add(label_86_copy_1, 0, 0, 0);
    grid_sizer_62_copy_1->Add(choice_24_copy_1, 0, 0, 0);
    sizer_57_copy_1->Add(grid_sizer_62_copy_1, 1, wxEXPAND, 0);
    grid_sizer_50_copy_1->Add(sizer_57_copy_1, 1, wxEXPAND, 0);
    grid_sizer_50_copy->Add(grid_sizer_50_copy_1, 1, wxEXPAND, 0);
    grid_sizer_50->Add(grid_sizer_50_copy, 1, wxEXPAND, 0);
    grid_sizer_47->Add(grid_sizer_50, 1, wxEXPAND, 0);
    grid_sizer_47->Add(grid_sizer_49, 1, wxEXPAND, 0);
    grid_sizer_48->Add(button_38, 0, 0, 0);
    grid_sizer_48->Add(button_39, 0, 0, 0);
    grid_sizer_47->Add(grid_sizer_48, 1, wxEXPAND, 0);
    SetSizer(grid_sizer_47);
    grid_sizer_47->Fit(this);
    Layout();
	// end wxGlade


	this->index = sideIndex;

	//combo setup

    return result;
}
void SidePropDialog::setIndex(int ind)
{
    this->index = ind;
}
int SidePropDialog::getIndex()
{
    return this->index;
}
side_data SidePropDialog::getSide()
{
	side_data data;
	wxASSERT(false);
	return data;
}

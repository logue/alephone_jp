#include "SidePropDialog.h"
#include "MapEditorWX.h"
#include "MapEditorMainFrame.h"

const int BTN_IMG_LBL_SIZE = 32;


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

	wxImage noneImg = wxGetApp().noneImage.Scale(BTN_IMG_LBL_SIZE, BTN_IMG_LBL_SIZE);
    // begin wxGlade: SidePropDialog::SidePropDialog
    sizer_56_staticbox = new wxStaticBox(this, -1, wxT("Exclusion (Impassible) zone"));
    sizer_57_staticbox = new wxStaticBox(this, -1, wxT("Primary texture"));
    sizer_57_copy_staticbox = new wxStaticBox(this, -1, wxT("Secondary texture"));
    sizer_57_copy_1_staticbox = new wxStaticBox(this, -1, wxT("Transparent texture"));
    sizer_55_staticbox = new wxStaticBox(this, -1, wxT("Flags"));
    label_80 = new wxStaticText(this, wxID_ANY, wxT("id"));
    text_ctrl_55 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_81 = new wxStaticText(this, wxID_ANY, wxT("type"));
    choice_27 = new wxChoice(this, wxID_ANY);
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
//    panel_14 = new wxPanel(this, wxID_ANY);
    bitmap_button_7 = new wxBitmapButton(this, wxID_ANY, noneImg);

    label_85 = new wxStaticText(this, wxID_ANY, wxT("transfer mode"));
    text_ctrl_60 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_86 = new wxStaticText(this, wxID_ANY, wxT("light"));
    choice_24 = new wxChoice(this, wxID_ANY);
    label_83_copy = new wxStaticText(this, wxID_ANY, wxT("x"));
    text_ctrl_58_copy = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_84_copy = new wxStaticText(this, wxID_ANY, wxT("y"));
    text_ctrl_59_copy = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
//    panel_14_copy = new wxPanel(this, wxID_ANY);
    bitmap_button_7_copy = new wxBitmapButton(this, wxID_ANY, noneImg);

    label_85_copy = new wxStaticText(this, wxID_ANY, wxT("transfer mode"));
    text_ctrl_60_copy = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_86_copy = new wxStaticText(this, wxID_ANY, wxT("light"));
    choice_24_copy = new wxChoice(this, wxID_ANY);
    label_83_copy_1 = new wxStaticText(this, wxID_ANY, wxT("x"));
    text_ctrl_58_copy_1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    label_84_copy_1 = new wxStaticText(this, wxID_ANY, wxT("y"));
    text_ctrl_59_copy_1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
//    panel_14_copy_1 = new wxPanel(this, wxID_ANY);
    bitmap_button_7_copy_1 = new wxBitmapButton(this, wxID_ANY, noneImg);

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
	/*
    panel_14->SetMinSize(wxSize(45,45));
    panel_14_copy->SetMinSize(wxSize(45,45));
    panel_14_copy_1->SetMinSize(wxSize(45,45));
	*/
    bitmap_button_7->SetMinSize(wxSize(45, 45));
    bitmap_button_7_copy->SetMinSize(wxSize(45, 45));
    bitmap_button_7_copy_1->SetMinSize(wxSize(45, 45));

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
//    grid_sizer_60->Add(panel_14, 1, wxEXPAND, 0);
    grid_sizer_60->Add(bitmap_button_7, 0, wxEXPAND, 0);

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
//    grid_sizer_60_copy->Add(panel_14_copy, 1, wxEXPAND, 0);
    grid_sizer_60_copy->Add(bitmap_button_7_copy, 0, wxEXPAND, 0);

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
//    grid_sizer_60_copy_1->Add(panel_14_copy_1, 1, wxEXPAND, 0);
    grid_sizer_60_copy_1->Add(bitmap_button_7_copy_1, 0, wxEXPAND, 0);

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
	//	type
	for(int i = 0; i < NUMBER_OF_SIDE_TYPES; i ++){
		this->choice_27->Insert(
			wxConvertMB2WX(wxGetApp().sideTypeInfo[i].jname.c_str()), i);
	}
	//	control panel type
	for(int i = 0; i < NUMBER_OF_CONTROL_PANELS; i ++){
		this->choice_25->Insert(
			wxConvertMB2WX(wxGetApp().sideControlPanelTypeInfo[i].jname.c_str()), i);
	}
	//lights
	for(int i = 0; i < (int)LightList.size(); i ++){
		this->choice_24->Insert(getString("%d", i), i);
		this->choice_24_copy->Insert(getString("%d", i), i);
		this->choice_24_copy_1->Insert(getString("%d", i), i);
	}
	int max = (int)LightList.size();
	this->choice_24->Insert(_T("NONE"), max);
	this->choice_24->Insert(_T("NONE"), max);
	this->choice_24_copy->Insert(_T("NONE"), max);

	side_data* side = get_side_data(sideIndex);
	wxASSERT(hpl::aleph::map::isValidIndex(sideIndex, SideList.size()));

	/*
		permutation
		スイッチ対象。
		コントロールパネルタイプが
		・ライトスイッチならライト番号
		・プラットフォームスイッチならプラットフォーム番号
		・TagスイッチならTag番号
		が入ります。
		ダイアログ起動時とコントロールパネルタイプ変更時にこれらを
		切り替える必要があります。
	*/
	this->setupPermutationChoice(side->control_panel_type);
	for(int i = 0; i < (int)LightList.size(); i ++){
		this->choice_24->Insert(getString("%d", i), i);
		this->choice_24_copy->Insert(getString("%d", i), i);
		this->choice_24_copy_1->Insert(getString("%d", i), i);
	}
	this->choice_24->Insert(_T("NONE"), (int)LightList.size());
	this->choice_24_copy->Insert(_T("NONE"), (int)LightList.size());
	this->choice_24_copy_1->Insert(_T("NONE"), (int)LightList.size());

	////////////////
	//Sideを反映
	this->text_ctrl_55->SetValue(getString("%d", sideIndex));
	this->choice_26->SetSelection(side->control_panel_permutation);
	this->choice_27->SetSelection(side->type);
	this->checkbox_68->SetValue((side->flags & _side_is_control_panel) != 0);
	this->checkbox_69->SetValue((side->flags & _side_is_repair_switch) != 0);
	this->checkbox_70->SetValue((side->flags & _control_panel_status) != 0);
	this->choice_25->SetSelection(side->control_panel_type);
	this->checkbox_71->SetValue((side->flags & _editor_dirty_bit) != 0);
	this->checkbox_72->SetValue((side->flags & _side_is_destructive_switch) != 0);
	this->checkbox_73->SetValue((side->flags & _side_is_lighted_switch) != 0);
	this->checkbox_74->SetValue((side->flags & _side_switch_can_be_destroyed) != 0);
	this->checkbox_75->SetValue((side->flags & _side_switch_can_only_be_hit_by_projectiles) != 0);
	//exclusion
	this->text_ctrl_61->SetValue(getString("%d", side->exclusion_zone.e0.x));
	this->text_ctrl_65->SetValue(getString("%d", side->exclusion_zone.e0.y));
	this->text_ctrl_62->SetValue(getString("%d", side->exclusion_zone.e1.x));
	this->text_ctrl_66->SetValue(getString("%d", side->exclusion_zone.e1.y));
	this->text_ctrl_63->SetValue(getString("%d", side->exclusion_zone.e2.x));
	this->text_ctrl_67->SetValue(getString("%d", side->exclusion_zone.e2.y));
	this->text_ctrl_64->SetValue(getString("%d", side->exclusion_zone.e3.x));
	this->text_ctrl_68->SetValue(getString("%d", side->exclusion_zone.e3.y));
	this->text_ctrl_70->SetValue(getString("%d", side->polygon_index));
	this->text_ctrl_57->SetValue(getString("%d", side->line_index));
	this->text_ctrl_69->SetValue(getString("%d", side->ambient_delta));

	//textures / lights
	this->setupTextureButtons(wxGetApp().getShapesManager()->isLoadedShapesFile(),
		this->getIndex());
	this->primaryTextureImage = ShapesImageInformation(side->primary_texture.texture);
	this->secondaryTextureImage = ShapesImageInformation(side->secondary_texture.texture);
	this->transparentTextureImage = ShapesImageInformation(side->transparent_texture.texture);
	{
		this->text_ctrl_58->SetValue(getString("%d", side->primary_texture.x0));
		this->text_ctrl_59->SetValue(getString("%d", side->primary_texture.y0));
		this->text_ctrl_60->SetValue(getString("%d", side->primary_transfer_mode));
		int index = side->primary_lightsource_index;
		if(index == NONE){
			index = (int)LightList.size();
		}
		this->choice_24->SetSelection(index);
	}

	{
		this->text_ctrl_58_copy->SetValue(getString("%d", side->secondary_texture.x0));
		this->text_ctrl_59_copy->SetValue(getString("%d", side->secondary_texture.y0));
		this->text_ctrl_60_copy->SetValue(getString("%d", side->secondary_transfer_mode));
		int index = side->secondary_lightsource_index;
		if(index == NONE){
			index = (int)LightList.size();
		}
		this->choice_24_copy->SetSelection(index);
	}
	{
		this->text_ctrl_58_copy_1->SetValue(getString("%d", side->transparent_texture.x0));
		this->text_ctrl_59_copy_1->SetValue(getString("%d", side->transparent_texture.y0));
		this->text_ctrl_60_copy_1->SetValue(getString("%d", side->transparent_transfer_mode));
		int index = side->transparent_lightsource_index;
		if(index == NONE){
			index = (int)LightList.size();
		}
		this->choice_24_copy_1->SetSelection(index);
	}
	return result;
}
void SidePropDialog::setTextureButtonImage(int shapesDescriptor,
								  wxBitmapButton* btn)
{
	if(shapesDescriptor == NONE || shapesDescriptor == UNONE){
		//TODO put the "NONE" image label on this button
		btn->SetImageLabel(wxGetApp().noneImage.Scale(BTN_IMG_LBL_SIZE, BTN_IMG_LBL_SIZE));
	}else{
		std::map<int, std::map<int, std::map<int, wxImage> > >* tmap = 
			&((MapEditorMainFrame*)GetParent())->textureMap;

		int collectionAndCLUT = GET_DESCRIPTOR_COLLECTION(shapesDescriptor);
		int collection = GET_COLLECTION(collectionAndCLUT);
		int clut = GET_COLLECTION_CLUT(collectionAndCLUT);
		int shapes = GET_DESCRIPTOR_SHAPE(shapesDescriptor);

		wxImage* img = &tmap->find(collection)->second[clut][shapes];
		btn->SetImageLabel(wxBitmap(img->Scale(BTN_IMG_LBL_SIZE, BTN_IMG_LBL_SIZE)));
	}
}

/**
	テクスチャボタンを設定します
*/
void SidePropDialog::setupTextureButtons(bool isLoadedShapesFile,
										 int sideIndex)
{
	if(isLoadedShapesFile){
		//イメージデータを取得します
		side_data* side = get_side_data(sideIndex);
		wxASSERT(hpl::aleph::map::isValidIndex(sideIndex, SideList.size()));
		setTextureButtonImage(side->primary_texture.texture, bitmap_button_7);
		setTextureButtonImage(side->secondary_texture.texture, bitmap_button_7_copy);
		setTextureButtonImage(side->transparent_texture.texture, bitmap_button_7_copy_1);
		Refresh();
	}
}

void SidePropDialog::setIndex(int ind)
{
    this->index = ind;
}
int SidePropDialog::getIndex()
{
    return this->index;
}
void SidePropDialog::OnOk(wxCommandEvent& ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void SidePropDialog::OnCancel(wxCommandEvent& ev)
{
    SetReturnCode(wxID_CANCEL);
    Destroy();
}
void SidePropDialog::OnControlPanelTypeChoice(wxCommandEvent& ev)
{
	//スイッチング
	this->setupPermutationChoice(ev.GetSelection());
}
void SidePropDialog::setupPermutationChoice(int controlPanelType)
{
	int max = (int)LightList.size();
	if(controlPanelType == _panel_is_light_switch){
	}else if(controlPanelType == _panel_is_platform_switch){
		max = (int)PlatformList.size();
	}else if(controlPanelType == _panel_is_tag_switch){
		//TODO tag?
		max = 0;
	}else{
		max = 0;
	}
	this->choice_26->Clear();
	for(int i = 0; i < max; i ++){
		this->choice_26->Insert(getString("%d", i), i);
	}
	this->choice_26->Insert(_T("NONE"), max);
}

side_data SidePropDialog::getSide()
{
	side_data data;
	//設定を反映
	//permutation
	{
		int index = this->choice_26->GetSelection();
		if(index == this->choice_26->GetCount() - 1){
			index = NONE;
		}
		data.control_panel_permutation = index;
	}
	data.type = choice_27->GetSelection();
	SET_FLAG(data.flags, _side_is_control_panel, checkbox_68->GetValue());
	SET_FLAG(data.flags, _side_is_repair_switch, checkbox_69->GetValue());
	SET_FLAG(data.flags, _control_panel_status, checkbox_70->GetValue());
	data.control_panel_type = choice_25->GetSelection();
	SET_FLAG(data.flags, _editor_dirty_bit, checkbox_71->GetValue());
	SET_FLAG(data.flags, _side_is_destructive_switch, checkbox_72->GetValue());
	SET_FLAG(data.flags, _side_is_lighted_switch, checkbox_73->GetValue());
	SET_FLAG(data.flags, _side_switch_can_be_destroyed, checkbox_74->GetValue());
	SET_FLAG(data.flags, _side_switch_can_only_be_hit_by_projectiles, checkbox_75->GetValue());
	//exclusion
	data.exclusion_zone.e0.x = atoi(text_ctrl_61->GetValue().mb_str());
	data.exclusion_zone.e0.y = atoi(text_ctrl_65->GetValue().mb_str());
	data.exclusion_zone.e1.x = atoi(text_ctrl_62->GetValue().mb_str());
	data.exclusion_zone.e1.y = atoi(text_ctrl_66->GetValue().mb_str());
	data.exclusion_zone.e2.x = atoi(text_ctrl_63->GetValue().mb_str());
	data.exclusion_zone.e2.y = atoi(text_ctrl_67->GetValue().mb_str());
	data.exclusion_zone.e3.x = atoi(text_ctrl_64->GetValue().mb_str());
	data.exclusion_zone.e3.y = atoi(text_ctrl_68->GetValue().mb_str());
	data.polygon_index = atoi(text_ctrl_70->GetValue().mb_str());
	data.line_index = atoi(text_ctrl_57->GetValue().mb_str());
	data.ambient_delta = atoi(text_ctrl_69->GetValue().mb_str());
	//texture / lights
	{
		data.primary_texture.texture = this->primaryTextureImage.getDescriptor();
		data.primary_texture.x0 = atoi(text_ctrl_58->GetValue().mb_str());
		data.primary_texture.y0 = atoi(text_ctrl_59->GetValue().mb_str());
		data.primary_transfer_mode = atoi(text_ctrl_60->GetValue().mb_str());
		int index = choice_24->GetSelection();
		if(index == (int)LightList.size())	index = NONE;
		data.primary_lightsource_index = index;
	}
	{
		data.secondary_texture.texture = this->primaryTextureImage.getDescriptor();
		data.secondary_texture.x0 = atoi(text_ctrl_58_copy->GetValue().mb_str());
		data.secondary_texture.y0 = atoi(text_ctrl_59_copy->GetValue().mb_str());
		data.secondary_transfer_mode = atoi(text_ctrl_60_copy->GetValue().mb_str());
		int index = choice_24_copy->GetSelection();
		if(index == (int)LightList.size())	index = NONE;
		data.secondary_lightsource_index = index;
	}
	{
		data.transparent_texture.texture = this->primaryTextureImage.getDescriptor();
		data.transparent_texture.x0 = atoi(text_ctrl_58_copy_1->GetValue().mb_str());
		data.transparent_texture.y0 = atoi(text_ctrl_59_copy_1->GetValue().mb_str());
		data.transparent_transfer_mode = atoi(text_ctrl_60_copy_1->GetValue().mb_str());
		int index = choice_24_copy_1->GetSelection();
		if(index == (int)LightList.size())	index = NONE;
		data.transparent_lightsource_index = index;
	}
	return data;
}

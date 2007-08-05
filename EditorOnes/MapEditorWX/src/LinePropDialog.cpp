#include "LinePropDialog.h"
#include "MapEditorWX.h"

/*enum{
    ID_LANDSCAPE,
    ID_ELEVATION,
    ID_VARIABLE,
    ID_HAS_TRANS_SIDE,
    ID_SEL,
    ID_FLOOR,
    ID_CEILING,
    ID_CLOCK_SIDE,
    ID_CCLOCK_SIDE,
    ID_CLOCK_POLY,
    ID_CCLOCK_POLY,
	
};
*/
BEGIN_EVENT_TABLE(LinePropDialog, wxDialog)
/*
//    EVT_TEXT(wxID_ANY, LinePropDialog::OnEndpoint1Edit)
//    EVT_TEXT(wxID_ANY, LinePropDialog::OnEndpoint2Edit)
    EVT_CHECKBOX(ID_LANDSCAPE, LinePropDialog::OnLandscape)
    EVT_CHECKBOX(ID_ELEVATION, LinePropDialog::OnElevation)
    EVT_CHECKBOX(ID_VARIABLE, LinePropDialog::OnVariableElev)
    EVT_CHECKBOX(ID_HAS_TRANS_SIDE, LinePropDialog::OnHasTransSide)
    EVT_RADIOBOX(ID_SEL, LinePropDialog::OnRadioSel)
    EVT_TEXT(ID_FLOOR, LinePropDialog::OnFloor)
    EVT_TEXT(ID_CEILING, LinePropDialog::OnCeiling)
    EVT_CHOICE(ID_CLOCK_SIDE, LinePropDialog::OnClockwiseSide)
    EVT_CHOICE(ID_CCLOCK_SIDE, LinePropDialog::OnCClockwiseSide)
    EVT_CHOICE(ID_CLOCK_POLY, LinePropDialog::OnClockwisePoly)
    EVT_CHOICE(ID_CCLOCK_POLY, LinePropDialog::OnCClockwisePoly)
	*/
    EVT_BUTTON(wxID_OK, LinePropDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, LinePropDialog::OnCancel)
END_EVENT_TABLE()
LinePropDialog::LinePropDialog()
{
}
LinePropDialog::~LinePropDialog()
{
}
bool LinePropDialog::Create(wxWindow* parent, wxWindowID id,
							int lineIndex_)
{
    bool result = wxDialog::Create(parent, id, _T("Line Properties"));
    sizer_54_staticbox = new wxStaticBox(this, -1, wxT("flags"));
    label_64 = new wxStaticText(this, wxID_ANY, wxT("endpoint indexes"));
    text_ctrl_42 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    text_ctrl_43 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    checkbox_45 = new wxCheckBox(this, wxID_ANY, wxT("Landscape"));
    checkbox_52 = new wxCheckBox(this, wxID_ANY, wxT("Elevation"));
    checkbox_53 = new wxCheckBox(this, wxID_ANY, wxT("Variable elev"));
    checkbox_54 = new wxCheckBox(this, wxID_ANY, wxT("Has trans side"));
    const wxString radio_box_1_choices[] = {
        wxT("Solid"),
        wxT("Transparent")
    };
    radio_box_1 = new wxRadioBox(this, wxID_ANY, wxT("solidity"), wxDefaultPosition, wxDefaultSize, 2, radio_box_1_choices, 2, wxRA_SPECIFY_ROWS);
    label_66 = new wxStaticText(this, wxID_ANY, wxT("length"));
    text_ctrl_45 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_67 = new wxStaticText(this, wxID_ANY, wxT("highest floor"));
    text_ctrl_46 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_70 = new wxStaticText(this, wxID_ANY, wxT("lowest ceiling"));
    text_ctrl_47 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_71 = new wxStaticText(this, wxID_ANY, wxT("clockwise side"));
    text_ctrl_50 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_69 = new wxStaticText(this, wxID_ANY, wxT("c-clockwise side"));
    text_ctrl_51 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_72 = new wxStaticText(this, wxID_ANY, wxT("clockwise poly"));
    text_ctrl_52 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_68 = new wxStaticText(this, wxID_ANY, wxT("c-clockwise poly"));
    text_ctrl_53 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    button_35 = new wxButton(this, wxID_OK, wxEmptyString);
    button_36 = new wxButton(this, wxID_CANCEL, wxEmptyString);

    text_ctrl_42->SetMinSize(wxSize(50, -1));
    text_ctrl_43->SetMinSize(wxSize(50, -1));
    radio_box_1->SetSelection(0);

    wxFlexGridSizer* grid_sizer_26 = new wxFlexGridSizer(10, 2, 0, 0);
    wxStaticBoxSizer* sizer_54 = new wxStaticBoxSizer(sizer_54_staticbox, wxVERTICAL);
    wxFlexGridSizer* grid_sizer_27 = new wxFlexGridSizer(1, 2, 0, 0);
    grid_sizer_26->Add(label_64, 0, 0, 0);
    grid_sizer_27->Add(text_ctrl_42, 0, 0, 0);
    grid_sizer_27->Add(text_ctrl_43, 0, 0, 0);
    grid_sizer_26->Add(grid_sizer_27, 1, wxEXPAND, 0);
    sizer_54->Add(checkbox_45, 0, 0, 0);
    sizer_54->Add(checkbox_52, 0, 0, 0);
    sizer_54->Add(checkbox_53, 0, 0, 0);
    sizer_54->Add(checkbox_54, 0, 0, 0);
    grid_sizer_26->Add(sizer_54, 1, wxEXPAND, 0);
    grid_sizer_26->Add(radio_box_1, 0, 0, 0);
    grid_sizer_26->Add(label_66, 0, 0, 0);
    grid_sizer_26->Add(text_ctrl_45, 0, 0, 0);
    grid_sizer_26->Add(label_67, 0, 0, 0);
    grid_sizer_26->Add(text_ctrl_46, 0, 0, 0);
    grid_sizer_26->Add(label_70, 0, 0, 0);
    grid_sizer_26->Add(text_ctrl_47, 0, 0, 0);
    grid_sizer_26->Add(label_71, 0, 0, 0);
    grid_sizer_26->Add(text_ctrl_50, 0, 0, 0);
    grid_sizer_26->Add(label_69, 0, 0, 0);
    grid_sizer_26->Add(text_ctrl_51, 0, 0, 0);
    grid_sizer_26->Add(label_72, 0, 0, 0);
    grid_sizer_26->Add(text_ctrl_52, 0, 0, 0);
    grid_sizer_26->Add(label_68, 0, 0, 0);
    grid_sizer_26->Add(text_ctrl_53, 0, 0, 0);
    grid_sizer_26->Add(button_35, 0, wxEXPAND, 0);
    grid_sizer_26->Add(button_36, 0, wxEXPAND, 0);
    SetSizer(grid_sizer_26);
    grid_sizer_26->Fit(this);
    Layout();

    setLineIndex(lineIndex_);

    setupDialog();
	
    return result;
}
int LinePropDialog::getLineIndex()
{
    return this->lineIndex;
}
void LinePropDialog::setLineIndex(int index)
{
    this->lineIndex = index;
}
void LinePropDialog::setupDialog()
{
    //チョイスのセットアップ
	/*
    choice_24->Clear();
    choice_25->Clear();
    for(int i = 0; i < (int)SideList.size(); i ++){
        choice_24->Insert(getString("%d", i), i);
        choice_25->Insert(getString("%d", i), i);
    }
    choice_24->Insert(_T("NONE"), (int)SideList.size());
    choice_25->Insert(_T("NONE"), (int)SideList.size());

    choice_26->Clear();
    choice_27->Clear();
    for(int i = 0; i < (int)PolygonList.size(); i ++){
        choice_26->Insert(getString("%d", i), i);
        choice_27->Insert(getString("%d", i), i);
    }
    choice_26->Insert(_T("NONE"), (int)PolygonList.size());
    choice_27->Insert(_T("NONE"), (int)PolygonList.size());
	*/

    //タイトル設定
    SetTitle(getString("line ID = [%d", getLineIndex()));

	if(!hpl::aleph::map::isValidIndex(this->getLineIndex(), LineList.size())){
		//インデックスが正しく指定されていない(NONE)
        return;
    }
    
    int index = getLineIndex();
    line_data* line = get_line_data(index);

    text_ctrl_42->SetValue(getString("%d", line->endpoint_indexes[0]));
    text_ctrl_43->SetValue(getString("%d", line->endpoint_indexes[1]));
    text_ctrl_45->SetValue(getString("%d", line->length));
    text_ctrl_46->SetValue(getString("%d", line->highest_adjacent_floor));
    text_ctrl_47->SetValue(getString("%d", line->lowest_adjacent_ceiling));
    checkbox_45->SetValue(LINE_IS_LANDSCAPED(line) != 0);
    checkbox_52->SetValue(LINE_IS_ELEVATION(line) != 0);
    checkbox_53->SetValue(LINE_IS_VARIABLE_ELEVATION(line) != 0);
    checkbox_54->SetValue(LINE_HAS_TRANSPARENT_SIDE(line) != 0);
    int sel = LINE_IS_SOLID(line) ? 0: 1;
    radio_box_1->SetSelection(sel);

	text_ctrl_50->SetValue(getString("%d",
		line->counterclockwise_polygon_side_index));
	text_ctrl_51->SetValue(getString("%d",
		line->counterclockwise_polygon_side_index));
	text_ctrl_52->SetValue(getString("%d",
		line->clockwise_polygon_owner));
	text_ctrl_53->SetValue(getString("%d",
		line->counterclockwise_polygon_owner));
    //値代入
    //setupDialog();
}
void LinePropDialog::OnOk(wxCommandEvent &ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void LinePropDialog::OnCancel(wxCommandEvent &ev)
{
    SetReturnCode(wxID_CANCEL);
    Destroy();
}
line_data LinePropDialog::getLine()
{
	if(!hpl::aleph::map::isValidIndex(getLineIndex(), LineList.size())){
		hpl::error::halt("invalid index:%d", getLineIndex());
	}
	line_data data;
	line_data* org = get_line_data(getLineIndex());
	data = *org;
	//memcpy(&data, org, sizeof(line_data));

	SET_LINE_SOLIDITY(&data, radio_box_1->GetSelection() == 0);
	SET_LINE_TRANSPARENCY(&data, radio_box_1->GetSelection() == 1);
	SET_LINE_LANDSCAPE_STATUS(&data, checkbox_45->GetValue());
	SET_LINE_ELEVATION(&data, checkbox_52->GetValue());
	SET_LINE_VARIABLE_ELEVATION(&data, checkbox_53->GetValue());
	SET_LINE_HAS_TRANSPARENT_SIDE(&data, checkbox_54->GetValue());

	//length
	//height(uneditable)
/*	data.highest_adjacent_floor = atoi(wxConvertWX2MB(
		text_ctrl_46->GetValue()));
	data.lowest_adjacent_ceiling = atoi(wxConvertWX2MB(
		text_ctrl_47->GetValue()));
		*/
	//side
	//polygon
	return data;
}



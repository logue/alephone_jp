#include "LinePropDialog.h"
#include "MapEditorWX.h"

enum{
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

BEGIN_EVENT_TABLE(LinePropDialog, wxDialog)
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
END_EVENT_TABLE()
LinePropDialog::LinePropDialog()
{
}
LinePropDialog::~LinePropDialog()
{
}
bool LinePropDialog::Create(wxWindow* parent, wxWindowID id)
{
    bool result = wxDialog::Create(parent, id, _T("Line Properties"));
    sizer_54_staticbox = new wxStaticBox(this, -1, wxT("flags"));
    label_64 = new wxStaticText(this, wxID_ANY, wxT("endpoint indexes"));
    text_ctrl_42 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    text_ctrl_43 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    checkbox_45 = new wxCheckBox(this, ID_LANDSCAPE, wxT("Landscape"));
    checkbox_52 = new wxCheckBox(this, ID_ELEVATION, wxT("Elevation"));
    checkbox_53 = new wxCheckBox(this, ID_VARIABLE, wxT("Variable elev"));
    checkbox_54 = new wxCheckBox(this, ID_HAS_TRANS_SIDE, wxT("Has trans side"));
    const wxString radio_box_1_choices[] = {
        wxT("Solid"),
        wxT("Transparent")
    };
    radio_box_1 = new wxRadioBox(this, ID_SEL, wxT("solidity"), wxDefaultPosition, wxDefaultSize, 2, radio_box_1_choices, 2, wxRA_SPECIFY_ROWS);
    label_66 = new wxStaticText(this, wxID_ANY, wxT("length"));
    text_ctrl_45 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_67 = new wxStaticText(this, wxID_ANY, wxT("highest floor"));
    text_ctrl_46 = new wxTextCtrl(this, ID_FLOOR, wxEmptyString);
    label_70 = new wxStaticText(this, wxID_ANY, wxT("lowest ceiling"));
    text_ctrl_47 = new wxTextCtrl(this, ID_CEILING, wxEmptyString);
    label_71 = new wxStaticText(this, wxID_ANY, wxT("clockwise side"));
    choice_24 = new wxChoice(this, ID_CLOCK_SIDE);
    label_69 = new wxStaticText(this, wxID_ANY, wxT("c-clockwise side"));
    choice_25 = new wxChoice(this, ID_CCLOCK_SIDE);
    label_72 = new wxStaticText(this, wxID_ANY, wxT("clockwise poly"));
    choice_26 = new wxChoice(this, ID_CLOCK_POLY);
    label_68 = new wxStaticText(this, wxID_ANY, wxT("c-clockwise poly"));
    choice_27 = new wxChoice(this, ID_CCLOCK_POLY);

    text_ctrl_42->SetMinSize(wxSize(50, -1));
    text_ctrl_43->SetMinSize(wxSize(50, -1));
    radio_box_1->SetSelection(0);

    wxFlexGridSizer* grid_sizer_26 = new wxFlexGridSizer(9, 2, 0, 0);
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
    grid_sizer_26->Add(choice_24, 0, 0, 0);
    grid_sizer_26->Add(label_69, 0, 0, 0);
    grid_sizer_26->Add(choice_25, 0, 0, 0);
    grid_sizer_26->Add(label_72, 0, 0, 0);
    grid_sizer_26->Add(choice_26, 0, 0, 0);
    grid_sizer_26->Add(label_68, 0, 0, 0);
    grid_sizer_26->Add(choice_27, 0, 0, 0);
    SetSizer(grid_sizer_26);
    grid_sizer_26->Fit(this);
    Layout();

    this->lineIndex = NONE;

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


    //タイトル設定
    SetTitle(getString("line ID = [%d", getLineIndex()));

    if(this->getLineIndex() == NONE){
        return;
    }
    
    int index = getLineIndex();
    line_data* line = get_line_data(index);
#ifdef __WXDEBUG__
    wxASSERT(line);
#endif

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
    index = line->clockwise_polygon_side_index;
    if(index == NONE){
        index = (int)SideList.size();
    }
    choice_24->SetSelection(index);
    index = line->counterclockwise_polygon_side_index;
    if(index == NONE){
        index = (int)SideList.size();
    }
    choice_25->SetSelection(index);
    index = line->clockwise_polygon_owner;
    if(index == NONE){
        index = (int)PolygonList.size();
    }
    choice_26->SetSelection(index);
    index = line->counterclockwise_polygon_owner;
    if(index == NONE){
        index = (int)PolygonList.size();
    }
    choice_27->SetSelection(index);

    //値代入
    setupDialog();
}
void LinePropDialog::OnEndpoint1Edit(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	get_line_data(getLineIndex())->endpoint_indexes[0] = atoi(wxConvertWX2MB(event.GetString()));
}


void LinePropDialog::OnEndpoint2Edit(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	get_line_data(getLineIndex())->endpoint_indexes[1] = atoi(wxConvertWX2MB(event.GetString()));
}


void LinePropDialog::OnLandscape(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	SET_LINE_LANDSCAPE_STATUS(get_line_data(getLineIndex()), event.IsChecked());
}

void LinePropDialog::OnElevation(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	SET_LINE_ELEVATION(get_line_data(getLineIndex()), event.IsChecked());
}


void LinePropDialog::OnVariableElev(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	SET_LINE_ELEVATION(get_line_data(getLineIndex()), event.IsChecked());
}


void LinePropDialog::OnHasTransSide(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	SET_LINE_HAS_TRANSPARENT_SIDE(get_line_data(getLineIndex()), event.IsChecked());
}


void LinePropDialog::OnRadioSel(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	//TODO
}


void LinePropDialog::OnFloor(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	//TODO
}


void LinePropDialog::OnCeiling(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	//TODO
}


void LinePropDialog::OnClockwiseSide(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	//TODO
}


void LinePropDialog::OnCClockwiseSide(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	//TODO
}


void LinePropDialog::OnClockwisePoly(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	//TODO
}


void LinePropDialog::OnCClockwisePoly(wxCommandEvent &event)
{
	if(getLineIndex() == NONE)return;
	//TODO
}


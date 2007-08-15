#include "PointPropDialog.h"
#include "MapEditorWX.h"
enum{
    ID_FLOOR,
    ID_CEILING,
    ID_X,
    ID_Y,
    ID_TX,
    ID_TY,
    ID_POLY_INDEX,
};

BEGIN_EVENT_TABLE(PointPropDialog, wxDialog)
/*
    EVT_TEXT(ID_FLOOR, PointPropDialog::OnEditFloor)
    EVT_TEXT(ID_CEILING, PointPropDialog::OnEditCeiling)
    EVT_TEXT(ID_X, PointPropDialog::OnEditX)
    EVT_TEXT(ID_Y, PointPropDialog::OnEditY)
    EVT_TEXT(ID_TX, PointPropDialog::OnEditTX)
    EVT_TEXT(ID_TY, PointPropDialog::OnEditTY)
    EVT_CHOICE(ID_POLY_INDEX, PointPropDialog::OnPolyChoice)
	*/
	EVT_BUTTON(wxID_OK, OnOk)
	EVT_BUTTON(wxID_CANCEL, OnCancel)
END_EVENT_TABLE()

void PointPropDialog::setIndex(int ind)
{
    this->index = ind;
}

PointPropDialog::PointPropDialog()
{
}
PointPropDialog::~PointPropDialog()
{
}
bool PointPropDialog::Create(wxWindow* parent, wxWindowID id, int endpointIndex)
{
    bool result = wxDialog::Create(parent, id, _T("Point Properties"));
    sizer_52_staticbox = new wxStaticBox(this, -1, wxT("Flags"));
    radio_btn_7 = new wxRadioButton(this, wxID_ANY, wxT("Solid"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radio_btn_8 = new wxRadioButton(this, wxID_ANY, wxT("Transparent"));
    checkbox_40 = new wxCheckBox(this, wxID_ANY, wxT("Elevation"));
    label_29 = new wxStaticText(this, wxID_ANY, wxT("Floor height"));
    text_ctrl_14 = new wxTextCtrl(this, ID_FLOOR, wxEmptyString);
    panel_8 = new wxPanel(this, wxID_ANY);
    label_30 = new wxStaticText(this, wxID_ANY, wxT("Ceiling hegiht"));
    text_ctrl_15 = new wxTextCtrl(this, ID_CEILING, wxEmptyString);
    panel_9 = new wxPanel(this, wxID_ANY);
    label_31 = new wxStaticText(this, wxID_ANY, wxT("Vertex"));
    text_ctrl_16 = new wxTextCtrl(this, ID_X, wxEmptyString);
    text_ctrl_18 = new wxTextCtrl(this, ID_Y, wxEmptyString);
    label_32 = new wxStaticText(this, wxID_ANY, wxT("Transformed"));
    text_ctrl_17 = new wxTextCtrl(this, ID_TX, wxEmptyString);
    text_ctrl_19 = new wxTextCtrl(this, ID_TY, wxEmptyString);
    label_33 = new wxStaticText(this, wxID_ANY, wxT("Supporting polygon index"));
    choice_11 = new wxChoice(this, ID_POLY_INDEX);

	buttonOK = new wxButton(this, wxID_OK, wxEmptyString);
	buttonCancel = new wxButton(this, wxID_CANCEL, wxEmptyString);

    wxFlexGridSizer* grid_sizer_10 = new wxFlexGridSizer(4, 1, 0, 0);
    wxGridSizer* grid_sizer_12 = new wxGridSizer(1, 2, 0, 0);
    wxGridSizer* grid_sizer_11 = new wxGridSizer(4, 3, 0, 0);
    wxStaticBoxSizer* sizer_52 = new wxStaticBoxSizer(sizer_52_staticbox, wxVERTICAL);

	wxGridSizer* grid_sizer_buttons = new wxFlexGridSizer(1, 2, 0, 0);

	sizer_52->Add(radio_btn_7, 0, 0, 0);
    sizer_52->Add(radio_btn_8, 0, 0, 0);
    sizer_52->Add(checkbox_40, 0, 0, 0);
    grid_sizer_10->Add(sizer_52, 1, wxEXPAND, 0);
    grid_sizer_11->Add(label_29, 0, 0, 0);
    grid_sizer_11->Add(text_ctrl_14, 0, 0, 0);
    grid_sizer_11->Add(panel_8, 1, wxEXPAND, 0);
    grid_sizer_11->Add(label_30, 0, 0, 0);
    grid_sizer_11->Add(text_ctrl_15, 0, 0, 0);
    grid_sizer_11->Add(panel_9, 1, wxEXPAND, 0);
    grid_sizer_11->Add(label_31, 0, 0, 0);
    grid_sizer_11->Add(text_ctrl_16, 0, 0, 0);
    grid_sizer_11->Add(text_ctrl_18, 0, 0, 0);
    grid_sizer_11->Add(label_32, 0, 0, 0);
    grid_sizer_11->Add(text_ctrl_17, 0, 0, 0);
    grid_sizer_11->Add(text_ctrl_19, 0, 0, 0);
    grid_sizer_10->Add(grid_sizer_11, 1, wxEXPAND, 0);
    grid_sizer_12->Add(label_33, 0, 0, 0);
    grid_sizer_12->Add(choice_11, 0, 0, 0);
    grid_sizer_10->Add(grid_sizer_12, 1, wxEXPAND, 0);

	grid_sizer_10->Add(grid_sizer_buttons, 1, wxEXPAND, 0);
	grid_sizer_buttons->Add(buttonOK, 0, wxEXPAND, 0);
	grid_sizer_buttons->Add(buttonCancel, 0, wxEXPAND, 0);

    SetSizer(grid_sizer_10);
    grid_sizer_10->Fit(this);
    Layout();

	//�|���S���R���{�Z�b�g�A�b�v
	for(int i = 0; i < (int)PolygonList.size(); i ++){
		//polygon_data* poly = get_polygon_data(i);
		choice_11->Insert(getString("%d", i), i);
	}
	choice_11->Insert(_T("NONE"), (int)PolygonList.size());
	this->setIndex(endpointIndex);
	wxASSERT(hpl::aleph::map::isValidIndex(endpointIndex, EndpointList.size()));
	//�I�𕨂̔��f
	//polygon
	endpoint_data* ep = get_endpoint_data(endpointIndex);
	int sel = ep->supporting_polygon_index;
	wxASSERT(hpl::aleph::map::isValidIndex(sel, PolygonList.size()));
	choice_11->SetSelection(sel == NONE ? (int)EndpointList.size(): sel);

	//flags
	radio_btn_7->SetValue(ENDPOINT_IS_SOLID(ep) != 0);
	radio_btn_8->SetValue(ENDPOINT_IS_TRANSPARENT(ep) != 0);
	checkbox_40->SetValue(ENDPOINT_IS_ELEVATION(ep) != 0);

	//height
	text_ctrl_14->SetValue(getString("%d", ep->highest_adjacent_floor_height));
	text_ctrl_15->SetValue(getString("%d", ep->lowest_adjacent_ceiling_height));
	text_ctrl_16->SetValue(getString("%d", ep->vertex.x));
	text_ctrl_18->SetValue(getString("%d", ep->vertex.y));
	text_ctrl_17->SetValue(getString("%d", ep->transformed.x));
	text_ctrl_19->SetValue(getString("%d", ep->transformed.y));
    return result;
}

/*
void PointPropDialog::OnEditFloor(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (PointPropDialog::OnEditFloor) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void PointPropDialog::OnEditCeiling(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (PointPropDialog::OnEditCeiling) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void PointPropDialog::OnEditX(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (PointPropDialog::OnEdit) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void PointPropDialog::OnEditY(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (PointPropDialog::OnEditY) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void PointPropDialog::OnEditTX(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (PointPropDialog::OnEditTX) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void PointPropDialog::OnEditTY(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (PointPropDialog::OnEditTY) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}


void PointPropDialog::OnPolyChoice(wxCommandEvent &event)
{
    event.Skip();
    std::cout<<"Event handler (PointPropDialog::OnPolyChoice) not implemented yet"<<std::endl; //notify the user that he hasn't implemented the event handler yet
}
*/

int PointPropDialog::getIndex()
{
    return this->index;
}
endpoint_data PointPropDialog::getEndpoint()
{
	endpoint_data data;
	int sel = choice_11->GetSelection();
	if(sel < 0 || sel >= (int)PolygonList.size()){
		sel = NONE;
	}
	data.supporting_polygon_index = sel;

	//flags
	SET_ENDPOINT_SOLIDITY(&data, radio_btn_7->GetValue());
	SET_ENDPOINT_TRANSPARENCY(&data, radio_btn_8->GetValue());
	SET_ENDPOINT_ELEVATION(&data, checkbox_40->GetValue());

	//height
	data.highest_adjacent_floor_height = atoi(text_ctrl_14->GetValue().mb_str());
	data.lowest_adjacent_ceiling_height = atoi(text_ctrl_15->GetValue().mb_str());
	data.vertex.x = atoi(text_ctrl_16->GetValue().mb_str());
	data.vertex.y = atoi(text_ctrl_18->GetValue().mb_str());
	data.transformed.x = atoi(text_ctrl_17->GetValue().mb_str());
	data.transformed.y = atoi(text_ctrl_19->GetValue().mb_str());
	return data;
}
void PointPropDialog::OnOk(wxCommandEvent &ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void PointPropDialog::OnCancel(wxCommandEvent &ev)
{
    SetReturnCode(wxID_CANCEL);
    Destroy();
}
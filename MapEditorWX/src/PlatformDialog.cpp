#include "PlatformDialog.h"
#include "MapEditorWX.h"

BEGIN_EVENT_TABLE(PlatformDialog, wxDialog)
    EVT_BUTTON(wxID_OK, PlatformDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, PlatformDialog::OnCancel)
END_EVENT_TABLE()
PlatformDialog::PlatformDialog()
{
}
PlatformDialog::~PlatformDialog()
{
}
bool PlatformDialog::Create(wxWindow* parent, wxWindowID id, int pindex)
{
    bool result = wxDialog::Create(parent, id, _T("Platform"));

    //create
    sizer_11_staticbox = new wxStaticBox(this, -1, wxT("Controlled by"));
    sizer_12_staticbox = new wxStaticBox(this, -1, wxT("When Bites"));
    sizer_19_staticbox = new wxStaticBox(this, -1, wxT("Open"));
    sizer_28_staticbox = new wxStaticBox(this, -1, wxT("Activates"));
    sizer_27_staticbox = new wxStaticBox(this, -1, wxT("Deactivates"));
    sizer_31_staticbox = new wxStaticBox(this, -1, wxT("Misc"));
    sizer_10_staticbox = new wxStaticBox(this, -1, wxT("Initially"));
    label_1 = new wxStaticText(this, wxID_ANY, wxT("Type"));
    /*const wxString choice_1_choices[] = {
        
    };*/
    choice_1 = new wxChoice(this, wxID_ANY);//, wxDefaultPosition, wxDefaultSize, 0, choice_1_choices, 0);
    label_2 = new wxStaticText(this, wxID_ANY, wxT("Speed"));
    text_ctrl_1 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    /*const wxString choice_2_choices[] = {
        
    };*/
    choice_2 = new wxChoice(this, wxID_ANY);//, wxDefaultPosition, wxDefaultSize, 0, choice_2_choices, 0);
    label_3 = new wxStaticText(this, wxID_ANY, wxT("Delay"));
    text_ctrl_2 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    /*const wxString choice_3_choices[] = {
        
    };*/
    choice_3 = new wxChoice(this, wxID_ANY);//, wxDefaultPosition, wxDefaultSize, 0, choice_3_choices, 0);
    checkbox_7 = new wxCheckBox(this, wxID_ANY, wxT("Auto Calc Min Height"));
    label_4 = new wxStaticText(this, wxID_ANY, wxT("Min Height"));
    text_ctrl_3 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    checkbox_8 = new wxCheckBox(this, wxID_ANY, wxT("Auto Clac Max Height"));
    label_5 = new wxStaticText(this, wxID_ANY, wxT("Max Height"));
    text_ctrl_4 = new wxTextCtrl(this, wxID_ANY, wxEmptyString);
    checkbox_1 = new wxCheckBox(this, wxID_ANY, wxT("Active"));
    checkbox_2 = new wxCheckBox(this, wxID_ANY, wxT("Opened"));
    checkbox_3 = new wxCheckBox(this, wxID_ANY, wxT("Player"));
    checkbox_4 = new wxCheckBox(this, wxID_ANY, wxT("Aliens"));
    checkbox_5 = new wxCheckBox(this, wxID_ANY, wxT("Causes Damage"));
    checkbox_6 = new wxCheckBox(this, wxID_ANY, wxT("Reverse"));
    checkbox_9 = new wxCheckBox(this, wxID_ANY, wxT("Door"));
    label_6 = new wxStaticText(this, wxID_ANY, wxT("Default Preset"));
/*    const wxString choice_4_choices[] = {
        
    };*/
    choice_4 = new wxChoice(this, wxID_ANY);//, wxDefaultPosition, wxDefaultSize, 0, choice_4_choices, 0);
    radio_btn_1 = new wxRadioButton(this, wxID_ANY, wxT("From Floor"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radio_btn_2 = new wxRadioButton(this, wxID_ANY, wxT("From Ceiling"));
    radio_btn_3 = new wxRadioButton(this, wxID_ANY, wxT("From Both"));
    checkbox_10 = new wxCheckBox(this, wxID_ANY, wxT("Floor to Ceiling"));
    label_7 = new wxStaticText(this, wxID_ANY, wxT("Copy from"));
/*    const wxString choice_5_choices[] = {
        
    };*/
    choice_5 = new wxChoice(this, wxID_ANY);//, wxDefaultPosition, wxDefaultSize, 0, choice_5_choices, 0);
    checkbox_15 = new wxCheckBox(this, wxID_ANY, wxT("Only once"));
    checkbox_16 = new wxCheckBox(this, wxID_ANY, wxT("Activates polygon lights"));
    checkbox_17 = new wxCheckBox(this, wxID_ANY, wxT("Activates adjacent polygon"));
    checkbox_18 = new wxCheckBox(this, wxID_ANY, wxT("Deactivates adjacent polygon"));
    checkbox_19 = new wxCheckBox(this, wxID_ANY, wxT("Adjacent at each level"));
    label_8 = new wxStaticText(this, wxID_ANY, wxT("Tag"));
/*  const wxString choice_6_choices[] = {
        
    };*/
    choice_6 = new wxChoice(this, wxID_ANY);//, wxDefaultPosition, wxDefaultSize, 0, choice_6_choices, 0);
    radio_btn_4 = new wxRadioButton(this, wxID_ANY, wxT("Never"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radio_btn_5 = new wxRadioButton(this, wxID_ANY, wxT("At each level"));
    radio_btn_6 = new wxRadioButton(this, wxID_ANY, wxT("At initial level"));
    checkbox_12 = new wxCheckBox(this, wxID_ANY, wxT("Deactivates polygon lights"));
    checkbox_13 = new wxCheckBox(this, wxID_ANY, wxT("Deactivates adjacent platform"));
    checkbox_14 = new wxCheckBox(this, wxID_ANY, wxT("Activates adjacent platform"));
    checkbox_20 = new wxCheckBox(this, wxID_ANY, wxT("Can't deactivate extenally"));
    checkbox_21 = new wxCheckBox(this, wxID_ANY, wxT("Uses native polygon heights"));
    checkbox_22 = new wxCheckBox(this, wxID_ANY, wxT("Delay befire activation"));
    checkbox_24 = new wxCheckBox(this, wxID_ANY, wxT("Doesn't activate parent"));
    checkbox_23 = new wxCheckBox(this, wxID_ANY, wxT("Contracts slower"));
    checkbox_25 = new wxCheckBox(this, wxID_ANY, wxT("Locked"));
    checkbox_26 = new wxCheckBox(this, wxID_ANY, wxT("Secret"));
    button_1 = new wxButton(this, wxID_OK, wxT("OK"));
    button_2 = new wxButton(this, wxID_CANCEL, wxT("Cancel"));

    //prefs
    label_2->SetMinSize(wxSize(35, 14));
    text_ctrl_1->SetMinSize(wxSize(60, -1));
    choice_2->SetMinSize(wxSize(80, -1));
    label_3->SetMinSize(wxSize(35, 14));
    text_ctrl_2->SetMinSize(wxSize(60, -1));
    choice_3->SetMinSize(wxSize(90, -1));
    label_4->SetMinSize(wxSize(61, 14));
    label_5->SetMinSize(wxSize(61, 14));

    //layout
    wxFlexGridSizer* sizer_1 = new wxFlexGridSizer(2, 1, 0, 0);
    wxBoxSizer* sizer_21 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* sizer_30 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* sizer_32 = new wxFlexGridSizer(1, 2, 0, 0);
    wxStaticBoxSizer* sizer_31 = new wxStaticBoxSizer(sizer_31_staticbox, wxVERTICAL);
    wxStaticBoxSizer* sizer_27 = new wxStaticBoxSizer(sizer_27_staticbox, wxVERTICAL);
    wxFlexGridSizer* sizer_26 = new wxFlexGridSizer(2, 1, 0, 0);
    wxFlexGridSizer* sizer_29 = new wxFlexGridSizer(1, 2, 0, 0);
    wxStaticBoxSizer* sizer_28 = new wxStaticBoxSizer(sizer_28_staticbox, wxVERTICAL);
    wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* sizer_16 = new wxFlexGridSizer(3, 1, 0, 0);
    wxBoxSizer* sizer_18 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_20 = new wxBoxSizer(wxVERTICAL);
    wxStaticBoxSizer* sizer_19 = new wxStaticBoxSizer(sizer_19_staticbox, wxVERTICAL);
    wxBoxSizer* sizer_17 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* sizer_3 = new wxFlexGridSizer(2, 1, 0, 0);
    wxBoxSizer* sizer_4 = new wxBoxSizer(wxHORIZONTAL);
    wxStaticBoxSizer* sizer_12 = new wxStaticBoxSizer(sizer_12_staticbox, wxVERTICAL);
    wxStaticBoxSizer* sizer_11 = new wxStaticBoxSizer(sizer_11_staticbox, wxVERTICAL);
    wxStaticBoxSizer* sizer_10 = new wxStaticBoxSizer(sizer_10_staticbox, wxVERTICAL);
    wxBoxSizer* sizer_5 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_13 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_15 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_14 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_6 = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* sizer_9 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer* sizer_8 = new wxBoxSizer(wxHORIZONTAL);
    wxFlexGridSizer* sizer_7 = new wxFlexGridSizer(1, 2, 0, 0);
    sizer_7->Add(label_1, 0, 0, 0);
    sizer_7->Add(choice_1, 0, 0, 0);
    sizer_6->Add(sizer_7, 1, wxEXPAND, 0);
    sizer_8->Add(label_2, 0, 0, 0);
    sizer_8->Add(text_ctrl_1, 0, 0, 0);
    sizer_8->Add(choice_2, 0, 0, 0);
    sizer_6->Add(sizer_8, 1, 0, 0);
    sizer_9->Add(label_3, 0, 0, 0);
    sizer_9->Add(text_ctrl_2, 0, 0, 0);
    sizer_9->Add(choice_3, 0, 0, 0);
    sizer_6->Add(sizer_9, 1, 0, 0);
    sizer_5->Add(sizer_6, 1, wxEXPAND, 0);
    sizer_13->Add(checkbox_7, 0, 0, 0);
    sizer_14->Add(label_4, 0, 0, 0);
    sizer_14->Add(text_ctrl_3, 0, 0, 0);
    sizer_13->Add(sizer_14, 1, 0, 0);
    sizer_13->Add(checkbox_8, 0, 0, 0);
    sizer_15->Add(label_5, 0, 0, 0);
    sizer_15->Add(text_ctrl_4, 0, 0, 0);
    sizer_13->Add(sizer_15, 1, 0, 0);
    sizer_5->Add(sizer_13, 1, 0, 0);
    sizer_3->Add(sizer_5, 1, wxEXPAND, 0);
    sizer_10->Add(checkbox_1, 0, 0, 0);
    sizer_10->Add(checkbox_2, 0, 0, 0);
    sizer_4->Add(sizer_10, 1, wxEXPAND, 0);
    sizer_11->Add(checkbox_3, 0, 0, 0);
    sizer_11->Add(checkbox_4, 0, 0, 0);
    sizer_4->Add(sizer_11, 1, wxEXPAND, 0);
    sizer_12->Add(checkbox_5, 0, 0, 0);
    sizer_12->Add(checkbox_6, 0, 0, 0);
    sizer_4->Add(sizer_12, 1, wxEXPAND, 0);
    sizer_3->Add(sizer_4, 1, wxEXPAND, 0);
    sizer_2->Add(sizer_3, 1, wxEXPAND, 0);
    sizer_16->Add(checkbox_9, 0, 0, 0);
    sizer_17->Add(label_6, 0, 0, 0);
    sizer_17->Add(choice_4, 0, 0, 0);
    sizer_16->Add(sizer_17, 1, wxEXPAND, 0);
    sizer_19->Add(radio_btn_1, 0, 0, 0);
    sizer_19->Add(radio_btn_2, 0, 0, 0);
    sizer_19->Add(radio_btn_3, 0, 0, 0);
    sizer_19->Add(checkbox_10, 0, 0, 0);
    sizer_18->Add(sizer_19, 1, wxEXPAND, 0);
    sizer_20->Add(label_7, 0, 0, 0);
    sizer_20->Add(choice_5, 0, 0, 0);
    sizer_18->Add(sizer_20, 1, wxEXPAND, 0);
    sizer_16->Add(sizer_18, 1, wxEXPAND, 0);
    sizer_2->Add(sizer_16, 1, wxEXPAND, 0);
    sizer_1->Add(sizer_2, 1, wxEXPAND, 0);
    sizer_28->Add(checkbox_15, 0, 0, 0);
    sizer_28->Add(checkbox_16, 0, 0, 0);
    sizer_28->Add(checkbox_17, 0, 0, 0);
    sizer_28->Add(checkbox_18, 0, 0, 0);
    sizer_28->Add(checkbox_19, 0, 0, 0);
    sizer_26->Add(sizer_28, 1, wxEXPAND, 0);
    sizer_29->Add(label_8, 0, 0, 0);
    sizer_29->Add(choice_6, 0, 0, 0);
    sizer_26->Add(sizer_29, 1, wxEXPAND, 0);
    sizer_21->Add(sizer_26, 1, wxEXPAND, 0);
    sizer_27->Add(radio_btn_4, 0, 0, 0);
    sizer_27->Add(radio_btn_5, 0, 0, 0);
    sizer_27->Add(radio_btn_6, 0, 0, 0);
    sizer_27->Add(checkbox_12, 0, 0, 0);
    sizer_27->Add(checkbox_13, 0, 0, 0);
    sizer_27->Add(checkbox_14, 0, 0, 0);
    sizer_21->Add(sizer_27, 1, wxEXPAND, 0);
    sizer_31->Add(checkbox_20, 0, 0, 0);
    sizer_31->Add(checkbox_21, 0, 0, 0);
    sizer_31->Add(checkbox_22, 0, 0, 0);
    sizer_31->Add(checkbox_24, 0, 0, 0);
    sizer_31->Add(checkbox_23, 0, 0, 0);
    sizer_31->Add(checkbox_25, 0, 0, 0);
    sizer_31->Add(checkbox_26, 0, 0, 0);
    sizer_30->Add(sizer_31, 1, wxEXPAND, 0);
    sizer_32->Add(button_1, 0, 0, 0);
    sizer_32->Add(button_2, 0, 0, 0);
    sizer_30->Add(sizer_32, 1, wxEXPAND, 0);
    sizer_21->Add(sizer_30, 1, 0, 0);
    sizer_1->Add(sizer_21, 1, wxEXPAND, 0);
    SetSizer(sizer_1);
    sizer_1->Fit(this);
    Layout();

    polyIndex = pindex;
	platform_data *platform = NULL;
	platform_data dummy;
	memset(&dummy, 0, sizeof(platform_data));

    //polygon_data* poly = get_polygon_data(polyIndex);
	if(polyIndex == NONE){
		platformIndex = NONE;
		platform = &dummy;
	}else{

		//search polygon's platform
		platformIndex = NONE;
		for(int i = 0; i < (int)PlatformList.size(); i ++){
			platform_data* temp = &PlatformList[i];
			if(temp->polygon_index == polyIndex){
				platformIndex = i;
				break;
			}
		}
#ifdef __WXDEBUG__
	    wxASSERT(platformIndex != NONE);
#endif

		platform = &PlatformList[platformIndex];
	}

    //チョイスの初期化 init choices
	//Type choice
	for(int i = 0; i < NUMBER_OF_PLATFORM_TYPES; i ++){
		choice_1->Append(wxConvertMB2WX(wxGetApp().platformTypeInfo[i].jname.c_str()));
	}
	//Speed	choice
	for(int i = 0; i < NUMBER_OF_PLATFORM_SPEEDS; i ++){
		choice_2->Append(wxConvertMB2WX(wxGetApp().platformSpeedInfo[i].jname.c_str()));
	}
	choice_2->Append(_T("Other"));
	//Delay choice
	for(int i = 0; i < NUMBER_OF_PLATFORM_DELAYS; i ++){
		choice_3->Append(wxConvertMB2WX(wxGetApp().platformDelayInfo[i].jname.c_str()));
	}
	choice_3->Append(_T("Other"));
	
	//TODO tags
	//TODO presets

	//copy from (ほかのプラットフォームインデックスを追加？)
	for(int i = 0; i < (int)PlatformList.size(); i ++){
		if(polyIndex != NONE && platformIndex != NONE && i == platformIndex){
			//自分は除外
			continue;
		}
		choice_5->Append(getString("%d", i));
	}
	
    //TODO 値の設定
	//Type
	choice_1->SetSelection(platform->type);
	//Speed
	//インデックス値を取得
	int spdIndex = hpl::aleph::getIndexFromInformationBinded(platform->speed, wxGetApp().platformSpeedInfo,
		NUMBER_OF_PLATFORM_SPEEDS);
	if(spdIndex >= 0){
		choice_2->SetSelection(spdIndex);
	}else{
		choice_2->SetSelection(NUMBER_OF_PLATFORM_SPEEDS);
	}
	//値を設定
    text_ctrl_1->SetValue(getString("%d", platform->speed));

	//Delay
	//インデックス値を取得
	int delayIndex = hpl::aleph::getIndexFromInformationBinded(platform->delay,
		wxGetApp().platformDelayInfo,
		NUMBER_OF_PLATFORM_DELAYS);
	if(delayIndex >= 0){
		choice_3->SetSelection(delayIndex);
	}else{
		choice_3->SetSelection(NUMBER_OF_PLATFORM_DELAYS);
	}
	//値を設定
	text_ctrl_2->SetValue(getString("%d", platform->delay));

	//height
	text_ctrl_3->SetValue(getString("%d", platform->minimum_floor_height));
	text_ctrl_4->SetValue(getString("%d", platform->maximum_ceiling_height));

	//initially
	checkbox_1->SetValue(PLATFORM_IS_INITIALLY_ACTIVE(platform));
	checkbox_2->SetValue(PLATFORM_IS_INITIALLY_EXTENDED(platform));
	//Controlled by
	checkbox_3->SetValue(PLATFORM_IS_PLAYER_CONTROLLABLE(platform));
	checkbox_4->SetValue(PLATFORM_IS_MONSTER_CONTROLLABLE(platform));
	//Bites!
	checkbox_5->SetValue(PLATFORM_CAUSES_DAMAGE(platform));
	checkbox_6->SetValue(PLATFORM_REVERSES_DIRECTION_WHEN_OBSTRUCTED(platform));

	//Door
	checkbox_9->SetValue(PLATFORM_IS_DOOR(platform));

	//TODO radio button

	//Activates
	checkbox_15->SetValue(PLATFORM_ACTIVATES_ONLY_ONCE(platform));
	checkbox_16->SetValue(PLATFORM_DEACTIVATES_LIGHT(platform));
	checkbox_17->SetValue(PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_WHEN_ACTIVATING(platform));
	checkbox_18->SetValue(PLATFORM_DEACTIVATES_ADJACENT_PLATFORMS_WHEN_ACTIVATING(platform));
	checkbox_19->SetValue(PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_AT_EACH_LEVEL(platform));
	//Deactivates
	bool deactivateEachLevel = PLATFORM_DEACTIVATES_AT_EACH_LEVEL(platform);
	bool deactivateInitialLevel = PLATFORM_DEACTIVATES_AT_INITIAL_LEVEL(platform);
	if(!deactivateEachLevel && !deactivateInitialLevel){
		radio_btn_4->SetValue(true);
	}else if(deactivateEachLevel){
		radio_btn_5->SetValue(true);
	}else{
		radio_btn_6->SetValue(true);
	}

	//Open
	if(
    return result;
}

void PlatformDialog::OnOk(wxCommandEvent& ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void PlatformDialog::OnCancel(wxCommandEvent& ev)
{
    //
    SetReturnCode(wxID_CANCEL);
    Destroy();
}

platform_data PlatformDialog::getPlatform()
{
	platform_data data;
	data.polygon_index = polyIndex;

	return data;
}

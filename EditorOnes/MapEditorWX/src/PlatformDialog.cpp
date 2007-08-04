#include "PlatformDialog.h"
#include "MapEditorWX.h"

/*
	�X�s�[�h���f�B���C��
	�`���C�X����I�������
	���̒l���e�L�X�g�R���g���[���ɓ�����A
	�e�L�X�g�R���g���[���𑀍삷���
	�`���C�X��"Other"�ɂȂ�
	���[�v����댯������̂ŁA
	�`���C�X��ύX����Ƃ���
	�l���ς��Ƃ��݂̂ɂ��邱�ƁB


	Auto height calclation is
	�������x�v�Z�̃`�F�b�N�{�b�N�X��
	�`�F�b�N������ƃe�L�X�g��
	�אڂ���Œፂ�x�̃|���S���ɍ�����
	���킹�܂��B

	�܂��A�C������Ǝ����v�Z�`�F�b�N��
	�͂����܂�


*/
enum{
	ID_SPEED_CHOICE,
	ID_DELAY_CHOICE,
	ID_SPEED,
	ID_DELAY,
	ID_AUTO_CALC_MIN_HEIGHT,
	ID_AUTO_CALC_MAX_HEIGHT,
	ID_MIN_HEIGHT,
	ID_MAX_HEIGHT,
	ID_COPY_FROM,
	ID_TAG,
	ID_PRESET,
};

BEGIN_EVENT_TABLE(PlatformDialog, wxDialog)
    EVT_BUTTON(wxID_OK, PlatformDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, PlatformDialog::OnCancel)
	EVT_CHOICE(ID_SPEED_CHOICE, PlatformDialog::OnSpeedChoice)
	EVT_CHOICE(ID_DELAY_CHOICE, PlatformDialog::OnDelayChoice)
	EVT_TEXT(ID_SPEED, PlatformDialog::OnSpeed)
	EVT_TEXT(ID_DELAY, PlatformDialog::OnDelay)
	EVT_CHECKBOX(ID_AUTO_CALC_MIN_HEIGHT, PlatformDialog::OnAutoMin)
	EVT_CHECKBOX(ID_AUTO_CALC_MAX_HEIGHT, PlatformDialog::OnAutoMax)
	EVT_TEXT(ID_MIN_HEIGHT, PlatformDialog::OnMinHeight)
	EVT_TEXT(ID_MAX_HEIGHT, PlatformDialog::OnMaxHeight)
	EVT_CHOICE(ID_COPY_FROM, PlatformDialog::OnCopyFrom)
	EVT_CHOICE(ID_TAG, PlatformDialog::OnTag)
	EVT_CHOICE(ID_PRESET, PlatformDialog::OnPreset)
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
	//type
    choice_1 = new wxChoice(this, wxID_ANY);//, wxDefaultPosition, wxDefaultSize, 0, choice_1_choices, 0);
	//speed
    label_2 = new wxStaticText(this, wxID_ANY, wxT("Speed"));
    text_ctrl_1 = new wxTextCtrl(this, ID_SPEED, wxEmptyString);
    /*const wxString choice_2_choices[] = {
        
    };*/
    choice_2 = new wxChoice(this, ID_SPEED_CHOICE);//, wxDefaultPosition, wxDefaultSize, 0, choice_2_choices, 0);
	//delay
    label_3 = new wxStaticText(this, wxID_ANY, wxT("Delay"));
    text_ctrl_2 = new wxTextCtrl(this, ID_DELAY, wxEmptyString);
    /*const wxString choice_3_choices[] = {
        
    };*/
    choice_3 = new wxChoice(this, ID_DELAY_CHOICE);//, wxDefaultPosition, wxDefaultSize, 0, choice_3_choices, 0);
    checkbox_7 = new wxCheckBox(this, ID_AUTO_CALC_MIN_HEIGHT, wxT("Auto Calc Min Height"));
    label_4 = new wxStaticText(this, wxID_ANY, wxT("Min Height"));
    text_ctrl_3 = new wxTextCtrl(this, ID_MIN_HEIGHT, wxEmptyString);
    checkbox_8 = new wxCheckBox(this, ID_AUTO_CALC_MAX_HEIGHT, wxT("Auto Clac Max Height"));
    label_5 = new wxStaticText(this, wxID_ANY, wxT("Max Height"));
    text_ctrl_4 = new wxTextCtrl(this, ID_MAX_HEIGHT, wxEmptyString);

	//check box
	//Initially
    checkbox_1 = new wxCheckBox(this, wxID_ANY, wxT("Active"));
    checkbox_2 = new wxCheckBox(this, wxID_ANY, wxT("Opened"));
    checkbox_3 = new wxCheckBox(this, wxID_ANY, wxT("Player"));
    checkbox_4 = new wxCheckBox(this, wxID_ANY, wxT("Aliens"));
    checkbox_5 = new wxCheckBox(this, wxID_ANY, wxT("Causes Damage"));
    checkbox_6 = new wxCheckBox(this, wxID_ANY, wxT("Reverse"));
    checkbox_9 = new wxCheckBox(this, wxID_ANY, wxT("Door"));
    label_6 = new wxStaticText(this, ID_PRESET, wxT("Default Preset"));
/*    const wxString choice_4_choices[] = {
        
    };*/
    choice_4 = new wxChoice(this, wxID_ANY);//, wxDefaultPosition, wxDefaultSize, 0, choice_4_choices, 0);
    radio_btn_1 = new wxRadioButton(this, wxID_ANY, wxT("From Floor"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    radio_btn_2 = new wxRadioButton(this, wxID_ANY, wxT("From Ceiling"));
    radio_btn_3 = new wxRadioButton(this, wxID_ANY, wxT("From Both"));
    checkbox_10 = new wxCheckBox(this, wxID_ANY, wxT("Floor to Ceiling"));
    label_7 = new wxStaticText(this, ID_COPY_FROM, wxT("Copy from"));
/*    const wxString choice_5_choices[] = {
        
    };*/
    choice_5 = new wxChoice(this, wxID_ANY);//, wxDefaultPosition, wxDefaultSize, 0, choice_5_choices, 0);
    checkbox_15 = new wxCheckBox(this, wxID_ANY, wxT("Only once"));
    checkbox_16 = new wxCheckBox(this, wxID_ANY, wxT("Activates polygon lights"));
    checkbox_17 = new wxCheckBox(this, wxID_ANY, wxT("Activates adjacent polygon"));
    checkbox_18 = new wxCheckBox(this, wxID_ANY, wxT("Deactivates adjacent polygon"));
    checkbox_19 = new wxCheckBox(this, wxID_ANY, wxT("Adjacent at each level"));
    label_8 = new wxStaticText(this, ID_TAG, wxT("Tag"));
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
    checkbox_22 = new wxCheckBox(this, wxID_ANY, wxT("Delay before activation"));
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
	memset(&dummy, 0, SIZEOF_platform_data);

	if(!hpl::aleph::map::isValidIndex(polyIndex, PolygonList.size())){
		//invalid
		platformIndex = NONE;
		platform = &dummy;
	}else{
		//valid number
		hpl::aleph::HPLStockManager* smgr = wxGetApp().getStockManager();
		//search polygon's platform
		platformIndex = hpl::aleph::map::getPlatformIndexFromPolygonIndex(polyIndex, smgr);
#ifdef __WXDEBUG__
	    wxASSERT(hpl::aleph::map::isValidIndex(platformIndex,
			PlatformList.size()));
#endif

		platform = &PlatformList[platformIndex];
	}

    //�`���C�X�̏����� init choices
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

	//copy from (�ق��̃v���b�g�t�H�[���C���f�b�N�X��ǉ��H)
	for(int i = 0; i < (int)PlatformList.size(); i ++){
		if(hpl::aleph::map::isValidIndex(polyIndex, PolygonList.size()) &&
			hpl::aleph::map::isValidIndex(platformIndex, PlatformList.size()) &&
			i == platformIndex)
		{
			//�����͏��O
			continue;
		}
		choice_5->Append(getString("%d", i));
	}
	
    //TODO �l�̐ݒ�
	//Type
	choice_1->SetSelection(platform->type);
	//Speed
	//�C���f�b�N�X�l���擾
	int spdIndex = hpl::aleph::getIndexFromInformationBinded(platform->speed, wxGetApp().platformSpeedInfo,
		NUMBER_OF_PLATFORM_SPEEDS);
	if(spdIndex >= 0){
		choice_2->SetSelection(spdIndex);
	}else{
		choice_2->SetSelection(NUMBER_OF_PLATFORM_SPEEDS);
	}
	//�l��ݒ�
    text_ctrl_1->SetValue(getString("%d", platform->speed));

	//Delay
	//�C���f�b�N�X�l���擾
	int delayIndex = hpl::aleph::getIndexFromInformationBinded(platform->delay,
		wxGetApp().platformDelayInfo,
		NUMBER_OF_PLATFORM_DELAYS);
	if(delayIndex >= 0){
		choice_3->SetSelection(delayIndex);
	}else{
		choice_3->SetSelection(NUMBER_OF_PLATFORM_DELAYS);
	}
	//�l��ݒ�
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
	checkbox_12->SetValue(PLATFORM_DEACTIVATES_LIGHT(platform));
	checkbox_13->SetValue(PLATFORM_DEACTIVATES_ADJACENT_PLATFORMS_WHEN_DEACTIVATING(platform));
	checkbox_14->SetValue(PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_WHEN_DEACTIVATING(platform));

	//Misc
	checkbox_20->SetValue(PLATFORM_CANNOT_BE_EXTERNALLY_DEACTIVATED(platform));
	checkbox_21->SetValue(PLATFORM_USES_NATIVE_POLYGON_HEIGHTS(platform));
	checkbox_22->SetValue(PLATFORM_DELAYS_BEFORE_ACTIVATION(platform));
	checkbox_24->SetValue(PLATFORM_DOES_NOT_ACTIVATE_PARENT(platform));
	checkbox_23->SetValue(PLATFORM_CONTRACTS_SLOWER(platform));
	checkbox_25->SetValue(PLATFORM_IS_LOCKED(platform));
	checkbox_26->SetValue(PLATFORM_IS_SECRET(platform));

	//Open
	if(PLATFORM_GOES_BOTH_WAYS(platform)){
		//�������炭��
		radio_btn_3->SetValue(true);
	}else if(PLATFORM_COMES_FROM_CEILING(platform)){
		//�V�䂩��
		radio_btn_2->SetValue(true);
	}else{
		//�n�ʂ̕�����
		radio_btn_1->SetValue(true);
	}
	checkbox_10->SetValue(PLATFORM_EXTENDS_FLOOR_TO_CEILING(platform));

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
	
	//TODO get height
	data.type = this->choice_1->GetSelection();
	int spdIndex = this->choice_2->GetSelection();
	int speed = 0;
	if(spdIndex < NUMBER_OF_PLATFORM_TYPES){
		//���ꂼ��̋K��̒l���擾����
		speed = wxGetApp().platformSpeedInfo[spdIndex].bind;
	}else{
		//�e�L�X�g�{�b�N�X�̒l��p����
		speed = atoi(wxConvertWX2MB(text_ctrl_1->GetValue()));
	}
	data.speed = speed;
	//delay
	int delayIndex = this->choice_3->GetSelection();
	int delay = 0;
	if(delayIndex < NUMBER_OF_PLATFORM_DELAYS){
		delay = wxGetApp().platformDelayInfo[delayIndex].bind;
	}else{
		delay = atoi(wxConvertWX2MB(text_ctrl_2->GetValue()));
	}
	data.delay = delay;

	//TODO HEIGHT
	bool isAutoMin = this->checkbox_7->GetValue();
	bool isAutoMax = this->checkbox_8->GetValue();
	//text_ctrl_3
	//text_ctrl_4

	//door
	SET_PLATFORM_IS_DOOR(&data, this->checkbox_9->GetValue());

	//Open
	{
		bool fromFloor = this->radio_btn_1->GetValue();
		bool fromCeiling = this->radio_btn_2->GetValue();
		bool fromBoth = this->radio_btn_3->GetValue();
		if(fromFloor){
			SET_PLATFORM_COMES_FROM_FLOOR(&data, true);
			SET_PLATFORM_COMES_FROM_CEILING(&data, false);
		}else if(fromCeiling){
			SET_PLATFORM_COMES_FROM_FLOOR(&data, false);
			SET_PLATFORM_COMES_FROM_CEILING(&data, true);
		}else{
			SET_PLATFORM_COMES_FROM_FLOOR(&data, true);
			SET_PLATFORM_COMES_FROM_CEILING(&data, true);
		}
		SET_PLATFORM_EXTENDS_FLOOR_TO_CEILING(&data,
			this->checkbox_10->GetValue());
	}

	//Initially
	{
		SET_PLATFORM_IS_INITIALLY_ACTIVE(&data,
			checkbox_1->GetValue());
		SET_PLATFORM_IS_INITIALLY_EXTENDED(&data,
			checkbox_2->GetValue());
	}

	//Controlled by
	{
		SET_PLATFORM_IS_PLAYER_CONTROLLABLE(&data,
			checkbox_3->GetValue());
		SET_PLATFORM_IS_MONSTER_CONTROLLABLE(&data,
			checkbox_4->GetValue());
	}

	//When bites
	{
		SET_PLATFORM_CAUSES_DAMAGE(&data,
			checkbox_5->GetValue());
		SET_PLATFORM_REVERSES_DIRECTION_WHEN_OBSTRUCTED(&data,
			checkbox_6->GetValue());
	}

	//Activates
	{
		SET_PLATFORM_ACTIVATES_ONLY_ONCE(&data,
			checkbox_15->GetValue());
		SET_PLATFORM_ACTIVATES_LIGHT(&data,
			checkbox_16->GetValue());
		SET_PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_WHEN_ACTIVATING(&data,
			checkbox_17->GetValue());
		SET_PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_WHEN_DEACTIVATING(&data,
			checkbox_18->GetValue());
		SET_PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_AT_EACH_LEVEL(&data,
			checkbox_19->GetValue());
	}

	//Deactivates
	{
		bool never = radio_btn_4->GetValue();
		bool atEachLevel = radio_btn_5->GetValue();
		bool atInitialLevel = radio_btn_6->GetValue();
		if(never){
			SET_PLATFORM_DEACTIVATES_AT_EACH_LEVEL(&data, false);
			SET_PLATFORM_DEACTIVATES_AT_INITIAL_LEVEL(&data, false);
		}else if(atEachLevel){
			SET_PLATFORM_DEACTIVATES_AT_EACH_LEVEL(&data, true);
			SET_PLATFORM_DEACTIVATES_AT_INITIAL_LEVEL(&data, false);
		}else{
			SET_PLATFORM_DEACTIVATES_AT_EACH_LEVEL(&data, false);
			SET_PLATFORM_DEACTIVATES_AT_INITIAL_LEVEL(&data, true);
		}
		SET_PLATFORM_DEACTIVATES_LIGHT(&data,
			checkbox_12->GetValue());
		SET_PLATFORM_DEACTIVATES_ADJACENT_PLATFORMS_WHEN_DEACTIVATING(&data,
			checkbox_13->GetValue());
		SET_PLATFORM_ACTIVATES_ADJACENT_PLATFORMS_WHEN_DEACTIVATING(&data,
			checkbox_14->GetValue());
	}

	//Misc
	{
		SET_PLATFORM_CANNOT_BE_EXTERNALLY_DEACTIVATED(&data,
			checkbox_20->GetValue());
		SET_PLATFORM_USES_NATIVE_POLYGON_HEIGHTS(&data,
			checkbox_21->GetValue());
		SET_PLATFORM_DELAYS_BEFORE_ACTIVATION(&data,
			checkbox_22->GetValue());
		SET_PLATFORM_DOES_NOT_ACTIVATE_PARENT(&data,
			checkbox_24->GetValue());
		SET_PLATFORM_CONTRACTS_SLOWER(&data,
			checkbox_23->GetValue());
		SET_PLATFORM_IS_LOCKED(&data,
			checkbox_25->GetValue());
		SET_PLATFORM_IS_SECRET(&data,
			checkbox_26->GetValue());
	}
	return data;
}

void PlatformDialog::OnSpeedChoice(wxCommandEvent& ev)
{
	int sel = ev.GetSelection();
	if(sel < NUMBER_OF_PLATFORM_SPEEDS){
		//Other �ȊO�Ȃ琔�l��ύX
		int value = wxGetApp().platformSpeedInfo[sel].bind;
		text_ctrl_1->SetValue(getString("%d", value));
	}
}
void PlatformDialog::OnDelayChoice(wxCommandEvent& ev)
{
	int sel = ev.GetSelection();
	if(sel < NUMBER_OF_PLATFORM_DELAYS){
		//Other �ȊO�Ȃ琔�l��ύX
		int value = wxGetApp().platformDelayInfo[sel].bind;
		text_ctrl_2->SetValue(getString("%d", value));
	}
}
void PlatformDialog::OnSpeed(wxCommandEvent& ev)
{
	static int oldNum = 0;
	int num = atoi(wxConvertWX2MB(text_ctrl_1->GetValue()));
	if(num != oldNum){
		//�`���C�X��ύX
		int index = hpl::aleph::getIndexFromInformationBinded(
			num, wxGetApp().platformSpeedInfo,
			NUMBER_OF_PLATFORM_SPEEDS);
		if(index < 0){
			index = NUMBER_OF_PLATFORM_SPEEDS;
		}
		choice_2->SetSelection(index);
	}
	oldNum = num;
}
void PlatformDialog::OnDelay(wxCommandEvent& ev)
{
	static int oldNum = 0;
	int num = atoi(wxConvertWX2MB(text_ctrl_2->GetValue()));
	if(num != oldNum){
		//�`���C�X��ύX
		int index = hpl::aleph::getIndexFromInformationBinded(
			num, wxGetApp().platformSpeedInfo,
			NUMBER_OF_PLATFORM_DELAYS);
		if(index < 0){
			index = NUMBER_OF_PLATFORM_DELAYS;
		}
		choice_3->SetSelection(index);
	}
	oldNum = num;
}
void PlatformDialog::OnAutoMin(wxCommandEvent& ev)
{
	//�e�L�X�g�{�b�N�X�ɍŒ�l�������ŋ��߂ē����
//	polygon_data* poly = get_polygon_data;
}
void PlatformDialog::OnAutoMax(wxCommandEvent& ev)
{
}
void PlatformDialog::OnMinHeight(wxCommandEvent& ev)
{
}
void PlatformDialog::OnMaxHeight(wxCommandEvent& ev)
{
}
void PlatformDialog::OnCopyFrom(wxCommandEvent& ev)
{
}
void PlatformDialog::OnTag(wxCommandEvent& ev)
{
}
void PlatformDialog::OnPreset(wxCommandEvent& ev)
{
}

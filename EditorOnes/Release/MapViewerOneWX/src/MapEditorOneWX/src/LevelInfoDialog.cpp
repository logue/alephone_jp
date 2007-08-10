#include "LevelInfoDialog.h"
#include "MapEditorWX.h"
/*
enum{
    ID_LABEL,
    ID_ENV,
    ID_LANDSCAPE,
    ID_SINGLE_PLAYER,
    ID_COOP,
    ID_CTF,
    ID_KOTH,
    ID_BALL,
    ID_DEFENSE,
    ID_RUGBY,
    ID_TAG,
    ID_VACUUME,
    ID_REBELLION,
    ID_LOW_GRAVITY,
    ID_MAGNETIC,
    ID_EXTERMINATION,

};
*/
BEGIN_EVENT_TABLE(LevelInfoDialog, wxDialog)
    EVT_BUTTON(wxID_OK, LevelInfoDialog::OnOk)
    EVT_BUTTON(wxID_CANCEL, LevelInfoDialog::OnCancel)
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
    label_65 = new wxStaticText(this, wxID_ANY, wxT("Label"));
	//TODO only showing
    text_ctrl_44 = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
    label_73 = new wxStaticText(this, wxID_ANY, wxT("Environment"));
    choice_28 = new wxChoice(this, wxID_ANY);
    label_74 = new wxStaticText(this, wxID_ANY, wxT("Landscape"));
    choice_29 = new wxChoice(this, wxID_ANY);
    const wxString radio_box_2_choices[] = {
        wxT("Single Player"),
        wxT("Cooperation (COOP)"),
        wxT("Capture The Flags (CTF)"),
        wxT("King Of The Hill (KOTH)"),
        wxT("Kill Man With Ball (BALL)"),
        wxT("Defense"),
        wxT("Rugby"),
        wxT("Tag")
    };
    radio_box_2 = new wxRadioBox(this, wxID_ANY, wxT("Game Type"), wxDefaultPosition, wxDefaultSize, 8, radio_box_2_choices, 0, wxRA_SPECIFY_ROWS);
/*    checkbox_60 = new wxCheckBox(this, wxID_ANY, wxT("Single Player"));
    checkbox_62 = new wxCheckBox(this, wxID_ANY, wxT("Cooperation (COOP)"));
    checkbox_66 = new wxCheckBox(this, wxID_ANY, wxT("Capture The Flags (CTF)"));
    checkbox_63 = new wxCheckBox(this, wxID_ANY, wxT("King Of The Hill (KOTH)"));
    checkbox_64 = new wxCheckBox(this, wxID_ANY, wxT("Kill Man With Ball (BALL)"));
    checkbox_65 = new wxCheckBox(this, wxID_ANY, wxT("Defense"));
    checkbox_67 = new wxCheckBox(this, wxID_ANY, wxT("Rugby"));
    checkbox_61 = new wxCheckBox(this, wxID_ANY, wxT("Tag"));
	*/
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
/*    sizer_60->Add(checkbox_60, 0, 0, 0);
    sizer_60->Add(checkbox_62, 0, 0, 0);
    sizer_60->Add(checkbox_66, 0, 0, 0);
    sizer_60->Add(checkbox_63, 0, 0, 0);
    sizer_60->Add(checkbox_64, 0, 0, 0);
    sizer_60->Add(checkbox_65, 0, 0, 0);
    sizer_60->Add(checkbox_67, 0, 0, 0);
    sizer_60->Add(checkbox_61, 0, 0, 0);
	*/
//    grid_sizer_37->Add(sizer_60, 1, wxEXPAND, 0);
    grid_sizer_37->Add(radio_box_2, 0, 0, 0);
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

    //ŠÂ‹«’Ç‰Á
	for(int i = 0; i < NUMBER_OF_ENVIRONMENTS; i ++){
		choice_28->Insert(wxConvertMB2WX(wxGetApp().envInfo[i].jname.c_str()), i);
	}
    //”wŒi’Ç‰Á()
	for(int i = 0; i < NUMBER_OF_LANDSPACES; i ++){
		choice_29->Insert(wxConvertMB2WX(wxGetApp().landscapeInfo[i].jname.c_str()), i);
	}
	if(dynamic_world != NULL && static_world != NULL){
		//label
		if(wxGetApp().levelNameList.size() > 0){
			text_ctrl_44->SetValue(wxConvertMB2WX(
				wxGetApp().levelNameList[wxGetApp().editLevelIndex].c_str()));
		}else{
			text_ctrl_44->SetValue(_T("unknown"));
		}
		//‘I‘ð
		game_data* game = &dynamic_world->game_information;
		//TODO	env
		this->choice_28->Disable();//SetSelection(static_world->environment_code);
		//TODO landscape
		this->choice_29->Disable();
		
		//Env flags
		int flags = static_world->environment_flags;
		checkbox_41->SetValue(TEST_FLAG16(flags, _environment_vacuum));
		checkbox_42->SetValue(TEST_FLAG16(flags, _environment_rebellion));
		checkbox_43->SetValue(TEST_FLAG16(flags, _environment_low_gravity));
		checkbox_44->SetValue(TEST_FLAG16(flags, _environment_magnetic));
		//mission
		flags = static_world->mission_flags;
		checkbox_55->SetValue(TEST_FLAG16(flags, _mission_extermination));
		checkbox_56->SetValue(TEST_FLAG16(flags, _mission_exploration));
		checkbox_57->SetValue(TEST_FLAG16(flags, _mission_retrieval));
		checkbox_58->SetValue(TEST_FLAG16(flags, _mission_repair));
		checkbox_59->SetValue(TEST_FLAG16(flags, _mission_rescue));
		//game type
		int type = GET_GAME_TYPE();
	    radio_box_2->SetSelection(type);
	}else{
		hpl::error::caution("No map loaded yet");
	}

    return result;
}
void LevelInfoDialog::OnOk(wxCommandEvent &ev)
{
    SetReturnCode(wxID_OK);
    Destroy();
}
void LevelInfoDialog::OnCancel(wxCommandEvent &ev)
{
    SetReturnCode(wxID_CANCEL);
    Destroy();
}

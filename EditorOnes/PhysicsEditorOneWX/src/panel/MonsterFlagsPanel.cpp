#include "MonsterFlagsPanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_IMMUNITIES,
	ID_WEAKNESSES,
	ID_FRIENDS,
	ID_ENEMIES,
	ID_FLAGS,
};

BEGIN_EVENT_TABLE(MonsterFlagsPanel, wxPanel)
	EVT_CHECKBOX(ID_IMMUNITIES, MonsterFlagsPanel::OnImmunities)
	EVT_CHECKBOX(ID_WEAKNESSES, MonsterFlagsPanel::OnWeaknesses)
	EVT_CHECKBOX(ID_FRIENDS, MonsterFlagsPanel::OnFriends)
	EVT_CHECKBOX(ID_ENEMIES, MonsterFlagsPanel::OnEnemies)
END_EVENT_TABLE()

MonsterFlagsPanel::MonsterFlagsPanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	wxStaticBox* staticDamage = new wxStaticBox(this, wxID_ANY, _T("Immunities/Weaknesses"));
	wxStaticBox* staticEnemy = new wxStaticBox(this, wxID_ANY, _T("Enemies/Friends"));
	wxStaticBox* staticFlags = new wxStaticBox(this, wxID_ANY, _T("Flags"));
	//create
	for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
		this->immunities[i] = new wxCheckBox(this, ID_IMMUNITIES, _T(""));
		this->weaknesses[i] = new wxCheckBox(this, ID_WEAKNESSES, 
			wxConvertMB2WX(wxGetApp().damageInfo[i].jname.c_str()));
	}
	for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
		this->friends[i] = new wxCheckBox(this, ID_FRIENDS, _T(""));
		this->enemies[i] = new wxCheckBox(this, ID_ENEMIES,
			wxConvertMB2WX(wxGetApp().monsterInfo[i].jname.c_str()));
	}
	for(int i = 0; i < NUMBER_OF_MONSTER_FLAG_INFORMATIONS; i ++){
		this->flags[i] = new wxCheckBox(this, ID_FLAGS, 
			wxConvertMB2WX(wxGetApp().monsterFlagsBind[i].jname.c_str()));
	}

	//setting
	//layout
	wxBoxSizer* sizerBase = new wxBoxSizer(wxHORIZONTAL);

	//damages
	wxStaticBoxSizer* staticDamageSizer = new wxStaticBoxSizer(staticDamage, wxVERTICAL);
	wxFlexGridSizer* sizerDamage = new wxFlexGridSizer(NUMBER_OF_DAMAGE_TYPES, 2,0,0);
	for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
		sizerDamage->Add(this->immunities[i], 0, 0,0);
		sizerDamage->Add(this->weaknesses[i], 0, 0,0);
	}
	staticDamageSizer->Add(sizerDamage, 0);

	//enemy
	wxStaticBoxSizer* staticEnemySizer = new wxStaticBoxSizer(staticEnemy, wxVERTICAL);
	wxFlexGridSizer* sizerEnemy = new wxFlexGridSizer(NUMBER_OF_CLASS_INFORMATIONS,2,0,0);
	for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
		sizerEnemy->Add(this->friends[i], 0, 0,0);
		sizerEnemy->Add(this->enemies[i], 0, 0,0);
	}
	staticEnemySizer->Add(sizerEnemy);

	//flags
	wxStaticBoxSizer* staticFlagsSizer = new wxStaticBoxSizer(staticFlags, wxHORIZONTAL);
	wxFlexGridSizer* sizerFlags = new wxFlexGridSizer(NUMBER_OF_MONSTER_FLAG_INFORMATIONS,1,0,0);
	for(int i = 0; i < NUMBER_OF_MONSTER_FLAG_INFORMATIONS; i ++){
		sizerFlags->Add(this->flags[i], 0,0,0);
	}
	staticFlagsSizer->Add(sizerFlags);

	sizerBase->Add(staticDamageSizer, 0, wxEXPAND);
	sizerBase->Add(staticEnemySizer, 1, wxEXPAND);
	sizerBase->Add(staticFlagsSizer, 2, wxEXPAND);
	this->SetSizer(sizerBase);
	sizerBase->Fit(this);
	this->Layout();
}

MonsterFlagsPanel::~MonsterFlagsPanel()
{
}

void MonsterFlagsPanel::OnImmunities(wxCommandEvent& ev)
{
/*	//全フラグチェックボックスの状態をデータにコピー
	for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
		SET_FLAG32(monster_definitions[wxGetApp().frame->get]
	}*/
}
void MonsterFlagsPanel::OnWeaknesses(wxCommandEvent& ev)
{
}
void MonsterFlagsPanel::OnFriends(wxCommandEvent& ev)
{
}
void MonsterFlagsPanel::OnEnemies(wxCommandEvent& ev)
{
}
void MonsterFlagsPanel::OnFlags(wxCommandEvent& ev)
{
}

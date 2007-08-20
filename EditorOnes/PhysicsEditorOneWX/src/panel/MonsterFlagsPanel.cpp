#include "MonsterFlagsPanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_IMMUNITIES,
	ID_WEAKNESSES,
	ID_FRIENDS,
	ID_ENEMIES,
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
	//setting
	//layout
	wxGridSizer* sizerBase = new wxGridSizer(1, 3);
	wxFlexGridSizer* sizerDamage = new wxFlexGridSizer(28, 2);
	for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
		sizerDamage->Add(this->immunities[i]);
	}
	wxStaticBoxSizer* staticDamage = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Immunities/Weaknesses"));
	staticDamage->Add(sizerDamage);

	wxFlexGridSizer* sizerEnemy = new wxFlexGridSizer(16,2);
	wxStaticBoxSizer* staticEnemy = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Enemies/Friends"));
	staticEnemy->Add(sizerEnemy);

	wxFlexGridSizer* sizerFlags = new wxFlexGridSizer(28);
	wxStaticBoxSizer* staticFlags = new wxStaticBoxSizer(wxHORIZONTAL, this, _T("Flags"));
	sizerFlags->Add(sizerFlags);

	sizerBase->Add(staticDamage);
	sizerBase->Add(staticEnemy);
	sizerBase->Add(staticFlags);
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

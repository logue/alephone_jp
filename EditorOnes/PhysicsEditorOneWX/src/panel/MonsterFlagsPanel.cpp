#include "MonsterFlagsPanel.h"

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
		this->immunities[i] = new wxCheckBox(this, ID_IMMUNITIES);
		this->weaknesses[i] = new wxCheckBox(this, ID_WEAKNESSES);
	}
	for(int i = 0l i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
		this->friends[i] = new wxCheckBox(this, ID_FRIENDS);
		this->enemies[i] = new wxCheckBox(this, ID_ENEMIES);
	}
	//setting
	//layout
	wxGridSizer* sizerBase = new wxGridSizer(1, 3);
	this->SetSizer(sizerBase);
	sizerBase->Fit(this);
	this->Layout();
}

MonsterFlagsPanel::~MonsterFlagsPanel()
{
}

void MonsterFlagsPanel::OnImmunities(wxCommandEvent& ev)
{
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

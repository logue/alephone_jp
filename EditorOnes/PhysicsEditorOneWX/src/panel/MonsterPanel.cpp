#include "MonsterPanel.h"

enum{
	ID_TYPE,
	ID_NOTE,
	ID_APPEARANCE,
	ID_FLAGS,
	ID_ATTACK,
};

BEGIN_EVENT_TABLE(MonsterPanel, wxPanel)
	EVT_LISTBOX(ID_TYPE, MonsterPanel::OnSelType)
END_EVENT_TABLE()

MonsterPanel::MonsterPanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	//listbox
	monsterTypeListBox = new wxListBox(this, ID_TYPE);
	//notebook
	notebook = new wxNotebook(this, ID_NOTE);
	this->appearancePanel = new MonsterAppearancePanel(notebook, wxID_ANY);
	this->flagsPanel = new MonsterFlagsPanel(notebook, wxID_ANY);
	this->attackPanel = new MonsterAttackPanel(notebook, wxID_ANY);
	notebook->AddPage(appearancePanel, _T("Appearance"));
	notebook->AddPage(flagsPanel, _T("Flags"));
	notebook->AddPage(attackPanel, _T("Attack"));

	//設定
	monsterTypeListBox->SetMinSize(wxSize(-1, 300));

	//配置
	wxFlexGridSizer* sizerBase = new wxFlexGridSizer(2);
	sizerBase->Add(monsterTypeListBox, 0, wxEXPAND);
	sizerBase->Add(notebook, 0, wxEXPAND, 0);
	
	SetSizer(sizerBase);
	sizerBase->Fit(this);
	Layout();
}

void MonsterPanel::OnSelType(wxCommandEvent& ev)
{
	int sel = ev.GetSelection();
	if(sel >= 0 && sel < NUMBER_OF_MONSTER_TYPES){
		//対象のデータを取得し、GUIアイテムに反映する
		this->setupMonster(sel);
	}
}
void MonsterPanel::setupMonster(int type)
{
	wxASSERT(type >= 0 && type < NUMBER_OF_MONSTER_TYPES);

	//appearanceの更新

	//flagsの更新
	//attackの更新

}

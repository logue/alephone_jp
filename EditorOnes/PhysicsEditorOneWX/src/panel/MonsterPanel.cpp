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
	wxNotebookPage* appearancePage = new wxNotebookPage(notebook, ID_APPEARANCE);
	notebook->AddPage(appearancePage, _T("Appearance"));
	wxNotebookPage* flagsPage = new wxNotebookPage(notebook, ID_FLAGS);
	notebook->AddPage(flagsPage, _T("Flags"));
	wxNotebookPage* attackPage = new wxNotebookPage(notebook, ID_ATTACK);
	notebook->AddPage(attackPage, _T("Attack"));

	//設定

	//配置
	wxFlexGridSizer* sizerBase = new wxFlexGridSizer(1,2);
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

#ifndef _MONSTER_PANEL_
#define _MONSTER_PANEL_

#include "../Common.h"

#include "MonsterAppearancePanel.h"
#include "MonsterFlagsPanel.h"
#include "MonsterAttackPanel.h"

class MonsterPanel: public wxPanel{
private:
	//monster type list
	wxListBox* monsterTypeListBox;
	
	//notebook (appearance / flags / attack)
	wxNotebook* notebook;

	//appearance panel
	MonsterAppearancePanel* appearancePanel;
	MonsterFlagsPanel* flagsPanel;
	MonsterAttackPanel* attackPanel;

	MonsterPanel(){}
public:
	MonsterPanel(wxWindow* parent, wxWindowID id);
    DECLARE_EVENT_TABLE()
	void OnSelType(wxCommandEvent& ev);
private:
	void setupMonster(int type);
public:
};

#endif

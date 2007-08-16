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
public:
	void Create(wxWindow* parent, wxWindowID id);
};

#endif

#ifndef _MONSTER_APPEARANCE_PANEL_
#define _MONSTER_APPEARANCE_PANEL_

#include "../Common.h"

/**
	MonsterのAppearance（見た目、音、シーケンス、体力等）
	に関するデータを操作するパネル
*/
class MonsterAppearancePanel: public wxPanel{
private:
	MonsterAppearancePanel(){}
public:
	MonsterAppearancePanel(wxWindow* parent, wxWindowID id);
	virtual ~MonsterAppearancePanel();
};


#endif

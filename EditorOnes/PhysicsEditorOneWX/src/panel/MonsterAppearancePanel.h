#ifndef _MONSTER_APPEARANCE_PANEL_
#define _MONSTER_APPEARANCE_PANEL_

#include "../Common.h"

/**
	MonsterのAppearance（見た目、音、シーケンス、体力等）
	に関するデータを操作するパネル
*/
class MonsterAppearancePanel: public wxPanel{
public:
	void Create(wxWindow* parent, wxWindowID id);
};


#endif

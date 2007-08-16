#ifndef _MONSTER_FLAGS_PANEL_
#define _MONSTER_FLAGS_PANEL_

#include "../Common.h"

/**
	敵味方判定や耐性、弱点。そして各種設定を行うパネル
*/
class MonsterFlagsPanel: wxPanel{
public:
	void Create(wxWindow* parent, wxWindowID id);
};

#endif

#ifndef _MONSTER_ATTACK_PANEL_
#define _MONSTER_ATTACK_PANEL_

#include "../Common.h"

/**
	�U���s���Ɋւ���ݒ�
*/
class MonsterAttackPanel: public wxPanel{
private:
	MonsterAttackPanel(){}
public:
	MonsterAttackPanel(wxWindow* parent, wxWindowID id);
	virtual ~MonsterAttackPanel();
};

#endif

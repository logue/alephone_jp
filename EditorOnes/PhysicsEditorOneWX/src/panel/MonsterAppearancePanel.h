#ifndef _MONSTER_APPEARANCE_PANEL_
#define _MONSTER_APPEARANCE_PANEL_

#include "../Common.h"

/**
	Monster��Appearance�i�����ځA���A�V�[�P���X�A�̗͓��j
	�Ɋւ���f�[�^�𑀍삷��p�l��
*/
class MonsterAppearancePanel: public wxPanel{
private:
	MonsterAppearancePanel(){}
public:
	MonsterAppearancePanel(wxWindow* parent, wxWindowID id);
	virtual ~MonsterAppearancePanel();
};


#endif

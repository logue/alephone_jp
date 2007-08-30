#ifndef _MONSTER_ATTACK_PANEL_
#define _MONSTER_ATTACK_PANEL_

#include "../Common.h"

/**
	�U���s���Ɋւ���ݒ�
*/
class MonsterAttackPanel: public wxPanel{
private:
	wxTextCtrl* frequencyText;

	//melee
	wxChoice* meleeTypeChoice;
	wxTextCtrl* meleeRepetitionsText;
	wxTextCtrl* meleeErrorText;
	wxTextCtrl* meleeRangeText;
	wxTextCtrl* meleeSequenceText;
	wxTextCtrl* meleeDXText;
	wxTextCtrl* meleeDYText;
	wxTextCtrl* meleeDZText;
	wxButton* meleeCopyFromButton;

	//ranged
	wxChoice* rangedTypeChoice;
	wxTextCtrl* rangedRepetitionsText;
	wxTextCtrl* rangedErrorText;
	wxTextCtrl* rangedRangeText;
	wxTextCtrl* rangedSequenceText;
	wxTextCtrl* rangedDXText;
	wxTextCtrl* rangedDYText;
	wxTextCtrl* rangedDZText;
	wxButton* rangedCopyFromButton;
private:
	MonsterAttackPanel(){}
public:
	MonsterAttackPanel(wxWindow* parent, wxWindowID id);
	virtual ~MonsterAttackPanel();
};

#endif

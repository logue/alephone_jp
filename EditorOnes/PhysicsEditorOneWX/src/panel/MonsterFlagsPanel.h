#ifndef _MONSTER_FLAGS_PANEL_
#define _MONSTER_FLAGS_PANEL_

#include "../Common.h"

/**
	敵味方判定や耐性、弱点。そして各種設定を行うパネル
*/
class MonsterFlagsPanel: public wxPanel{
private:
	//チェックボックス
	//	耐性・弱点
	wxCheckBox* immunities[NUMBER_OF_DAMAGE_TYPES];
	wxCheckBox* weaknesses[NUMBER_OF_DAMAGE_TYPES];
	//	味方・敵
	wxCheckBox* friends[NUMBER_OF_CLASS_INFORMATIONS];
	wxCheckBox* enemies[NUMBER_OF_CLASS_INFORMATIONS];
	//	flags
	wxCheckBox* flags[NUMBER_OF_MONSTER_FLAG_INFORMATIONS];
private:
	MonsterFlagsPanel(){}
public:
	MonsterFlagsPanel(wxWindow* parent, wxWindowID id);
	virtual ~MonsterFlagsPanel();

protected:
    DECLARE_EVENT_TABLE()
	void OnImmunities(wxCommandEvent& ev);
	void OnWeaknesses(wxCommandEvent& ev);
	void OnFriends(wxCommandEvent& ev);
	void OnEnemies(wxCommandEvent& ev);
	void OnFlags(wxCommandEvent& ev);
	int common();
public:

	void setup();
};

#endif

#ifndef _MONSTER_FLAGS_PANEL_
#define _MONSTER_FLAGS_PANEL_

#include "../Common.h"

/**
	�G���������ϐ��A��_�B�����Ċe��ݒ���s���p�l��
*/
class MonsterFlagsPanel: public wxPanel{
private:
	//�`�F�b�N�{�b�N�X
	//	�ϐ��E��_
	wxCheckBox* immunities[NUMBER_OF_DAMAGE_TYPES];
	wxCheckBox* weaknesses[NUMBER_OF_DAMAGE_TYPES];
	//	�����E�G
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

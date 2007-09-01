#ifndef _MONSTER_ATTACK_PANEL_
#define _MONSTER_ATTACK_PANEL_

#include "../Common.h"

/**
	çUåÇçsìÆÇ…ä÷Ç∑ÇÈê›íË
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
    DECLARE_EVENT_TABLE()
	void OnFrequency(wxCommandEvent& ev);

	void OnMeleeType(wxCommandEvent& ev);
	void OnMeleeRep(wxCommandEvent& ev);
	void OnMeleeError(wxCommandEvent& ev);
	void OnMeleeRange(wxCommandEvent& ev);
	void OnMeleeSequence(wxCommandEvent& ev);
	void OnMeleeDX(wxCommandEvent& ev);
	void OnMeleeDY(wxCommandEvent& ev);
	void OnMeleeDZ(wxCommandEvent& ev);
	void OnMeleeCopyFrom(wxCommandEvent& ev);

	void OnRangedType(wxCommandEvent& ev);
	void OnRangedRep(wxCommandEvent& ev);
	void OnRangedError(wxCommandEvent& ev);
	void OnRangedRange(wxCommandEvent& ev);
	void OnRangedSequence(wxCommandEvent& ev);
	void OnRangedDX(wxCommandEvent& ev);
	void OnRangedDY(wxCommandEvent& ev);
	void OnRangedDZ(wxCommandEvent& ev);
	void OnRangedCopyFrom(wxCommandEvent& ev);
public:

	void setup();
};

#endif

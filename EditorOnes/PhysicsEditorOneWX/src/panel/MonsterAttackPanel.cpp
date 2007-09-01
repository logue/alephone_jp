#include "MonsterAttackPanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_FREQUENCY,

	ID_MELEE_TYPE,
	ID_MELEE_REP,
	ID_MELEE_ERROR,
	ID_MELEE_RANGE,
	ID_MELEE_SEQUENCE,
	ID_MELEE_DX,
	ID_MELEE_DY,
	ID_MELEE_DZ,
	ID_MELEE_COPY_FROM,

	ID_RANGED_TYPE,
	ID_RANGED_REP,
	ID_RANGED_ERROR,
	ID_RANGED_RANGE,
	ID_RANGED_SEQUENCE,
	ID_RANGED_DX,
	ID_RANGED_DY,
	ID_RANGED_DZ,
	ID_RANGED_COPY_FROM,
};

BEGIN_EVENT_TABLE(MonsterAttackPanel, wxPanel)
	EVT_TEXT(ID_FREQUENCY, MonsterAttackPanel::OnFrequency)

	EVT_CHOICE(ID_MELEE_TYPE, MonsterAttackPanel::OnMeleeType)
	EVT_TEXT(ID_MELEE_REP, MonsterAttackPanel::OnMeleeRep)
	EVT_TEXT(ID_MELEE_ERROR, MonsterAttackPanel::OnMeleeError)
	EVT_TEXT(ID_MELEE_RANGE, MonsterAttackPanel::OnMeleeRange)
	EVT_TEXT(ID_MELEE_SEQUENCE, MonsterAttackPanel::OnMeleeSequence)
	EVT_TEXT(ID_MELEE_DX, MonsterAttackPanel::OnMeleeDX)
	EVT_TEXT(ID_MELEE_DY, MonsterAttackPanel::OnMeleeDZ)
	EVT_TEXT(ID_MELEE_DZ, MonsterAttackPanel::OnMeleeDZ)
	EVT_BUTTON(ID_MELEE_COPY_FROM, MonsterAttackPanel::OnMeleeCopyFrom)

	EVT_CHOICE(ID_RANGED_TYPE, MonsterAttackPanel::OnRangedType)
	EVT_TEXT(ID_RANGED_REP, MonsterAttackPanel::OnRangedRep)
	EVT_TEXT(ID_RANGED_ERROR, MonsterAttackPanel::OnRangedError)
	EVT_TEXT(ID_RANGED_RANGE, MonsterAttackPanel::OnRangedRange)
	EVT_TEXT(ID_RANGED_SEQUENCE, MonsterAttackPanel::OnRangedSequence)
	EVT_TEXT(ID_RANGED_DX, MonsterAttackPanel::OnRangedDX)
	EVT_TEXT(ID_RANGED_DY, MonsterAttackPanel::OnRangedDZ)
	EVT_TEXT(ID_RANGED_DZ, MonsterAttackPanel::OnRangedDZ)
	EVT_BUTTON(ID_RANGED_COPY_FROM, MonsterAttackPanel::OnRangedCopyFrom)
END_EVENT_TABLE()
MonsterAttackPanel::MonsterAttackPanel(wxWindow* parent, wxWindowID id)
:wxPanel(parent, id)
{
	//create
	this->frequencyText = new wxTextCtrl(this, ID_FREQUENCY);
	this->meleeTypeChoice = new wxChoice(this, ID_MELEE_TYPE);
	this->meleeRepetitionsText = new wxTextCtrl(this, ID_MELEE_REP);
	this->meleeErrorText = new wxTextCtrl(this, ID_MELEE_ERROR);
	this->meleeRangeText = new wxTextCtrl(this, ID_MELEE_RANGE);
	this->meleeSequenceText = new wxTextCtrl(this, ID_MELEE_SEQUENCE);
	this->meleeDXText = new wxTextCtrl(this, ID_MELEE_DX);
	this->meleeDYText = new wxTextCtrl(this, ID_MELEE_DY);
	this->meleeDZText = new wxTextCtrl(this, ID_MELEE_DZ);
	this->meleeCopyFromButton = new wxButton(this, ID_MELEE_COPY_FROM,
		_T("Copy from ..."));

	this->rangedTypeChoice = new wxChoice(this, ID_MELEE_TYPE);
	this->rangedRepetitionsText = new wxTextCtrl(this, ID_MELEE_REP);
	this->rangedErrorText = new wxTextCtrl(this, ID_MELEE_ERROR);
	this->rangedRangeText = new wxTextCtrl(this, ID_MELEE_RANGE);
	this->rangedSequenceText = new wxTextCtrl(this, ID_MELEE_SEQUENCE);
	this->rangedDXText = new wxTextCtrl(this, ID_MELEE_DX);
	this->rangedDYText = new wxTextCtrl(this, ID_MELEE_DY);
	this->rangedDZText = new wxTextCtrl(this, ID_MELEE_DZ);
	this->rangedCopyFromButton = new wxButton(this, ID_MELEE_COPY_FROM,
		_T("Copy from ..."));

	//set
	//	type
	for(int i = 0; i < NUMBER_OF_PROJECTILE_TYPES; i ++){
		meleeTypeChoice->Insert(wxConvertMB2WX(
			wxGetApp().projectileInfo[i].jname.c_str()), i);
		rangedTypeChoice->Insert(wxConvertMB2WX(
			wxGetApp().projectileInfo[i].jname.c_str()), i);
	}
	meleeTypeChoice->Insert(_T("NONE"), NUMBER_OF_PROJECTILE_TYPES);
	rangedTypeChoice->Insert(_T("NONE"), NUMBER_OF_PROJECTILE_TYPES);

	//layout
	wxFlexGridSizer* allSizer = new wxFlexGridSizer(2,2, 0,0);

	//frequency
	wxFlexGridSizer* fleqFlexSizer = new wxFlexGridSizer(1,2,0,0);
		fleqFlexSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Frequency")));
		fleqFlexSizer->Add(this->frequencyText, 0, wxEXPAND, 0, 0);
	allSizer->Add(fleqFlexSizer);
	allSizer->Add(new wxPanel(this, wxID_ANY));

	//melee
	wxStaticBox* meleeStaticBox = new wxStaticBox(this, wxID_ANY,
		_T("Ranged"));
	wxStaticBoxSizer* meleeStaticSizer = new wxStaticBoxSizer(meleeStaticBox, wxVERTICAL);
		wxFlexGridSizer* meleeFlexSizer = new wxFlexGridSizer(2,1,0,0);
			wxFlexGridSizer* meleeAboveSizer = new wxFlexGridSizer(8,2,0,0);
			meleeAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Type")));
			meleeAboveSizer->Add(meleeTypeChoice);
			meleeAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Repetitions")));
			meleeAboveSizer->Add(meleeRepetitionsText);
			meleeAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Error")));
			meleeAboveSizer->Add(meleeErrorText);
			meleeAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Range")));
			meleeAboveSizer->Add(meleeRangeText);
			meleeAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Sequence")));
			meleeAboveSizer->Add(meleeSequenceText);
			meleeAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Delta X")));
			meleeAboveSizer->Add(meleeDXText);
			meleeAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Delta Y")));
			meleeAboveSizer->Add(meleeDYText);
			meleeAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Delta Z")));
			meleeAboveSizer->Add(meleeDZText);
		meleeFlexSizer->Add(meleeAboveSizer);
		meleeFlexSizer->Add(meleeCopyFromButton);
		meleeStaticSizer->Add(meleeFlexSizer);
	allSizer->Add(meleeStaticSizer);

	//ranged
	wxStaticBox* rangedStaticBox = new wxStaticBox(this, wxID_ANY,
		_T("Melee"));
	wxStaticBoxSizer* rangedStaticSizer = new wxStaticBoxSizer(rangedStaticBox, wxVERTICAL);
		wxFlexGridSizer* rangedFlexSizer = new wxFlexGridSizer(2,1,0,0);
			wxFlexGridSizer* rangedAboveSizer = new wxFlexGridSizer(8,2,0,0);
			rangedAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Type")));
			rangedAboveSizer->Add(rangedTypeChoice);
			rangedAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Repetitions")));
			rangedAboveSizer->Add(rangedRepetitionsText);
			rangedAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Error")));
			rangedAboveSizer->Add(rangedErrorText);
			rangedAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Range")));
			rangedAboveSizer->Add(rangedRangeText);
			rangedAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Sequence")));
			rangedAboveSizer->Add(rangedSequenceText);
			rangedAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Delta X")));
			rangedAboveSizer->Add(rangedDXText);
			rangedAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Delta Y")));
			rangedAboveSizer->Add(rangedDYText);
			rangedAboveSizer->Add(new wxStaticText(this, wxID_ANY,
				_T("Delta Z")));
			rangedAboveSizer->Add(rangedDZText);
		rangedFlexSizer->Add(rangedAboveSizer);
		rangedFlexSizer->Add(rangedCopyFromButton);
		rangedStaticSizer->Add(rangedFlexSizer);
	allSizer->Add(rangedStaticSizer);

	this->SetSizer(allSizer);
	allSizer->Fit(this);
	Layout();

}
MonsterAttackPanel::~MonsterAttackPanel()
{
}
void MonsterAttackPanel::OnFrequency(wxCommandEvent& ev)
{
}

void MonsterAttackPanel::OnMeleeType(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnMeleeRep(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnMeleeError(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnMeleeRange(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnMeleeSequence(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnMeleeDX(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnMeleeDY(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnMeleeDZ(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnMeleeCopyFrom(wxCommandEvent& ev)
{
}

void MonsterAttackPanel::OnRangedType(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnRangedRep(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnRangedError(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnRangedRange(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnRangedSequence(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnRangedDX(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnRangedDY(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnRangedDZ(wxCommandEvent& ev)
{
}
void MonsterAttackPanel::OnRangedCopyFrom(wxCommandEvent& ev)
{
}

void MonsterAttackPanel::setup()
{
	int type = wxGetApp().getEditingMonsterIndex();

	//frequency
	frequencyText->SetValue(wx::string::getString("%d",
		monster_definitions[type].attack_frequency));

	//melee
	setChoice(meleeTypeChoice, monster_definitions[type].melee_attack.type,
		NUMBER_OF_PROJECTILE_TYPES);
	meleeRepetitionsText->SetValue(wx::string::getString("%d",
		monster_definitions[type].melee_attack.repetitions));
	meleeErrorText->SetValue(wx::string::getString("%d",
		monster_definitions[type].melee_attack.error));
	meleeRangeText->SetValue(wx::string::getString("%d",
		monster_definitions[type].melee_attack.range));
	meleeSequenceText->SetValue(wx::string::getString("%d",
		monster_definitions[type].melee_attack.attack_shape));
	meleeDXText->SetValue(wx::string::getString("%d",
		monster_definitions[type].melee_attack.dx));
	meleeDYText->SetValue(wx::string::getString("%d",
		monster_definitions[type].melee_attack.dy));
	meleeDZText->SetValue(wx::string::getString("%d",
		monster_definitions[type].melee_attack.dz));

	//ranged
	setChoice(rangedTypeChoice, monster_definitions[type].ranged_attack.type,
		NUMBER_OF_PROJECTILE_TYPES);
	rangedRepetitionsText->SetValue(wx::string::getString("%d",
		monster_definitions[type].ranged_attack.repetitions));
	rangedErrorText->SetValue(wx::string::getString("%d",
		monster_definitions[type].ranged_attack.error));
	rangedRangeText->SetValue(wx::string::getString("%d",
		monster_definitions[type].ranged_attack.range));
	rangedSequenceText->SetValue(wx::string::getString("%d",
		monster_definitions[type].ranged_attack.attack_shape));
	rangedDXText->SetValue(wx::string::getString("%d",
		monster_definitions[type].ranged_attack.dx));
	rangedDYText->SetValue(wx::string::getString("%d",
		monster_definitions[type].ranged_attack.dy));
	rangedDZText->SetValue(wx::string::getString("%d",
		monster_definitions[type].ranged_attack.dz));

}

#include "EffectPanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_TYPE,
	ID_COLLECTION,
	ID_PALETTE,
	ID_SEQUENCE,
	ID_SOUND_PITCH,
	ID_DELAY,
	ID_DELAY_SOUND,
	ID_FLAGS,
};

BEGIN_EVENT_TABLE(EffectPanel, wxPanel)
	EVT_LISTBOX(ID_TYPE, EffectPanel::OnType)
	EVT_CHOICE(ID_COLLECTION, EffectPanel::OnCollection)
	EVT_TEXT(ID_PALETTE, EffectPanel::OnPalette)
	EVT_TEXT(ID_SEQUENCE, EffectPanel::OnSequence)
	EVT_TEXT(ID_SOUND_PITCH, EffectPanel::OnSoundPitch)
	EVT_TEXT(ID_DELAY, EffectPanel::OnDelay)
	EVT_CHOICE(ID_DELAY_SOUND, EffectPanel::OnDelaySound)
	EVT_CHECKBOX(ID_FLAGS, EffectPanel::OnFlags)
END_EVENT_TABLE()

EffectPanel::EffectPanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	//create
	this->typeListBox = new wxListBox(this, ID_TYPE);
	this->collectionChoice = new wxChoice(this, ID_COLLECTION);
	this->paletteText = new wxTextCtrl(this, ID_PALETTE);
	this->sequenceText = new wxTextCtrl(this, ID_SEQUENCE);
	this->soundPitchText = new wxTextCtrl(this, ID_SOUND_PITCH);
	this->delayText = new wxTextCtrl(this, ID_DELAY);
	this->delaySoundChoice = new wxChoice(this, ID_DELAY_SOUND);
	this->flags[0] = new wxCheckBox(this, ID_FLAGS,
		_T("End When Animation Loops"));
	this->flags[1] = new wxCheckBox(this, ID_FLAGS,
		_T("End When Transfer Animation Loops"));
	this->flags[2] = new wxCheckBox(this, ID_FLAGS,
		_T("End When Sound Only"));
	this->flags[3] = new wxCheckBox(this, ID_FLAGS,
		_T("Make Twin Visible"));
	this->flags[4] = new wxCheckBox(this, ID_FLAGS,
		_T("Media Effect"));
	//set
	this->typeListBox->SetMinSize(wxSize(-1,LIST_BOX_HEIGHT));

	for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
		this->collectionChoice->Insert(wxConvertMB2WX(
			wxGetApp().collectionInfo[i].jname.c_str()),i);
	}
	for(int i = 0; i < NUMBER_OF_SOUND_DEFINITIONS; i ++){
		this->delaySoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()),i);
	}
	this->delaySoundChoice->Insert(_T("NONE"),NUMBER_OF_SOUND_DEFINITIONS);

	for(int i = 0; i < NUMBER_OF_EFFECT_TYPES; i ++){
		this->typeListBox->Insert(wxConvertMB2WX(
			wxGetApp().effectInfo[i].jname.c_str()), i);
	}
	//layout
	//
	wxFlexGridSizer* rightSizer = new wxFlexGridSizer(2,1,0,0);
	wxFlexGridSizer* upSizer = new wxFlexGridSizer(6,2,0,0);
		upSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Collection")));
		upSizer->Add(this->collectionChoice);
		upSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Palette")));
		upSizer->Add(this->paletteText);
		upSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Sequence")));
		upSizer->Add(this->sequenceText);
		upSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Sound Pitch")));
		upSizer->Add(this->soundPitchText);
		upSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Delay")));
		upSizer->Add(this->delayText);
		upSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Delay Sound")));
		upSizer->Add(this->delaySoundChoice);
	wxStaticBox* flagsStaticBox = new wxStaticBox(this, wxID_ANY,
		_T("Flags"));
		wxStaticBoxSizer* flagsStaticBoxSizer = new wxStaticBoxSizer(
			flagsStaticBox, wxVERTICAL);
		wxFlexGridSizer* flagsFlexGridSizer = new wxFlexGridSizer(5,1,0,0);
		for(int i = 0; i < NUMBER_OF_EFFECT_FLAG_INFORMATIONS; i ++){
			flagsFlexGridSizer->Add(this->flags[i],0,wxEXPAND,0,0);
		}
		flagsStaticBoxSizer->Add(flagsFlexGridSizer);
	rightSizer->Add(upSizer);
	rightSizer->Add(flagsStaticBoxSizer);

	wxFlexGridSizer* allSizer = new wxFlexGridSizer(1,2,0,0);
	allSizer->Add(this->typeListBox, 0, wxEXPAND,0,0);
	allSizer->Add(rightSizer);
	this->SetSizer(allSizer);
	allSizer->Fit(this);
	Layout();
}

EffectPanel::~EffectPanel()
{
}

void EffectPanel::OnType(wxCommandEvent& ev)
{
	int index = ev.GetSelection();
	if(index >= 0 && index < NUMBER_OF_EFFECT_TYPES){
		wxGetApp().setEditingEffectIndex(index);
		setup();
	}
	common();
}
void EffectPanel::OnCollection(wxCommandEvent& ev)
{
	int type = common();
	int col = ev.GetSelection();
	int clut = getNumberFromTextCtrl(this->paletteText);
	effect_definitions[type].collection = BUILD_COLLECTION(col, clut);
}
void EffectPanel::OnPalette(wxCommandEvent& ev)
{
	int type = common();
	int col = this->collectionChoice->GetSelection();
	int clut = getNumberFromTextCtrl(&ev);
	effect_definitions[type].collection = BUILD_COLLECTION(col, clut);
}
void EffectPanel::OnSequence(wxCommandEvent& ev)
{
	int type = common();
	effect_definitions[type].shape = getNumberFromTextCtrl(&ev);
}
void EffectPanel::OnSoundPitch(wxCommandEvent& ev)
{
	int type = common();
	effect_definitions[type].sound_pitch = getNumberFromTextCtrl(&ev);
}
void EffectPanel::OnDelay(wxCommandEvent& ev)
{
	int type = common();
	effect_definitions[type].delay = getNumberFromTextCtrl(&ev);
}
void EffectPanel::OnDelaySound(wxCommandEvent& ev)
{
	int type = common();
	effect_definitions[type].delay_sound = 
		getChoice(&ev, NUMBER_OF_SOUND_DEFINITIONS);
}
void EffectPanel::OnFlags(wxCommandEvent& ev)
{
	int type = common();
	int flag = 0;
	for(int i = 0; i < NUMBER_OF_EFFECT_FLAG_INFORMATIONS; i ++){
		flag |= this->flags[i]->GetValue() ? wxGetApp().effectFlagsBind[i].bind : 0;
	}
	effect_definitions[type].flags = flag;
}
void EffectPanel::setup()
{
	int type = wxGetApp().getEditingEffectIndex();
	int collection = effect_definitions[type].collection;
	int col = GET_COLLECTION(collection);
	int clut = GET_COLLECTION_CLUT(collection);
	this->collectionChoice->SetSelection(col);
	this->paletteText->SetValue(
		wx::string::getString("%d", clut));
	this->sequenceText->SetValue(
		wx::string::getString("%d", 
		effect_definitions[type].shape));
	this->soundPitchText->SetValue(
		wx::string::getString("%d", 
		effect_definitions[type].sound_pitch));
	this->delayText->SetValue(
		wx::string::getString("%d", 
		effect_definitions[type].delay));
	setChoice(this->delaySoundChoice, effect_definitions[type].delay_sound,
		NUMBER_OF_SOUND_DEFINITIONS);
	for(int i = 0; i < NUMBER_OF_EFFECT_FLAG_INFORMATIONS; i ++){
		this->flags[i]->SetValue(
			(effect_definitions[type].flags & wxGetApp().effectFlagsBind[i].bind) != 0);
	}
}
int EffectPanel::common()
{
	int type = wxGetApp().getEditingMonsterIndex();
	wxGetApp().setChanged(true);
	return type;
}


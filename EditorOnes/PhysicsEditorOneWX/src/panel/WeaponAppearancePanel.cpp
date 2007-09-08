#include "WeaponAppearancePanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_COLLECTION,
	ID_PALETTE,
	ID_IDLE_SEQ,
	ID_FIRING_SEQ,
	ID_RELOAD_SEQ,
	ID_CHARGING_SEQ,
	ID_CHARGED_SEQ,
	ID_ITEM,
	ID_CLASS,
	ID_LIGHT_INTENSITY,
	ID_INTENSITY_DECAY,
	ID_IDLE_WIDTH,
	ID_IDLE_HEIGHT,
	ID_FIRING_HEIGHT,
	ID_RELOADING_HEIGHT,
	ID_HORIZONTAL_AMPLITUDE,
	ID_USER_AMPLITUDE,
	ID_READY_TICKS,
	ID_AWAIT_RELOAD_TICKS,
	ID_LOADING_TICKS,
	ID_LOADED_TICKS,

	ID_FLAGS,
};

BEGIN_EVENT_TABLE(WeaponAppearancePanel, wxPanel)
EVT_CHOICE(ID_COLLECTION, WeaponAppearancePanel::OnCollection)
EVT_TEXT(ID_PALETTE, WeaponAppearancePanel::OnPalette)
EVT_TEXT(ID_IDLE_SEQ, WeaponAppearancePanel::OnIdleSeq)
EVT_TEXT(ID_FIRING_SEQ, WeaponAppearancePanel::OnFiringSeq)
EVT_TEXT(ID_RELOAD_SEQ, WeaponAppearancePanel::OnReloadSeq)
EVT_TEXT(ID_CHARGING_SEQ, WeaponAppearancePanel::OnChargingSeq)
EVT_TEXT(ID_CHARGED_SEQ, WeaponAppearancePanel::OnChargedSeq)
EVT_CHOICE(ID_ITEM, WeaponAppearancePanel::OnItem)
EVT_CHOICE(ID_CLASS, WeaponAppearancePanel::OnClass)
EVT_TEXT(ID_LIGHT_INTENSITY, WeaponAppearancePanel::OnLightIntensity)
EVT_TEXT(ID_INTENSITY_DECAY, WeaponAppearancePanel::OnIntensityDecay)
EVT_TEXT(ID_IDLE_WIDTH, WeaponAppearancePanel::OnIdleWidth)
EVT_TEXT(ID_IDLE_HEIGHT, WeaponAppearancePanel::OnIdleHeight)
EVT_TEXT(ID_FIRING_HEIGHT, WeaponAppearancePanel::OnFiringHeight)
EVT_TEXT(ID_RELOADING_HEIGHT, WeaponAppearancePanel::OnReloadingHeight)
EVT_TEXT(ID_HORIZONTAL_AMPLITUDE, WeaponAppearancePanel::OnHorizontalAmplitude)
EVT_TEXT(ID_USER_AMPLITUDE, WeaponAppearancePanel::OnUserAmplitude)
EVT_TEXT(ID_READY_TICKS, WeaponAppearancePanel::OnReadyTicks)
EVT_TEXT(ID_AWAIT_RELOAD_TICKS, WeaponAppearancePanel::OnAwaitReloadTicks)
EVT_TEXT(ID_LOADING_TICKS, WeaponAppearancePanel::OnLoadingTicks)
EVT_TEXT(ID_LOADED_TICKS, WeaponAppearancePanel::OnLoadedTicks)

EVT_CHECKBOX(ID_FLAGS, WeaponAppearancePanel::OnFlags)
END_EVENT_TABLE()

WeaponAppearancePanel::WeaponAppearancePanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	//create
	this->collectionChoice = new wxChoice(this, ID_COLLECTION);
	this->paletteText = new wxTextCtrl(this, ID_PALETTE);
	this->idleSeqText = new wxTextCtrl(this, ID_IDLE_SEQ);
	this->firingSeqText = new wxTextCtrl(this, ID_FIRING_SEQ);
	this->reloadSeqText = new wxTextCtrl(this, ID_RELOAD_SEQ);
	this->chargingSeqText = new wxTextCtrl(this, ID_CHARGING_SEQ);
	this->chargedSeqText = new wxTextCtrl(this, ID_CHARGED_SEQ);
	this->itemChoice = new wxChoice(this, ID_ITEM);
	this->classChoice = new wxChoice(this, ID_CLASS);
	this->lightIntensityText = new wxTextCtrl(this, ID_LIGHT_INTENSITY);
	this->intensityDecayText = new wxTextCtrl(this, ID_INTENSITY_DECAY);
	this->idleWidthText = new wxTextCtrl(this, ID_IDLE_WIDTH);
	this->idleHeightText = new wxTextCtrl(this, ID_IDLE_HEIGHT);
	this->firingHeightText = new wxTextCtrl(this, ID_FIRING_HEIGHT);
	this->reloadHeightText = new wxTextCtrl(this, ID_RELOADING_HEIGHT);
	this->horizontalAmplitudeText = new wxTextCtrl(this, ID_HORIZONTAL_AMPLITUDE);
	this->userAmplitudeText = new wxTextCtrl(this, ID_USER_AMPLITUDE);
	this->readyTicksText = new wxTextCtrl(this, ID_READY_TICKS);
	this->awaitReloadTicksText = new wxTextCtrl(this, ID_AWAIT_RELOAD_TICKS);
	this->loadingTicksText = new wxTextCtrl(this, ID_LOADING_TICKS);
	this->loadedTicksText = new wxTextCtrl(this, ID_LOADED_TICKS);

	for(int i = 0; i < NUMBER_OF_WEAPON_FLAG_INFORMATIONS; i ++){
		this->flags[i] = new wxCheckBox(this, ID_FLAGS,
			wxConvertMB2WX(wxGetApp().weaponFlagsBind[i].jname.c_str()));
	}

	//set
	for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
		this->collectionChoice->Insert(wxConvertMB2WX(
			wxGetApp().collectionInfo[i].jname.c_str()),i);
	}
	for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
		this->itemChoice->Insert(wxConvertMB2WX(
			wxGetApp().itemInfo[i].jname.c_str()),i);
	}
	this->itemChoice->Insert(_T("NONE"),
		NUMBER_OF_DEFINED_ITEMS);
	//	class
	for(int i = 0; i < NUMBER_OF_WEAPON_CLASS_INFORMATIONS; i ++){
		this->classChoice->Insert(wxConvertMB2WX(
			wxGetApp().weaponClassInfo[i].jname.c_str()),i);
	}
	this->classChoice->Insert(_T("NONE"),
		NUMBER_OF_WEAPON_CLASS_INFORMATIONS);
	
	//layout
	wxFlexGridSizer* leftSizer = new wxFlexGridSizer(21,2,0,0);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Collection")));
		leftSizer->Add(collectionChoice);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Palette")));
		leftSizer->Add(paletteText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Idle Sequence")));
		leftSizer->Add(idleSeqText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Firing Sequence")));
		leftSizer->Add(firingSeqText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Reload Sequence")));
		leftSizer->Add(reloadSeqText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Charging Sequence")));
		leftSizer->Add(chargingSeqText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Charged Sequence")));
		leftSizer->Add(chargedSeqText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Item")));
		leftSizer->Add(itemChoice);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Class")));
		leftSizer->Add(classChoice);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Light Intensity")));
		leftSizer->Add(lightIntensityText);

		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Light Intensity Decay")));
		leftSizer->Add(intensityDecayText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Idle Width")));
		leftSizer->Add(idleWidthText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Idle Height")));
		leftSizer->Add(idleHeightText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Firing Height")));
		leftSizer->Add(firingHeightText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Reloading Height")));
		leftSizer->Add(reloadHeightText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Horizontal Amplitude")));
		leftSizer->Add(horizontalAmplitudeText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Usre Amplitude")));
		leftSizer->Add(userAmplitudeText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Ready Ticks")));
		leftSizer->Add(readyTicksText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Await Reload Ticks")));
		leftSizer->Add(awaitReloadTicksText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Loading Ticks")));
		leftSizer->Add(loadingTicksText);
		leftSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Loaded Ticks")));
		leftSizer->Add(loadedTicksText);
	wxStaticBox* flagStaticBox = new wxStaticBox(this, wxID_ANY,
		_T("Flags"));
	wxStaticBoxSizer* flagSizer = new wxStaticBoxSizer(flagStaticBox,
		wxVERTICAL);
	wxFlexGridSizer* flagFlexSizer = new wxFlexGridSizer(
		NUMBER_OF_WEAPON_FLAG_INFORMATIONS, 1, 0,0);
	for(int i = 0; i < NUMBER_OF_WEAPON_FLAG_INFORMATIONS; i ++){
		flagFlexSizer->Add(this->flags[i]);
	}
	flagSizer->Add(flagFlexSizer);
	wxFlexGridSizer* allSizer = new wxFlexGridSizer(1,2,0,0);
	allSizer->Add(leftSizer);
	allSizer->Add(flagSizer);
	this->SetSizer(allSizer);
	allSizer->Fit(this);
	Layout();
}

WeaponAppearancePanel::~WeaponAppearancePanel()
{
}

void WeaponAppearancePanel::OnCollection(wxCommandEvent& ev)
{
	int type = common();
	int col = ev.GetSelection();
	int clut = getNumberFromTextCtrl(this->paletteText);
	weapon_definitions[type].collection =
		BUILD_COLLECTION(col, clut);
}
void WeaponAppearancePanel::OnPalette(wxCommandEvent& ev)
{
	int type = common();
	int col = this->collectionChoice->GetSelection();
	int clut = getNumberFromTextCtrl(&ev);
	weapon_definitions[type].collection =
		BUILD_COLLECTION(col, clut);
}
void WeaponAppearancePanel::OnIdleSeq(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnFiringSeq(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnReloadSeq(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnChargingSeq(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnChargedSeq(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnItem(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnClass(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnLightIntensity(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnIntensityDecay(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnIdleWidth(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnIdleHeight(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnFiringHeight(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnReloadingHeight(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnHorizontalAmplitude(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnUserAmplitude(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnReadyTicks(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnAwaitReloadTicks(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnLoadingTicks(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}
void WeaponAppearancePanel::OnLoadedTicks(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].idle_shape = getNumberFromTextCtrl(&ev);
}

void WeaponAppearancePanel::OnFlags(wxCommandEvent& ev)
{
	int type = common();
	int flag = 0;
	for(int i = 0; i < NUMBER_OF_WEAPON_FLAG_INFORMATIONS; i ++){
		if(this->flags[i]->IsChecked()){
			flag |= wxGetApp().weaponFlagsBind[i].bind;
		}
	}
	weapon_definitions[type].flags = flag;
}
int WeaponAppearancePanel::common()
{
	int type = wxGetApp().getEditingWeaponIndex();
	wxGetApp().setChanged(true);
	return type;
}
void WeaponAppearancePanel::setup()
{
	int type = wxGetApp().getEditingWeaponIndex();
	
	int collection = weapon_definitions[type].collection;
	int col = GET_COLLECTION(collection);
	int clut = GET_COLLECTION_CLUT(collection);
	collectionChoice->SetSelection(col);
	paletteText->SetValue(wx::string::getString("%d",
		clut));
	idleSeqText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].idle_shape));
	firingSeqText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].firing_shape));
	reloadSeqText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].reloading_shape));
	chargingSeqText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].charging_shape));
	chargedSeqText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].charged_shape));
	setChoice(itemChoice, weapon_definitions[type].item_type,
		NUMBER_OF_DEFINED_ITEMS);
	setChoice(classChoice, weapon_definitions[type].weapon_class,
		NUMBER_OF_WEAPON_CLASS_INFORMATIONS);
	lightIntensityText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].firing_light_intensity));
	intensityDecayText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].firing_intensity_decay_ticks));
	idleWidthText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].idle_width));
	idleHeightText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].idle_height));
	firingHeightText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].kick_height));
	reloadHeightText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].reload_height));
	horizontalAmplitudeText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].horizontal_amplitude));
	userAmplitudeText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].bob_amplitude));
	readyTicksText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].ready_ticks));
	awaitReloadTicksText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].await_reload_ticks));
	loadingTicksText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].loading_ticks));
	loadedTicksText->SetValue(wx::string::getString("%d",
		weapon_definitions[type].finish_loading_ticks));

	for(int i = 0; i < NUMBER_OF_WEAPON_FLAG_INFORMATIONS; i ++){
		this->flags[i]->SetValue(
			(weapon_definitions[type].flags & 
			wxGetApp().weaponFlagsBind[i].bind) != 0);
	}
}
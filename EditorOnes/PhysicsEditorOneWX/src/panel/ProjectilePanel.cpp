#include "ProjectilePanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_TYPE,
	ID_COLLECTION,
	ID_PALETTE,
	ID_SEQUENCE,
	ID_DETONATION_EFFECT,
	ID_DETONATION_MEDIA_EFFECT,
	ID_CONTRAIL_EFFECT,
	ID_TICKS_BETWEEN_CONTRAILS,
	ID_MAX_CONTRAILS,
	ID_MEDIA_PROMOTION,
	ID_RADIUS,
	ID_AREA,

	ID_DAMAGE_TYPE,
	ID_DAMAGE_BASE,
	ID_DAMAGE_RANDOM,
	ID_DAMAGE_SCALE,
	ID_DAMAGE_IS_ALIEN,

	ID_FLAGS,

	ID_SPEED,
	ID_MAX_RANGE,
	ID_SOUND_PITCH,
	ID_FLY_BY_SOUND,
	ID_REBOUND_SOUND,

	ID_RESET,
};

BEGIN_EVENT_TABLE(ProjectilePanel, wxPanel)
	EVT_LISTBOX(ID_TYPE, ProjectilePanel::OnType)

	EVT_CHOICE(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_PALETTE, ProjectilePanel::OnPalette)
	EVT_TEXT(ID_SEQUENCE, ProjectilePanel::OnSequence)
	EVT_CHOICE(ID_DETONATION_EFFECT, ProjectilePanel::OnDetonationEffect)
	EVT_CHOICE(ID_DETONATION_MEDIA_EFFECT, ProjectilePanel::OnDetonationMediaEffect)
	EVT_CHOICE(ID_CONTRAIL_EFFECT, ProjectilePanel::OnContrailEffect)
	EVT_TEXT(ID_TICKS_BETWEEN_CONTRAILS, ProjectilePanel::OnTicksBetweenContrails)
	EVT_TEXT(ID_MAX_CONTRAILS, ProjectilePanel::OnMaxContrail)
	EVT_TEXT(ID_MEDIA_PROMOTION, ProjectilePanel::OnMediaPromotion)
	EVT_TEXT(ID_RADIUS, ProjectilePanel::OnRadius)
	EVT_TEXT(ID_AREA, ProjectilePanel::OnArea)

	EVT_CHOICE(ID_DAMAGE_TYPE, ProjectilePanel::OnDamageType)
	EVT_TEXT(ID_DAMAGE_BASE, ProjectilePanel::OnDamageBase)
	EVT_TEXT(ID_DAMAGE_RANDOM, ProjectilePanel::OnDamageRandom)
	EVT_TEXT(ID_DAMAGE_SCALE, ProjectilePanel::OnDamageScale)
	EVT_CHECKBOX(ID_DAMAGE_IS_ALIEN, ProjectilePanel::OnDamageIsAlien)

	EVT_CHECKBOX(ID_FLAGS, ProjectilePanel::OnFlags)

	EVT_TEXT(ID_SPEED, ProjectilePanel::OnSpeed)
	EVT_TEXT(ID_MAX_RANGE, ProjectilePanel::OnMaxRange)
	EVT_TEXT(ID_SOUND_PITCH, ProjectilePanel::OnSoundPitch)
	EVT_CHOICE(ID_FLY_BY_SOUND, ProjectilePanel::OnFlyBySound)
	EVT_CHOICE(ID_REBOUND_SOUND, ProjectilePanel::OnReboundSound)

	EVT_BUTTON(ID_RESET, ProjectilePanel::OnReset)

END_EVENT_TABLE()

ProjectilePanel::ProjectilePanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	//create
	this->typeListBox = new wxListBox(this, ID_TYPE);
	
	this->collectionChoice = new wxChoice(this, ID_COLLECTION);
	this->paletteType = new wxTextCtrl(this, ID_PALETTE);
	this->sequenceText = new wxTextCtrl(this, ID_SEQUENCE);
	this->detonationEffectChoice = new wxChoice(this, ID_DETONATION_EFFECT);
	this->detonationMediaEffectChoice = new wxChoice(this, ID_DETONATION_MEDIA_EFFECT);
	this->contrailEffectChoice = new wxChoice(this, ID_CONTRAIL_EFFECT);
	this->ticksBetweenContrailsText = new wxTextCtrl(this, ID_TICKS_BETWEEN_CONTRAILS);
	this->maxContrailsText = new wxTextCtrl(this, ID_MAX_CONTRAILS);
	this->mediaPromotionText = new wxTextCtrl(this, ID_MEDIA_PROMOTION);
	this->radiusText = new wxTextCtrl(this, ID_RADIUS);
	this->areaText = new wxTextCtrl(this, ID_AREA);

	this->damageTypeChoice = new wxChoice(this, ID_DAMAGE_TYPE);
	this->damageBaseText = new wxTextCtrl(this, ID_DAMAGE_BASE);
	this->damageRandomText = new wxTextCtrl(this, ID_DAMAGE_RANDOM);
	this->damageScaleText = new wxTextCtrl(this, ID_DAMAGE_SCALE);
	this->damageIsAlienCheckBox = new wxCheckBox(this, ID_DAMAGE_IS_ALIEN,
		_T("Damage is alien"));

	for(int i = 0; i < NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS; i ++){
		this->flags[i] = new wxCheckBox(this, ID_FLAGS,
			wxConvertMB2WX(wxGetApp().projectileFlagsBind[i].jname.c_str()));
	}

	this->speedText = new wxTextCtrl(this, ID_SPEED);
	this->maxRangeText = new wxTextCtrl(this, ID_MAX_RANGE);
	this->soundPitchText = new wxTextCtrl(this, ID_SOUND_PITCH);
	this->flyBySoundChoice = new wxChoice(this, ID_FLY_BY_SOUND);
	this->reboundSoundChoice = new wxChoice(this, ID_REBOUND_SOUND);

	this->resetButton = new wxButton();
	//set
	for(int i = 0; i < NUMBER_OF_PROJECTILE_TYPES; i ++){
		this->typeListBox->Insert(wxConvertMB2WX(
			wxGetApp().projectileInfo[i].jname.c_str()), i);
	}
	this->typeListBox->SetMinSize(wxSize(-1, LIST_BOX_HEIGHT));
	areaText->SetHelpText(_T(
		"The radius the effect this projectile generates"));

	for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
		this->collectionChoice->Insert(wxConvertMB2WX(
			wxGetApp().collectionInfo[i].jname.c_str()),i);
	}
	for(int i = 0; i < NUMBER_OF_EFFECT_TYPES; i ++){
		this->detonationEffectChoice->Insert(wxConvertMB2WX(
			wxGetApp().effectInfo[i].jname.c_str()),i);
		this->detonationMediaEffectChoice->Insert(wxConvertMB2WX(
			wxGetApp().effectInfo[i].jname.c_str()),i);
		this->contrailEffectChoice->Insert(wxConvertMB2WX(
			wxGetApp().effectInfo[i].jname.c_str()),i);
	}
	this->detonationEffectChoice->Insert(
		_T("NONE"), NUMBER_OF_EFFECT_TYPES);
	this->detonationMediaEffectChoice->Insert(
		_T("NONE"), NUMBER_OF_EFFECT_TYPES);
	this->contrailEffectChoice->Insert(
		_T("NONE"), NUMBER_OF_EFFECT_TYPES);

	for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
		this->damageTypeChoice->Insert(wxConvertMB2WX(
			wxGetApp().damageInfo[i].jname.c_str()),i);
	}
	this->damageTypeChoice->Insert(_T("NONE"),
		NUMBER_OF_DAMAGE_TYPES);

	for(int i = 0; i < NUMBER_OF_SOUND_DEFINITIONS; i ++){
		this->flyBySoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()),i);
		this->reboundSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()),i);
	}
	this->flyBySoundChoice->Insert(_T("NONE"),
		NUMBER_OF_SOUND_DEFINITIONS);
	this->reboundSoundChoice->Insert(_T("NONE"),
		NUMBER_OF_SOUND_DEFINITIONS);

	//layout
	//	left
	wxFlexGridSizer* leftSizer = new wxFlexGridSizer(2,1,0,0);
		wxFlexGridSizer* leftUpSizer = new wxFlexGridSizer(11,2,0,0);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Collection")));
		leftUpSizer->Add(this->collectionChoice);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Palette")));
		leftUpSizer->Add(this->paletteType);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Sequence")));
		leftUpSizer->Add(this->sequenceText);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Detonation Effect")));
		leftUpSizer->Add(this->detonationEffectChoice);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Detonation Media Effect")));
		leftUpSizer->Add(this->detonationMediaEffectChoice);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Contrail Effect")));
		leftUpSizer->Add(this->contrailEffectChoice);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Ticks Between Contrail")));
		leftUpSizer->Add(this->ticksBetweenContrailsText);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Max Contrails")));
		leftUpSizer->Add(this->maxContrailsText);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Media Promotion")));
		leftUpSizer->Add(this->mediaPromotionText);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Radius")));
		leftUpSizer->Add(this->radiusText);
		leftUpSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Area Of Effect")));
		leftUpSizer->Add(this->areaText);

		wxStaticBox* damageStaticBox = new wxStaticBox(this, wxID_ANY,
			_T("Damage"));
		wxStaticBoxSizer* damageStaticBoxSizer = new wxStaticBoxSizer(
			damageStaticBox, wxVERTICAL);
		wxFlexGridSizer* damageFlexGridSizer = new wxFlexGridSizer(5,2,0,0);
		damageFlexGridSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Type")));
		damageFlexGridSizer->Add(this->damageTypeChoice);
		damageFlexGridSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Base")));
		damageFlexGridSizer->Add(this->damageBaseText);
		damageFlexGridSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Random")));
		damageFlexGridSizer->Add(this->damageRandomText);
		damageFlexGridSizer->Add(new wxStaticText(this, wxID_ANY,
			_T("Scale")));
		damageFlexGridSizer->Add(this->damageScaleText);
		damageFlexGridSizer->Add(this->damageIsAlienCheckBox);
		damageStaticBoxSizer->Add(damageFlexGridSizer);
	leftSizer->Add(leftUpSizer);
	leftSizer->Add(damageStaticBoxSizer);

	//	center
	wxFlexGridSizer* centerSizer = new wxFlexGridSizer(5,2,0,0);
	centerSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Speed")));
	centerSizer->Add(this->speedText);
	centerSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Max Range (-1 to infinity)")));
	centerSizer->Add(this->maxRangeText);
	centerSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Sound Pitch")));
	centerSizer->Add(this->soundPitchText);
	centerSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Fly By Sound")));
	centerSizer->Add(this->flyBySoundChoice);
	centerSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Rebound Sound")));
	centerSizer->Add(this->reboundSoundChoice);

	//	right
	wxFlexGridSizer* rightSizer = new wxFlexGridSizer(2,1,0,0);
		wxStaticBox* flagsStaticBox = new wxStaticBox(this, wxID_ANY,
			_T("Flags"));
		wxStaticBoxSizer* flagsStaticBoxSizer = new wxStaticBoxSizer(
			flagsStaticBox, wxVERTICAL);
		wxFlexGridSizer* flagsSizer = new wxFlexGridSizer(
			NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS,1,0,0);
		for(int i = 0; i < NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS; i ++){
			flagsSizer->Add(this->flags[i]);
		}
		flagsStaticBoxSizer->Add(flagsSizer);
	rightSizer->Add(flagsStaticBoxSizer);
	rightSizer->Add(this->resetButton);

	wxFlexGridSizer* allSizer = new wxFlexGridSizer(1,4,0,0);
	allSizer->Add(this->typeListBox);
	allSizer->Add(leftSizer);
	allSizer->Add(centerSizer);
	allSizer->Add(rightSizer);
	this->SetSizer(allSizer);
	allSizer->Fit(this);
	Layout();
}

ProjectilePanel::~ProjectilePanel()
{
}

void ProjectilePanel::OnType(wxCommandEvent& ev)
{
	int index = ev.GetSelection();
	if(index >= 0 && index < NUMBER_OF_PROJECTILE_TYPES){
		wxGetApp().setEditingProjectileIndex(index);
		common();
		setup();
	}
}
void ProjectilePanel::OnCollection(wxCommandEvent& ev)
{
	int type = common();
	int col = ev.GetSelection();
	int clut = getNumberFromTextCtrl(this->paletteType);
	projectile_definitions[type].collection = BUILD_COLLECTION(col, clut);
}
void ProjectilePanel::OnPalette(wxCommandEvent& ev)
{
	int type = common();
	int col = this->collectionChoice->GetSelection();
	int clut = getNumberFromTextCtrl(&ev);
	projectile_definitions[type].collection = BUILD_COLLECTION(col, clut);
}
void ProjectilePanel::OnSequence(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].shape = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnDetonationEffect(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].detonation_effect = 
		getChoice(&ev, NUMBER_OF_EFFECT_TYPES);
}
void ProjectilePanel::OnDetonationMediaEffect(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].media_detonation_effect = 
		getChoice(&ev, NUMBER_OF_EFFECT_TYPES);
}
void ProjectilePanel::OnContrailEffect(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].contrail_effect = 
		getChoice(&ev, NUMBER_OF_EFFECT_TYPES);
}
void ProjectilePanel::OnTicksBetweenContrails(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].ticks_between_contrails = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnMaxContrail(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].maximum_contrails = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnMediaPromotion(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].media_projectile_promotion = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnRadius(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].radius = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnArea(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].area_of_effect = getNumberFromTextCtrl(&ev);
}

void ProjectilePanel::OnDamageType(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].damage.type = getChoice(&ev, NUMBER_OF_DAMAGE_TYPES);
}
void ProjectilePanel::OnDamageBase(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].damage.base = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnDamageRandom(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].damage.random = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnDamageScale(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].damage.scale = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnDamageIsAlien(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].damage.flags = ev.IsChecked() ? 1: 0;
}

void ProjectilePanel::OnFlags(wxCommandEvent& ev)
{
	int type = common();
	int flags = 0;
	for(int i = 0; i < NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS; i ++){
		SET_FLAG32(flags, i, this->flags[i]->GetValue());
	}
	projectile_definitions[type].flags = flags;
}
void ProjectilePanel::OnSpeed(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].speed = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnMaxRange(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].maximum_range = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnSoundPitch(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].sound_pitch = getNumberFromTextCtrl(&ev);
}
void ProjectilePanel::OnFlyBySound(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].flyby_sound = getChoice(&ev, NUMBER_OF_SOUND_DEFINITIONS);
}
void ProjectilePanel::OnReboundSound(wxCommandEvent& ev)
{
	int type = common();
	projectile_definitions[type].rebound_sound = getChoice(&ev, NUMBER_OF_SOUND_DEFINITIONS);
}

void ProjectilePanel::OnReset(wxCommandEvent& ev)
{
	int type = common();
	memcpy(&projectile_definitions[type],
		wxGetApp().getDefaultValues()->getProjectileDefinition(type),
		sizeof(projectile_definition));
	setup();
}

void ProjectilePanel::setup()
{
	int type = wxGetApp().getEditingProjectileIndex();
	int collection = projectile_definitions[type].collection;
	int col = GET_COLLECTION(collection);
	int clut = GET_COLLECTION_CLUT(collection);
	collectionChoice->SetSelection(col);
	paletteType->SetValue(wx::string::getString("%d",
		clut));
	sequenceText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].shape));
	setChoice(detonationEffectChoice,
		projectile_definitions[type].detonation_effect, NUMBER_OF_EFFECT_TYPES);
	setChoice(detonationMediaEffectChoice,
		projectile_definitions[type].media_detonation_effect, NUMBER_OF_EFFECT_TYPES);
	setChoice(contrailEffectChoice,
		projectile_definitions[type].contrail_effect, NUMBER_OF_EFFECT_TYPES);
	ticksBetweenContrailsText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].ticks_between_contrails));
	maxContrailsText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].maximum_contrails));
	mediaPromotionText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].media_projectile_promotion));
	radiusText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].radius));
	areaText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].area_of_effect));

	setChoice(damageTypeChoice,
		projectile_definitions[type].damage.type, NUMBER_OF_EFFECT_TYPES);
	damageBaseText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].damage.base));
	damageRandomText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].damage.random));
	damageScaleText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].damage.scale));
	damageIsAlienCheckBox->SetValue(
		projectile_definitions[type].damage.flags != 0);

	for(int i = 0; i < NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS; i ++){
		this->flags[i]->SetValue(
			(projectile_definitions[type].flags &
			wxGetApp().projectileFlagsBind[i].bind) != 0);
	}

	speedText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].speed));
	maxRangeText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].maximum_range));
	soundPitchText->SetValue(wx::string::getString("%d",
		projectile_definitions[type].sound_pitch));
	setChoice(flyBySoundChoice,
		projectile_definitions[type].flyby_sound, NUMBER_OF_SOUND_DEFINITIONS);
	setChoice(reboundSoundChoice,
		projectile_definitions[type].rebound_sound, NUMBER_OF_SOUND_DEFINITIONS);
}

int ProjectilePanel::common()
{
	int type = wxGetApp().getEditingProjectileIndex();
	wxGetApp().setChanged(true);
	return type;
}

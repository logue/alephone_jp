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
	this->damageIsAlienCheckBox = new wxCheckBox(this, ID_DAMAGE_IS_ALIEN);

	for(int i = 0; i < NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS; i ++){
		this->flags[i] = new wxCheckBox(this, ID_FLAGS);
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
			_T("Flags");
		wxStaticBoxSizer* flagsStaticBoxSizer = new wxStaticBoxSizer(
			flagsStaticBox, wxVERTICAL);
		wxFlexGridSizer* flagsSizer = new wxFlexGridSizer(
			NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS,1,0,0);
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
	common();
}
void ProjectilePanel::OnCollection(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnPalette(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnSequence(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnDetonationEffect(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnDetonationMediaEffect(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnContrailEffect(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnTicksBetweenContrails(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnMaxContrail(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnMediaPromotion(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnRadius(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnArea(wxCommandEvent& ev)
{
	int type = common();
}

void ProjectilePanel::OnDamageType(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnDamageBase(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnDamageRandom(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnDamageScale(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnDamageIsAlien(wxCommandEvent& ev)
{
	int type = common();
}

void ProjectilePanel::OnFlags(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnSpeed(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnMaxRange(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnSoundPitch(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnFlyBySound(wxCommandEvent& ev)
{
	int type = common();
}
void ProjectilePanel::OnReboundSound(wxCommandEvent& ev)
{
	int type = common();
}

void ProjectilePanel::OnReset(wxCommandEvent& ev)
{
	int type = common();
}

void ProjectilePanel::setup()
{
}

int ProjectilePanel::common()
{
	int type = wxGetApp().getEditingProjectileIndex();
	wxGetApp().setNewAndChanged(false, true);
	return type;
}

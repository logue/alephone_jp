#include "MonsterAppearancePanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_COLLECTION,
	ID_PALETTE,
	ID_VITALITY,
	ID_CLASS,
	ID_RADIUS,
	ID_HEIGHT,
	ID_HOVER,
	ID_MIN_LEDGE,
	ID_MAX_LEDGE,
	ID_EXT_VEL_SCALE,
	ID_CARRY_ITEM,
	ID_HALF_VISUAL_ARC,
	ID_VERT_VISUAL_ARC,
	ID_INTELLIGENCE,
	ID_SPEED_TEXT,
	ID_SPEED_CHOICE,
	ID_GRAVITY,

	ID_STATIONALY,
	ID_MOVING,
	ID_HITTING,
	ID_SOFT_DYING,
	ID_SOFT_DEAD,
	ID_HARD_DYING,
	ID_HARD_DEAD,
	ID_TELEPORT_IN,
	ID_TELEPORT_OUT,

	ID_SHRAPNEL_RADIUS,
	ID_SHRAPNEL_BASE,
	ID_SHRAPNEL_RND,
	ID_SHRAPNEL_SCALE,
	ID_SHRAPNEL_TYPE,
	ID_SHRAPNEL_IS_ALIEN,

	ID_COPY_FROM,
	
	ID_PITCH,
	ID_ACTIVATION,
	ID_FRIEND_ACT,
	ID_CLEAR,
	ID_KILL,
	ID_APOLYGY,
	ID_FRIEND_FIRE,
	ID_FLAMING,
	ID_RANDOM,
	ID_RANDOM_MASK,
	
	ID_EFFECT,
	ID_EFFECT_MELEE,
	ID_EFFECT_CONTRAIL,

	ID_RESET,
};

MonsterAppearancePanel::MonsterAppearancePanel(wxWindow* parent, wxWindowID id)
:wxPanel(parent, id)
{
	//create
	//	appearance/system
	this->collectionChoice = new wxChoice(this, ID_COLLECTION);
	this->paletteText = new wxTextCtrl(this, ID_PALETTE);
	this->vitalityText = new wxTextCtrl(this, ID_VITALITY);
	this->classChoice = new wxChoice(this, ID_CLASS);
	this->radiusText = new wxTextCtrl(this, ID_RADIUS);
	this->heightText = new wxTextCtrl(this, ID_HEIGHT);
	this->hoverText = new wxTextCtrl(this, ID_HOVER);
	this->minLedgeText = new wxTextCtrl(this, ID_MIN_LEDGE);
	this->maxLedgeText = new wxTextCtrl(this, ID_MAX_LEDGE);
	this->extVelScaleText = new wxTextCtrl(this, ID_EXT_VEL_SCALE);
	this->carryItemChoice = new wxChoice(this, ID_CARRY_ITEM);
	this->halfVisualArcText = new wxTextCtrl(this, ID_HALF_VISUAL_ARC);
	this->vertVisualArcText = new wxTextCtrl(this, ID_VERT_VISUAL_ARC);
	this->intelligenceChoice = new wxChoice(this, ID_INTELLIGENCE);
	this->speedText = new wxTextCtrl(this, ID_SPEED_TEXT);
	this->speedChoice = new wxChoice(this, ID_SPEED_CHOICE);
	this->gravityText = new wxTextCtrl(this, ID_GRAVITY);

	//sequences
	this->stationalyText = new wxTextCtrl(this, ID_STATIONALY);
	this->movingText = new wxTextCtrl(this, ID_MOVING);
	this->hittingText = new wxTextCtrl(this, ID_HITTING);
	this->softDyingText = new wxTextCtrl(this, ID_SOFT_DYING);
	this->softDeadText = new wxTextCtrl(this, ID_SOFT_DEAD);
	this->hardDyingText = new wxTextCtrl(this, ID_HARD_DYING);
	this->hardDeadText = new wxTextCtrl(this, ID_HARD_DEAD);
	this->teleportInText = new wxTextCtrl(this, ID_TELEPORT_IN);
	this->teleportOutText = new wxTextCtrl(this, ID_TELEPORT_OUT);

	//shrapnel damages
	this->shrapnelRadiusText = new wxTextCtrl(this, ID_SHRAPNEL_RADIUS);
	this->shrapnelBaseText = new wxTextCtrl(this, ID_SHRAPNEL_BASE);
	this->shrapnelRndText = new wxTextCtrl(this, ID_SHRAPNEL_RND);
	this->shrapnelScaleText = new wxTextCtrl(this, ID_SHRAPNEL_SCALE);
	this->shrapnelTypeChoice = new wxChoice(this, ID_SHRAPNEL_TYPE);
	this->shrapnelIsAlienCheckbox = new wxCheckBox(this, ID_SHRAPNEL_IS_ALIEN,
		_T("Shrapnel is alien"));

	copyFromButton = new wxButton(this, ID_COPY_FROM, _T("Copy from ..."));

	//sound
	soundPitchText = new wxTextCtrl(this, ID_PITCH);
	soundActivationChoice = new wxChoice(this, ID_ACTIVATION);
	soundFriendActChoice = new wxChoice(this, ID_FRIEND_ACT);
	soundClearChoice = new wxChoice(this, ID_CLEAR);
	soundKillChoice = new wxChoice(this, ID_KILL);
	soundApologyChoice = new wxChoice(this, ID_APOLYGY);
	soundFriendFireChoice = new wxChoice(this, ID_FRIEND_FIRE);
	soundFlamingChoice = new wxChoice(this, ID_FLAMING);
	soundRandomChoice = new wxChoice(this, ID_RANDOM);
	soundRandomMask = new wxTextCtrl(this, ID_RANDOM_MASK);

	//effect
	effectChoice = new wxChoice(this, ID_EFFECT);
	effectMeleeChoice = new wxChoice(this, ID_EFFECT_MELEE);
	effectContrailChoice = new wxChoice(this, ID_EFFECT_CONTRAIL);

	//reset
	resetButton = new wxButton(this, ID_RESET, _T("Reset"));

	//static boxes
	wxStaticBox* appearanceStaticBox = new wxStaticBox(this, wxID_ANY, _T("Apeearance"));
	wxStaticBox* shrapnelStaticBox = new wxStaticBox(this, wxID_ANY, _T("Shrapnel damages"));
	wxStaticBox* soundStaticBox = new wxStaticBox(this, wxID_ANY, _T("Sounds"));
	wxStaticBox* effectStaticBox = new wxStaticBox(this, wxID_ANY, _T("Effects"));
	
	//set
	//	collection
	for(int i = 0; i < NUMBER_OF_COLLECTIONS; i ++){
		collectionChoice->Insert(wxConvertMB2WX(wxGetApp().collectionInfo[i].jname.c_str()), i);
	}
	//	class
	for(int i = 0; i < NUMBER_OF_CLASS_INFORMATIONS; i ++){
		classChoice->Insert(wxConvertMB2WX(wxGetApp().monsterClassBind[i].jname.c_str()), i);
	}
	//	item
	for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
		classChoice->Insert(wxConvertMB2WX(wxGetApp().itemInfo[i].jname.c_str()), i);
	}
	//	intelligence
	for(int i = 0; i < NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS; i ++){
		intelligenceChoice->Insert(wxConvertMB2WX(wxGetApp().monsterIntelligenceBind[i].jname.c_str()), i);
	}
	//	speed
	for(int i = 0; i < NUMBER_OF_SPEED_INFORMATIONS; i ++){
		intelligenceChoice->Insert(wxConvertMB2WX(wxGetApp().speedBind[i].jname.c_str()), i);
	}
	//	shrapnel type
	//	sounds
	//	effects

	//layout
	wxBoxSizer* baseSizer = new wxBoxSizer(wxHORIZONTAL);

	//	left column
	wxFlexGridSizer* infoSizer = new wxFlexGridSizer(17, 2, 0,0);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Collection")));
	infoSizer->Add(this->collectionChoice);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Palette")));
	infoSizer->Add(this->paletteText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Vitality")));
	infoSizer->Add(this->vitalityText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Class")));
	infoSizer->Add(this->classChoice);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Radius")));
	infoSizer->Add(this->radiusText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Height")));
	infoSizer->Add(this->heightText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Hover")));
	infoSizer->Add(this->hoverText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Min Ledge")));
	infoSizer->Add(this->minLedgeText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Max Ledge")));
	infoSizer->Add(this->maxLedgeText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("External Velocity Scale")));
	infoSizer->Add(this->extVelScaleText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Carry Item")));
	infoSizer->Add(this->carryItemChoice);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Half Visual Arc")));
	infoSizer->Add(this->halfVisualArcText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Vertical Visual Arc")));
	infoSizer->Add(this->vertVisualArcText);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Intelligence")));
	infoSizer->Add(this->intelligenceChoice);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Speed")));
	infoSizer->Add(this->speedText);
	infoSizer->Add(new wxPanel(this, wxID_ANY), 0,wxEXPAND);
	infoSizer->Add(this->speedChoice);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Gravity")));
	infoSizer->Add(this->gravityText);

	//	center column
	wxFlexGridSizer* appearanceAndShrapnelSizer = new wxFlexGridSizer(3, 1,0,0);
	//		appearance
	wxStaticBoxSizer* appearanceStaticSizer = new wxStaticBoxSizer(appearanceStaticBox,
		wxVERTICAL);
	wxFlexGridSizer* appearanceFlexSizer = new wxFlexGridSizer(9,2,0,0);
	appearanceFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Stationaly")), 0, wxEXPAND);
	appearanceFlexSizer->Add(this->stationalyText, 0, wxEXPAND);
	appearanceFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Moving")), 0, wxEXPAND);
	appearanceFlexSizer->Add(this->movingText, 0, wxEXPAND);
	appearanceFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Hitting")), 0, wxEXPAND);
	appearanceFlexSizer->Add(this->hittingText, 0, wxEXPAND);
	appearanceFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Soft Dying")), 0, wxEXPAND);
	appearanceFlexSizer->Add(this->softDyingText, 0, wxEXPAND);
	appearanceFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Soft Dead")), 0, wxEXPAND);
	appearanceFlexSizer->Add(this->softDeadText, 0, wxEXPAND);
	appearanceFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Hard Dying")), 0, wxEXPAND);
	appearanceFlexSizer->Add(this->hardDyingText, 0, wxEXPAND);
	appearanceFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Hard Dead")), 0, wxEXPAND);
	appearanceFlexSizer->Add(this->hardDeadText, 0, wxEXPAND);
	appearanceFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Teleport In")), 0, wxEXPAND);
	appearanceFlexSizer->Add(this->teleportInText, 0, wxEXPAND);
	appearanceFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Teleport Out")), 0, wxEXPAND);
	appearanceFlexSizer->Add(this->teleportOutText, 0, wxEXPAND);
	appearanceStaticSizer->Add(appearanceFlexSizer);
	appearanceAndShrapnelSizer->Add(appearanceStaticSizer);
	//		shrapnel
	wxStaticBoxSizer* shrapnelStaticSizer = new wxStaticBoxSizer(shrapnelStaticBox, wxVERTICAL);
		wxFlexGridSizer* shrapnelFlexSizer = new wxFlexGridSizer(2,1,0,0);
			wxFlexGridSizer* shrapnelDamageFlexSizer = new wxFlexGridSizer(5,2,0,0);
				shrapnelDamageFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Radius")));
				shrapnelDamageFlexSizer->Add(this->shrapnelRadiusText);
				shrapnelDamageFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Base")));
				shrapnelDamageFlexSizer->Add(this->shrapnelBaseText);
				shrapnelDamageFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Random")));
				shrapnelDamageFlexSizer->Add(this->shrapnelRndText);
				shrapnelDamageFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Scale")));
				shrapnelDamageFlexSizer->Add(this->shrapnelScaleText);
				shrapnelDamageFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Type")));
				shrapnelDamageFlexSizer->Add(this->shrapnelTypeChoice);
		shrapnelFlexSizer->Add(shrapnelDamageFlexSizer);
		shrapnelFlexSizer->Add(this->shrapnelIsAlienCheckbox);
	shrapnelStaticSizer->Add(shrapnelFlexSizer);
	appearanceAndShrapnelSizer->Add(shrapnelStaticSizer);
	//		button
	appearanceAndShrapnelSizer->Add(this->copyFromButton,0,wxEXPAND,0,0);


	//	right column
	wxFlexGridSizer* soundAndEffectSizer = new wxFlexGridSizer(3, 1, 0,0);
	//	sound
		wxFlexGridSizer* soundFlexSizer = new wxFlexGridSizer(10,2,0,0);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Pitch")));
			soundFlexSizer->Add(this->soundPitchText);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Activation")));
			soundFlexSizer->Add(this->soundActivationChoice);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Friend Activation")));
			soundFlexSizer->Add(this->soundFriendActChoice);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Clear")));
			soundFlexSizer->Add(this->soundClearChoice);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Kill")));
			soundFlexSizer->Add(this->soundKillChoice);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Apology")));
			soundFlexSizer->Add(this->soundApologyChoice);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Friend Fire")));
			soundFlexSizer->Add(this->soundFriendFireChoice);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Flaming")));
			soundFlexSizer->Add(this->soundFlamingChoice);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Random")));
			soundFlexSizer->Add(this->soundRandomChoice);
			soundFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Random Mask")));
			soundFlexSizer->Add(this->soundRandomMask);
		
		wxStaticBoxSizer* soundStaticSizer = new wxStaticBoxSizer(soundStaticBox, wxVERTICAL);
		soundStaticSizer->Add(soundFlexSizer);
	soundAndEffectSizer->Add(soundStaticSizer);
	//	effect
		wxFlexGridSizer* effectFlexSizer = new wxFlexGridSizer(3,2,0,0);
			effectFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Effect")));
			effectFlexSizer->Add(this->effectChoice);
			effectFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Melee Effect")));
			effectFlexSizer->Add(this->effectMeleeChoice);
			effectFlexSizer->Add(new wxStaticText(this, wxID_ANY, _T("Contrail Effect")));
			effectFlexSizer->Add(this->effectContrailChoice);
			
		wxStaticBoxSizer* effectStaticSizer = new wxStaticBoxSizer(effectStaticBox, wxVERTICAL);
		effectStaticSizer->Add(effectFlexSizer);
	soundAndEffectSizer->Add(effectStaticSizer);
	soundAndEffectSizer->Add(this->resetButton);

	baseSizer->Add(infoSizer);
	baseSizer->Add(appearanceAndShrapnelSizer);
	baseSizer->Add(soundAndEffectSizer);

	this->SetSizer(baseSizer);
	baseSizer->Fit(this);
	this->Layout();

}
MonsterAppearancePanel::~MonsterAppearancePanel()
{
}

void MonsterAppearancePanel::OnCollection(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnPalette(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnVitality(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnClass(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnRadius(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnHeight(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnHover(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnMinLedge(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnMaxLedge(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnExtVelScale(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnCarryItem(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnHalfVisualArc(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnVertVisualArc(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnIntelligence(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSpeedText(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSpeedChoice(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnGravity(wxCommandEvent& ev)
{
}

void MonsterAppearancePanel::OnStationaly(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnMoving(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnHitting(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoftDying(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoftDead(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnHardDying(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnHardDead(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnTeleportIn(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnTeleportOut(wxCommandEvent& ev)
{
}

void MonsterAppearancePanel::OnShrapnelRadius(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnShrapnelBase(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnShrapnelRnd(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnShrapnelScale(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnShrapnelType(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnShrapnelIsAlien(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnCopyFrom(wxCommandEvent& ev)
{
}

void MonsterAppearancePanel::OnSoundPitch(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoundActivation(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoundFriendAct(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoundClear(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoundKill(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoundApology(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoundFriendFire(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoundFlaming(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoundRandom(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnSoundRandomMask(wxCommandEvent& ev)
{
}

void MonsterAppearancePanel::OnEffect(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnEffectMelee(wxCommandEvent& ev)
{
}
void MonsterAppearancePanel::OnEffectContrail(wxCommandEvent& ev)
{
}

void MonsterAppearancePanel::OnResetButton(wxCommandEvent& ev)
{
}

void MonsterAppearancePanel::setup()
{
}

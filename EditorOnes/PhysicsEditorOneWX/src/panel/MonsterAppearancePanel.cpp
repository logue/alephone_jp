#include "MonsterAppearancePanel.h"
#include "../PhysicsEditorOneWX.h"
#include "../MonsterTypeSelectDialog.h"

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

	ID_DOOR_RETRY_MASK,

	ID_RESET,
};

BEGIN_EVENT_TABLE(MonsterAppearancePanel, wxPanel)
	EVT_CHOICE(ID_COLLECTION, MonsterAppearancePanel::OnCollection)
	EVT_CHOICE(ID_PALETTE, MonsterAppearancePanel::OnPalette)
	EVT_TEXT(ID_VITALITY, MonsterAppearancePanel::OnVitality)
	EVT_CHOICE(ID_CLASS, MonsterAppearancePanel::OnClass)
	EVT_TEXT(ID_RADIUS, MonsterAppearancePanel::OnRadius)
	EVT_TEXT(ID_HEIGHT, MonsterAppearancePanel::OnHeight)
	EVT_TEXT(ID_HOVER, MonsterAppearancePanel::OnHover)
	EVT_TEXT(ID_MIN_LEDGE, MonsterAppearancePanel::OnMinLedge)
	EVT_TEXT(ID_MAX_LEDGE, MonsterAppearancePanel::OnMaxLedge)
	EVT_TEXT(ID_EXT_VEL_SCALE, MonsterAppearancePanel::OnExtVelScale)
	EVT_CHOICE(ID_CARRY_ITEM, MonsterAppearancePanel::OnCarryItem)
	EVT_TEXT(ID_HALF_VISUAL_ARC, MonsterAppearancePanel::OnHalfVisualArc)
	EVT_TEXT(ID_VERT_VISUAL_ARC, MonsterAppearancePanel::OnVertVisualArc)
	EVT_CHOICE(ID_INTELLIGENCE, MonsterAppearancePanel::OnIntelligence)
	EVT_TEXT(ID_SPEED_TEXT, MonsterAppearancePanel::OnSpeedText)
	EVT_CHOICE(ID_SPEED_CHOICE, MonsterAppearancePanel::OnSpeedChoice)
	EVT_TEXT(ID_GRAVITY, MonsterAppearancePanel::OnGravity)

	EVT_TEXT(ID_STATIONALY, MonsterAppearancePanel::OnStationaly)
	EVT_TEXT(ID_MOVING, MonsterAppearancePanel::OnMoving)
	EVT_TEXT(ID_HITTING, MonsterAppearancePanel::OnHitting)
	EVT_TEXT(ID_SOFT_DYING, MonsterAppearancePanel::OnSoftDying)
	EVT_TEXT(ID_SOFT_DEAD, MonsterAppearancePanel::OnSoftDead)
	EVT_TEXT(ID_HARD_DYING, MonsterAppearancePanel::OnHardDying)
	EVT_TEXT(ID_HARD_DEAD, MonsterAppearancePanel::OnHardDead)
	EVT_TEXT(ID_TELEPORT_IN, MonsterAppearancePanel::OnTeleportIn)
	EVT_TEXT(ID_TELEPORT_OUT, MonsterAppearancePanel::OnTeleportOut)

	EVT_TEXT(ID_SHRAPNEL_RADIUS, MonsterAppearancePanel::OnShrapnelRadius)
	EVT_TEXT(ID_SHRAPNEL_BASE, MonsterAppearancePanel::OnShrapnelBase)
	EVT_TEXT(ID_SHRAPNEL_RND, MonsterAppearancePanel::OnShrapnelRnd)
	EVT_TEXT(ID_SHRAPNEL_SCALE, MonsterAppearancePanel::OnShrapnelScale)
	EVT_CHOICE(ID_SHRAPNEL_TYPE, MonsterAppearancePanel::OnShrapnelType)
	EVT_CHECKBOX(ID_SHRAPNEL_IS_ALIEN, MonsterAppearancePanel::OnShrapnelIsAlien)

	EVT_BUTTON(ID_COPY_FROM, MonsterAppearancePanel::OnCopyFrom)

	EVT_TEXT(ID_PITCH, MonsterAppearancePanel::OnSoundPitch)
	EVT_CHOICE(ID_ACTIVATION, MonsterAppearancePanel::OnSoundActivation)
	EVT_CHOICE(ID_FRIEND_ACT, MonsterAppearancePanel::OnSoundFriendAct)
	EVT_CHOICE(ID_CLEAR, MonsterAppearancePanel::OnSoundClear)
	EVT_CHOICE(ID_KILL, MonsterAppearancePanel::OnSoundKill)
	EVT_CHOICE(ID_APOLYGY, MonsterAppearancePanel::OnSoundApology)
	EVT_CHOICE(ID_FRIEND_FIRE, MonsterAppearancePanel::OnSoundFriendFire)
	EVT_CHOICE(ID_FLAMING, MonsterAppearancePanel::OnSoundFlaming)
	EVT_CHOICE(ID_RANDOM, MonsterAppearancePanel::OnSoundRandom)
	EVT_TEXT(ID_RANDOM_MASK, MonsterAppearancePanel::OnSoundRandomMask)

	EVT_CHOICE(ID_EFFECT, MonsterAppearancePanel::OnEffect)
	EVT_CHOICE(ID_EFFECT_MELEE, MonsterAppearancePanel::OnEffectMelee)
	EVT_CHOICE(ID_EFFECT_CONTRAIL, MonsterAppearancePanel::OnEffectContrail)

	EVT_TEXT(ID_DOOR_RETRY_MASK, MonsterAppearancePanel::OnDoorRetryMask)

	EVT_BUTTON(ID_RESET, MonsterAppearancePanel::OnResetButton)
END_EVENT_TABLE()


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
	this->paletteText->SetSize(wxSize(100,-1));
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

	doorRetryMaskText = new wxTextCtrl(this, ID_DOOR_RETRY_MASK);

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
		carryItemChoice->Insert(wxConvertMB2WX(wxGetApp().itemInfo[i].jname.c_str()), i);
	}
	carryItemChoice->Insert(_T("NONE"), NUMBER_OF_DEFINED_ITEMS);
	//	intelligence
	for(int i = 0; i < NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS; i ++){
		intelligenceChoice->Insert(wxConvertMB2WX(wxGetApp().monsterIntelligenceBind[i].jname.c_str()), i);
	}
	//	speed
	for(int i = 0; i < NUMBER_OF_SPEED_INFORMATIONS; i ++){
		speedChoice->Insert(wxConvertMB2WX(wxGetApp().speedBind[i].jname.c_str()), i);
	}
	speedChoice->Insert(_T("Other"), NUMBER_OF_SPEED_INFORMATIONS);
	//	shrapnel type
	for(int i = 0; i < NUMBER_OF_DAMAGE_TYPES; i ++){
		shrapnelTypeChoice->Insert(wxConvertMB2WX(wxGetApp().damageInfo[i].jname.c_str()), i);
	}
	shrapnelTypeChoice->Insert(_T("NONE"), NUMBER_OF_DAMAGE_TYPES);
	//	sounds
	for(int i = 0; i < NUMBER_OF_SOUND_DEFINITIONS; i ++){
		soundActivationChoice->Insert(wxConvertMB2WX(wxGetApp().soundInfo[i].jname.c_str()), i);
		soundFriendActChoice->Insert(wxConvertMB2WX(wxGetApp().soundInfo[i].jname.c_str()), i);
		soundClearChoice->Insert(wxConvertMB2WX(wxGetApp().soundInfo[i].jname.c_str()), i);
		soundKillChoice->Insert(wxConvertMB2WX(wxGetApp().soundInfo[i].jname.c_str()), i);
		soundApologyChoice->Insert(wxConvertMB2WX(wxGetApp().soundInfo[i].jname.c_str()), i);
		soundFriendFireChoice->Insert(wxConvertMB2WX(wxGetApp().soundInfo[i].jname.c_str()), i);
		soundFlamingChoice->Insert(wxConvertMB2WX(wxGetApp().soundInfo[i].jname.c_str()), i);
		soundRandomChoice->Insert(wxConvertMB2WX(wxGetApp().soundInfo[i].jname.c_str()), i);
	}
	soundActivationChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	soundFriendActChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	soundClearChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	soundKillChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	soundApologyChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	soundFriendFireChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	soundFlamingChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	soundRandomChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);

	//	effects
	for(int i = 0; i < NUMBER_OF_EFFECT_TYPES; i ++){
		effectChoice->Insert(wxConvertMB2WX(wxGetApp().effectInfo[i].jname.c_str()), i);
		effectMeleeChoice->Insert(wxConvertMB2WX(wxGetApp().effectInfo[i].jname.c_str()), i);
		effectContrailChoice->Insert(wxConvertMB2WX(wxGetApp().effectInfo[i].jname.c_str()), i);
	}
	effectChoice->Insert(_T("NONE"), NUMBER_OF_EFFECT_TYPES);
	effectMeleeChoice->Insert(_T("NONE"), NUMBER_OF_EFFECT_TYPES);
	effectContrailChoice->Insert(_T("NONE"), NUMBER_OF_EFFECT_TYPES);

	//layout
	wxBoxSizer* baseSizer = new wxBoxSizer(wxHORIZONTAL);

	//	left column
	wxFlexGridSizer* infoSizer = new wxFlexGridSizer(17, 2, 0,0);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Collection")));
	infoSizer->Add(this->collectionChoice);
	infoSizer->Add(new wxStaticText(this, wxID_ANY, _T("Palette")));
	infoSizer->Add(this->paletteText,0,0,0,0);
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
	wxFlexGridSizer* soundAndEffectSizer = new wxFlexGridSizer(4, 1, 0,0);
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
	soundAndEffectSizer->Add(new wxStaticText(this, wxID_ANY, _T("Door Retry Mask")));
	soundAndEffectSizer->Add(doorRetryMaskText);
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
	int type = common();
	//
	int col = ev.GetSelection();
	int clut = getNumberFromTextCtrl(paletteText);
	monster_definitions[type].collection = BUILD_COLLECTION(col, clut);

}
void MonsterAppearancePanel::OnPalette(wxCommandEvent& ev)
{
	int type = common();
	//
	int col = collectionChoice->GetSelection();
	int clut = getNumberFromTextCtrl(&ev);
	monster_definitions[type].collection = BUILD_COLLECTION(col, clut);
}
void MonsterAppearancePanel::OnVitality(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].vitality = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnClass(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type]._class =
		wxGetApp().monsterClassBind[ev.GetSelection()].bind;

}
void MonsterAppearancePanel::OnRadius(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].radius = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnHeight(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].height= getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnHover(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].preferred_hover_height = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnMinLedge(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].minimum_ledge_delta = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnMaxLedge(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].maximum_ledge_delta = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnExtVelScale(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].external_velocity_scale = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnCarryItem(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].carrying_item_type =
		getChoice(carryItemChoice, NUMBER_OF_DEFINED_ITEMS);

}
void MonsterAppearancePanel::OnHalfVisualArc(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].half_visual_arc = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnVertVisualArc(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].half_vertical_visual_arc = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnIntelligence(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].intelligence = wxGetApp().monsterIntelligenceBind[
		getChoice(&ev, NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS)].bind;

}

void MonsterAppearancePanel::OnSpeedText(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].speed = getNumberFromTextCtrl(&ev);

	int oldIndex = this->speedChoice->GetSelection();
	int index = hpl::aleph::getIndexFromInformationBinded(
		monster_definitions[type].speed, wxGetApp().speedBind,
		NUMBER_OF_SPEED_INFORMATIONS);
	if(index < 0){
		index = NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS;
	}else{
	}
	if(index != oldIndex){
		this->speedChoice->SetSelection(index);
	}

}
void MonsterAppearancePanel::OnSpeedChoice(wxCommandEvent& ev)
{
	int type = common();
	int sel = ev.GetSelection();
	if(sel >= NUMBER_OF_SPEED_INFORMATIONS){
	}else{
		//monster_definitions[type].speed = getNumberFromTextCtrl(&ev);
		int prefferedNum = wxGetApp().speedBind[sel].bind;
		if(getNumberFromTextCtrl(this->speedText) != prefferedNum){
			this->speedText->SetValue(wx::string::getString("%d", prefferedNum));
		}
	}

}

void MonsterAppearancePanel::OnGravity(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].gravity = getNumberFromTextCtrl(&ev);

}

void MonsterAppearancePanel::OnStationaly(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].stationary_shape = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnMoving(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].moving_shape = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnHitting(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].hit_shapes = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnSoftDying(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].soft_dying_shape = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnSoftDead(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].soft_dead_shapes = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnHardDying(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].hard_dying_shape = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnHardDead(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].hard_dead_shapes = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnTeleportIn(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].teleport_in_shape = getNumberFromTextCtrl(&ev);

}
void MonsterAppearancePanel::OnTeleportOut(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].teleport_out_shape = getNumberFromTextCtrl(&ev);

}

void MonsterAppearancePanel::OnShrapnelRadius(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].shrapnel_radius = getNumberFromTextCtrl(&ev);
}
void MonsterAppearancePanel::OnShrapnelBase(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].shrapnel_damage.base = getNumberFromTextCtrl(&ev);
}
void MonsterAppearancePanel::OnShrapnelRnd(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].shrapnel_damage.random = getNumberFromTextCtrl(&ev);
}
void MonsterAppearancePanel::OnShrapnelScale(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].shrapnel_damage.scale = getNumberFromTextCtrl(&ev);
}
void MonsterAppearancePanel::OnShrapnelType(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].shrapnel_damage.type = getChoice(&ev, NUMBER_OF_DAMAGE_TYPES);
}
void MonsterAppearancePanel::OnShrapnelIsAlien(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].shrapnel_damage.flags = ev.IsChecked() ? 1: 0;
}

void MonsterAppearancePanel::OnCopyFrom(wxCommandEvent& ev)
{
	//TODO
	MonsterTypeSelectDialog* dlg = new MonsterTypeSelectDialog(this, wxID_ANY);
	if(dlg->ShowModal() == wxID_OK){
		int index = dlg->getIndex();
		//
		monster_definition* def = wxGetApp().getDefaultValues()->getMonsterDefinition(index);
		int type = wxGetApp().getEditingMonsterIndex();
		//アピアランス関連だけコピー
		monster_definitions[type].collection = def->collection;
		monster_definitions[type].vitality = def->vitality;
		monster_definitions[type]._class = def->_class;
		monster_definitions[type].radius = def->radius;
		monster_definitions[type].height = def->height;
		monster_definitions[type].preferred_hover_height = def->preferred_hover_height;
		monster_definitions[type].minimum_ledge_delta = def->minimum_ledge_delta;
		monster_definitions[type].maximum_ledge_delta = def->maximum_ledge_delta;
		monster_definitions[type].external_velocity_scale = def->external_velocity_scale;
		monster_definitions[type].carrying_item_type = def->carrying_item_type;
		monster_definitions[type].half_visual_arc = def->half_visual_arc;
		monster_definitions[type].half_vertical_visual_arc = def->half_vertical_visual_arc;
		monster_definitions[type].intelligence = def->intelligence;
		monster_definitions[type].speed = def->speed;
		monster_definitions[type].gravity = def->gravity;

		monster_definitions[type].stationary_shape = def->stationary_shape;
		monster_definitions[type].moving_shape = def->moving_shape;
		monster_definitions[type].hit_shapes = def->hit_shapes;
		monster_definitions[type].soft_dying_shape = def->soft_dying_shape;
		monster_definitions[type].soft_dead_shapes = def->soft_dead_shapes;
		monster_definitions[type].hard_dying_shape = def->hard_dying_shape;
		monster_definitions[type].hard_dead_shapes = def->hard_dead_shapes;
		monster_definitions[type].teleport_in_shape = def->teleport_in_shape;
		monster_definitions[type].teleport_out_shape = def->teleport_out_shape;

		monster_definitions[type].shrapnel_damage.type = def->shrapnel_damage.type;
		monster_definitions[type].shrapnel_damage.base = def->shrapnel_damage.base;
		monster_definitions[type].shrapnel_radius = def->shrapnel_radius;
		monster_definitions[type].shrapnel_damage.random = def->shrapnel_damage.random;
		monster_definitions[type].shrapnel_damage.scale = def->shrapnel_damage.scale;
		monster_definitions[type].shrapnel_damage.flags = def->shrapnel_damage.flags;

		monster_definitions[type].sound_pitch = def->sound_pitch;
		monster_definitions[type].activation_sound = def->activation_sound;
		monster_definitions[type].friendly_activation_sound = def->friendly_activation_sound;
		monster_definitions[type].clear_sound = def->clear_sound;
		monster_definitions[type].kill_sound = def->kill_sound;
		monster_definitions[type].apology_sound = def->apology_sound;
		monster_definitions[type].friendly_fire_sound = def->friendly_fire_sound;
		monster_definitions[type].flaming_sound = def->flaming_sound;
		monster_definitions[type].random_sound = def->random_sound;
		monster_definitions[type].random_sound_mask = def->random_sound_mask;

		monster_definitions[type].impact_effect = def->impact_effect;
		monster_definitions[type].melee_impact_effect = def->melee_impact_effect;
		monster_definitions[type].contrail_effect = def->contrail_effect;

		monster_definitions[type].door_retry_mask = def->door_retry_mask;
		/*		memcpy(&monster_definitions[wxGetApp().getEditingMonsterIndex()],
			wxGetApp().getDefaultValues()->getMonsterDefinition(index),
			sizeof(monster_definition));
			*/
		setup();
	}
}


void MonsterAppearancePanel::OnSoundPitch(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].sound_pitch = getNumberFromTextCtrl(&ev);
}
void MonsterAppearancePanel::OnSoundActivation(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].activation_sound = getChoice(&ev,
		NUMBER_OF_SOUND_DEFINITIONS);
}
void MonsterAppearancePanel::OnSoundFriendAct(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].friendly_activation_sound = getChoice(&ev,
		NUMBER_OF_SOUND_DEFINITIONS);
}
void MonsterAppearancePanel::OnSoundClear(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].clear_sound = getChoice(&ev,
		NUMBER_OF_SOUND_DEFINITIONS);
}
void MonsterAppearancePanel::OnSoundKill(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].kill_sound = getChoice(&ev,
		NUMBER_OF_SOUND_DEFINITIONS);
}
void MonsterAppearancePanel::OnSoundApology(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].apology_sound = getChoice(&ev,
		NUMBER_OF_SOUND_DEFINITIONS);
}
void MonsterAppearancePanel::OnSoundFriendFire(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].friendly_fire_sound = getChoice(&ev,
		NUMBER_OF_SOUND_DEFINITIONS);
}
void MonsterAppearancePanel::OnSoundFlaming(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].flaming_sound = getChoice(&ev,
		NUMBER_OF_SOUND_DEFINITIONS);
}
void MonsterAppearancePanel::OnSoundRandom(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].random_sound = getChoice(&ev,
		NUMBER_OF_SOUND_DEFINITIONS);
}
void MonsterAppearancePanel::OnSoundRandomMask(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].random_sound_mask = getNumberFromTextCtrl(&ev);
}

void MonsterAppearancePanel::OnEffect(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].impact_effect = getChoice(&ev,
		NUMBER_OF_EFFECT_TYPES);
}
void MonsterAppearancePanel::OnEffectMelee(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].melee_impact_effect = getChoice(&ev,
		NUMBER_OF_EFFECT_TYPES);
}
void MonsterAppearancePanel::OnEffectContrail(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].contrail_effect = getChoice(&ev,
		NUMBER_OF_EFFECT_TYPES);
}

void MonsterAppearancePanel::OnDoorRetryMask(wxCommandEvent& ev)
{
	int type = common();
	monster_definitions[type].door_retry_mask = getNumberFromTextCtrl(&ev);
}

void MonsterAppearancePanel::OnResetButton(wxCommandEvent& ev)
{
	int reply = wxMessageBox(_T("Are you sure to reset this monster?"),
		_T(""), wxCENTRE|wxOK|wxCANCEL);
	if(reply == wxOK){
		int type = wxGetApp().getEditingMonsterIndex();
		memcpy(&monster_definitions[type],
			wxGetApp().getDefaultValues()->getMonsterDefinition(type),
			sizeof(monster_definition));
		setup();
	}
}

int MonsterAppearancePanel::common()
{
	int type = wxGetApp().getEditingMonsterIndex();
	wxGetApp().setChanged(true);
	return type;
}

void MonsterAppearancePanel::setup()
{
	int type = wxGetApp().getEditingMonsterIndex();

	int collection = GET_COLLECTION(monster_definitions[type].collection);
	int clut = GET_COLLECTION_CLUT(monster_definitions[type].collection);

	collectionChoice->SetSelection(collection);
	paletteText->SetValue(wx::string::getString("%d", clut));
	vitalityText->SetValue(wx::string::getString("%d", monster_definitions[type].vitality));
	int cls = hpl::aleph::getIndexFromInformationBinded(monster_definitions[type]._class,
		wxGetApp().monsterClassBind, NUMBER_OF_CLASS_INFORMATIONS);
	classChoice->SetSelection(cls);
	radiusText->SetValue(wx::string::getString("%d", monster_definitions[type].radius));
	heightText->SetValue(wx::string::getString("%d", monster_definitions[type].height));
	hoverText->SetValue(wx::string::getString("%d", monster_definitions[type].preferred_hover_height));
	minLedgeText->SetValue(wx::string::getString("%d", monster_definitions[type].minimum_ledge_delta));
	maxLedgeText->SetValue(wx::string::getString("%d", monster_definitions[type].maximum_ledge_delta));
	extVelScaleText->SetValue(wx::string::getString("%d", monster_definitions[type].external_velocity_scale));
	setChoice(carryItemChoice, monster_definitions[type].carrying_item_type, NUMBER_OF_DEFINED_ITEMS);
	halfVisualArcText->SetValue(wx::string::getString("%d",
		monster_definitions[type].half_visual_arc));
	vertVisualArcText->SetValue(wx::string::getString("%d",
		monster_definitions[type].half_vertical_visual_arc));
	intelligenceChoice->SetSelection(hpl::aleph::getIndexFromInformationBinded(monster_definitions[type].intelligence, 
		wxGetApp().monsterIntelligenceBind, NUMBER_OF_MONSTER_INTELLIGENCE_INFORMATIONS));
	speedText->SetValue(wx::string::getString("%d", monster_definitions[type].speed));
	int index = hpl::aleph::getIndexFromInformationBinded(monster_definitions[type].speed, 
		wxGetApp().speedBind, NUMBER_OF_SPEED_INFORMATIONS);
	if(index < 0){
		index = NUMBER_OF_SPEED_INFORMATIONS;
	}
	speedChoice->SetSelection(index);
	gravityText->SetValue(wx::string::getString("%d", monster_definitions[type].gravity));

	//sequences
	stationalyText->SetValue(wx::string::getString("%d", monster_definitions[type].stationary_shape));
	movingText->SetValue(wx::string::getString("%d", monster_definitions[type].moving_shape));
	hittingText->SetValue(wx::string::getString("%d", monster_definitions[type].hit_shapes));
	softDyingText->SetValue(wx::string::getString("%d", monster_definitions[type].soft_dying_shape));
	softDeadText->SetValue(wx::string::getString("%d", monster_definitions[type].soft_dead_shapes));
	hardDyingText->SetValue(wx::string::getString("%d", monster_definitions[type].hard_dying_shape));
	hardDeadText->SetValue(wx::string::getString("%d", monster_definitions[type].hard_dead_shapes));
	teleportInText->SetValue(wx::string::getString("%d", monster_definitions[type].teleport_in_shape));
	teleportOutText->SetValue(wx::string::getString("%d", monster_definitions[type].teleport_out_shape));

	//shrapnel
	setChoice(shrapnelTypeChoice, monster_definitions[type].shrapnel_damage.type,
		NUMBER_OF_DAMAGE_TYPES);
	shrapnelBaseText->SetValue(wx::string::getString("%d", monster_definitions[type].shrapnel_damage.base));
	shrapnelRadiusText->SetValue(wx::string::getString("%d", monster_definitions[type].shrapnel_radius));
	shrapnelRndText->SetValue(wx::string::getString("%d", monster_definitions[type].shrapnel_damage.random));
	shrapnelScaleText->SetValue(wx::string::getString("%d", monster_definitions[type].shrapnel_damage.scale));
	shrapnelIsAlienCheckbox->SetValue(monster_definitions[type].shrapnel_damage.flags != 0);

	//sound
	soundPitchText->SetValue(wx::string::getString("%d", monster_definitions[type].sound_pitch));
	setChoice(soundActivationChoice, monster_definitions[type].activation_sound, NUMBER_OF_SOUND_DEFINITIONS);
	setChoice(soundFriendActChoice, monster_definitions[type].friendly_activation_sound, NUMBER_OF_SOUND_DEFINITIONS);
	setChoice(soundClearChoice, monster_definitions[type].clear_sound, NUMBER_OF_SOUND_DEFINITIONS);
	setChoice(soundKillChoice, monster_definitions[type].kill_sound, NUMBER_OF_SOUND_DEFINITIONS);
	setChoice(soundApologyChoice, monster_definitions[type].apology_sound, NUMBER_OF_SOUND_DEFINITIONS);
	setChoice(soundFriendFireChoice, monster_definitions[type].friendly_fire_sound, NUMBER_OF_SOUND_DEFINITIONS);
	setChoice(soundFlamingChoice, monster_definitions[type].flaming_sound, NUMBER_OF_SOUND_DEFINITIONS);
	setChoice(soundRandomChoice, monster_definitions[type].random_sound, NUMBER_OF_SOUND_DEFINITIONS);
	soundRandomMask->SetValue(wx::string::getString("%d", monster_definitions[type].random_sound_mask));

	//effect
	setChoice(effectChoice, monster_definitions[type].impact_effect, NUMBER_OF_EFFECT_TYPES);
	setChoice(effectMeleeChoice, monster_definitions[type].melee_impact_effect, NUMBER_OF_EFFECT_TYPES);
	setChoice(effectContrailChoice, monster_definitions[type].contrail_effect, NUMBER_OF_EFFECT_TYPES);

	doorRetryMaskText->SetValue(wx::string::getString("%d", monster_definitions[type].door_retry_mask));
}

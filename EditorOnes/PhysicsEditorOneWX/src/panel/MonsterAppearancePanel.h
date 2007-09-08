#ifndef _MONSTER_APPEARANCE_PANEL_
#define _MONSTER_APPEARANCE_PANEL_

#include "../Common.h"

/**
	MonsterのAppearance（見た目、音、シーケンス、体力等）
	に関するデータを操作するパネル
*/
class MonsterAppearancePanel: public wxPanel{
private:
	wxChoice* collectionChoice;
	wxTextCtrl* paletteText;
	wxTextCtrl* vitalityText;
	wxChoice* classChoice;
	wxTextCtrl* radiusText;
	wxTextCtrl* heightText;
	wxTextCtrl* hoverText;
	wxTextCtrl* minLedgeText;
	wxTextCtrl* maxLedgeText;
	wxTextCtrl* extVelScaleText;
	wxChoice* carryItemChoice;
	wxTextCtrl* halfVisualArcText;
	wxTextCtrl* vertVisualArcText;
	wxChoice* intelligenceChoice;
	wxTextCtrl* speedText;
	wxChoice* speedChoice;
	wxTextCtrl* gravityText;

	//シーケンス
	wxTextCtrl* stationalyText;
	wxTextCtrl* movingText;
	wxTextCtrl* hittingText;
	wxTextCtrl* softDyingText;
	wxTextCtrl* softDeadText;
	wxTextCtrl* hardDyingText;
	wxTextCtrl* hardDeadText;
	wxTextCtrl* teleportInText;
	wxTextCtrl* teleportOutText;

	//shrapnel自爆ダメージ
	wxTextCtrl* shrapnelRadiusText;
	wxTextCtrl* shrapnelBaseText;
	wxTextCtrl* shrapnelRndText;
	wxTextCtrl* shrapnelScaleText;
	wxChoice* shrapnelTypeChoice;
	wxCheckBox* shrapnelIsAlienCheckbox;

	//copy from
	wxButton* copyFromButton;

	//sound
	wxTextCtrl* soundPitchText;
	wxChoice* soundActivationChoice;
	wxChoice* soundFriendActChoice;
	wxChoice* soundClearChoice;
	wxChoice* soundKillChoice;
	wxChoice* soundApologyChoice;
	wxChoice* soundFriendFireChoice;
	wxChoice* soundFlamingChoice;
	wxChoice* soundRandomChoice;
	wxTextCtrl* soundRandomMask;

	//effect
	wxChoice* effectChoice;
	wxChoice* effectMeleeChoice;
	wxChoice* effectContrailChoice;

	//TODO  door retry mask
	wxTextCtrl* doorRetryMaskText;

	//button
	wxButton* resetButton;

	MonsterAppearancePanel(){}
public:
	MonsterAppearancePanel(wxWindow* parent, wxWindowID id);
	virtual ~MonsterAppearancePanel();
protected:
    DECLARE_EVENT_TABLE()
	
	void OnCollection(wxCommandEvent& ev);
	void OnPalette(wxCommandEvent& ev);
	void OnVitality(wxCommandEvent& ev);
	void OnClass(wxCommandEvent& ev);
	void OnRadius(wxCommandEvent& ev);
	void OnHeight(wxCommandEvent& ev);
	void OnHover(wxCommandEvent& ev);
	void OnMinLedge(wxCommandEvent& ev);
	void OnMaxLedge(wxCommandEvent& ev);
	void OnExtVelScale(wxCommandEvent& ev);
	void OnCarryItem(wxCommandEvent& ev);
	void OnHalfVisualArc(wxCommandEvent& ev);
	void OnVertVisualArc(wxCommandEvent& ev);
	void OnIntelligence(wxCommandEvent& ev);
	
	void OnSpeedText(wxCommandEvent& ev);
	void OnSpeedChoice(wxCommandEvent& ev);
	
	void OnGravity(wxCommandEvent& ev);

	void OnStationaly(wxCommandEvent& ev);
	void OnMoving(wxCommandEvent& ev);
	void OnHitting(wxCommandEvent& ev);
	void OnSoftDying(wxCommandEvent& ev);
	void OnSoftDead(wxCommandEvent& ev);
	void OnHardDying(wxCommandEvent& ev);
	void OnHardDead(wxCommandEvent& ev);
	void OnTeleportIn(wxCommandEvent& ev);
	void OnTeleportOut(wxCommandEvent& ev);

	void OnShrapnelRadius(wxCommandEvent& ev);
	void OnShrapnelBase(wxCommandEvent& ev);
	void OnShrapnelRnd(wxCommandEvent& ev);
	void OnShrapnelScale(wxCommandEvent& ev);
	void OnShrapnelType(wxCommandEvent& ev);
	void OnShrapnelIsAlien(wxCommandEvent& ev);
	
	void OnCopyFrom(wxCommandEvent& ev);

	void OnSoundPitch(wxCommandEvent& ev);
	void OnSoundActivation(wxCommandEvent& ev);
	void OnSoundFriendAct(wxCommandEvent& ev);
	void OnSoundClear(wxCommandEvent& ev);
	void OnSoundKill(wxCommandEvent& ev);
	void OnSoundApology(wxCommandEvent& ev);
	void OnSoundFriendFire(wxCommandEvent& ev);
	void OnSoundFlaming(wxCommandEvent& ev);
	void OnSoundRandom(wxCommandEvent& ev);
	void OnSoundRandomMask(wxCommandEvent& ev);

	void OnEffect(wxCommandEvent& ev);
	void OnEffectMelee(wxCommandEvent& ev);
	void OnEffectContrail(wxCommandEvent& ev);

	void OnDoorRetryMask(wxCommandEvent& ev);

	void OnResetButton(wxCommandEvent& ev);
	int common();
public:
	void setup();
};


#endif

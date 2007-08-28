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

	//button
	wxButton* resetButton;

	MonsterAppearancePanel(){}
public:
	MonsterAppearancePanel(wxWindow* parent, wxWindowID id);
	virtual ~MonsterAppearancePanel();
};


#endif

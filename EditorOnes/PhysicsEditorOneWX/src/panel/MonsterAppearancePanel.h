#ifndef _MONSTER_APPEARANCE_PANEL_
#define _MONSTER_APPEARANCE_PANEL_

#include "../Common.h"

/**
	Monster��Appearance�i�����ځA���A�V�[�P���X�A�̗͓��j
	�Ɋւ���f�[�^�𑀍삷��p�l��
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

	//�V�[�P���X
	wxTextCtrl* stationalyText;
	wxTextCtrl* movingText;
	wxTextCtrl* hittingText;
	wxTextCtrl* softDyingText;
	wxTextCtrl* softDeadText;
	wxTextCtrl* hardDyingText;
	wxTextCtrl* hardDeadText;
	wxTextCtrl* teleportInText;
	wxTextCtrl* teleportOutText;

	//shrapnel�����_���[�W
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

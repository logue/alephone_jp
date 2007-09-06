#ifndef _WEAPON_APPEARANCE_PANEL_
#define _WEAPON_APPEARANCE_PANEL_

#include "../Common.h"

class WeaponAppearancePanel: public wxPanel{
private:
	wxChoice* collectionChoice;
	wxTextCtrl* paletteText;
	wxTextCtrl* idleSeqText;
	wxTextCtrl* firingSeqText;
	wxTextCtrl* reloadSeqText;
	wxTextCtrl* chargingSeqText;
	wxTextCtrl* chargedSeqText;
	wxChoice* itemChoice;
	wxChoice* classChoice;
	wxTextCtrl* lightIntensityText;
	wxTextCtrl* intensityDecayText;
	wxTextCtrl* idleWidthText;
	wxTextCtrl* idleHeightText;
	wxTextCtrl* firingHeightText;
	wxTextCtrl* reloadHeightText;
	wxTextCtrl* horizontalAmplitudeText;
	wxTextCtrl* userAmplitudeText;
	wxTextCtrl* readyTicksText;
	wxTextCtrl* awaitReloadTicksText;
	wxTextCtrl* loadingTicksText;
	wxTextCtrl* loadedTicksText;

	wxCheckBox* flags[NUMBER_OF_WEAPON_FLAG_INFORMATIONS];
private:
	WeaponAppearancePanel(){}
public:
	WeaponAppearancePanel(wxWindow* parent, wxWindowID id);
	virtual ~WeaponAppearancePanel();
    DECLARE_EVENT_TABLE()
public:
	void setup();
};


#endif

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
	void OnCollection(wxCommandEvent& ev);
	void OnPalette(wxCommandEvent& ev);
	void OnIdleSeq(wxCommandEvent& ev);
	void OnFiringSeq(wxCommandEvent& ev);
	void OnReloadSeq(wxCommandEvent& ev);
	void OnChargingSeq(wxCommandEvent& ev);
	void OnChargedSeq(wxCommandEvent& ev);
	void OnItem(wxCommandEvent& ev);
	void OnClass(wxCommandEvent& ev);
	void OnLightIntensity(wxCommandEvent& ev);
	void OnIntensityDecay(wxCommandEvent& ev);
	void OnIdleWidth(wxCommandEvent& ev);
	void OnIdleHeight(wxCommandEvent& ev);
	void OnFiringHeight(wxCommandEvent& ev);
	void OnReloadingHeight(wxCommandEvent& ev);
	void OnHorizontalAmplitude(wxCommandEvent& ev);
	void OnUserAmplitude(wxCommandEvent& ev);
	void OnReadyTicks(wxCommandEvent& ev);
	void OnAwaitReloadTicks(wxCommandEvent& ev);
	void OnLoadingTicks(wxCommandEvent& ev);
	void OnLoadedTicks(wxCommandEvent& ev);

	void OnFlags(wxCommandEvent& ev);
	int common();
public:
	void setup();
};


#endif

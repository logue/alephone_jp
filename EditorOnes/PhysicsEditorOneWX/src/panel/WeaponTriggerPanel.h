#ifndef _WEAPON_TRIGGER_PANEL_
#define _WEAPON_TRIGGER_PANEL_

#include "../Common.h"

typedef struct WeaponSet_tag{
	wxTextCtrl* roundPerMagazineText;
	wxChoice* ammoItemChoice;
	wxTextCtrl* ticksPerRoundText;
	wxTextCtrl* recoveryTicksText;
	wxTextCtrl* chargingTicksText;
	wxTextCtrl* recoilText;
	wxChoice* firingSoundChoice;
	wxChoice* clickSoundChoice;
	wxChoice* chargingSoundChoice;
	wxChoice* shellSoundChoice;
	wxChoice* reloadSoundChoice;
	wxChoice* chargedSoundChoice;
	wxChoice* projectileChoice;
	wxTextCtrl* errorText;
	wxTextCtrl* dxText;
	wxTextCtrl* dzText;
	wxChoice* shellCasingChoice;
	wxTextCtrl* burstCountText;
}WeaponSet;

class WeaponTriggerPanel: public wxPanel{
private:
	WeaponSet primary;
	WeaponSet secondary;
private:
	WeaponTriggerPanel(){}
public:
	WeaponTriggerPanel(wxWindow* parent, wxWindowID id);
	virtual ~WeaponTriggerPanel();
    DECLARE_EVENT_TABLE()
	void OnPrimaryRoundPerMagazine(wxCommandEvent& ev);
	void OnPrimaryAmmoItem(wxCommandEvent& ev);
	void OnPrimaryTicksPerRound(wxCommandEvent& ev);
	void OnPrimaryRecoveryTicks(wxCommandEvent& ev);
	void OnPrimaryChargingTicks(wxCommandEvent& ev);
	void OnPrimaryRecoil(wxCommandEvent& ev);
	void OnPrimaryFiringSound(wxCommandEvent& ev);
	void OnPrimaryClickSound(wxCommandEvent& ev);
	void OnPrimaryChargingSound(wxCommandEvent& ev);
	void OnPrimaryShellCasingSound(wxCommandEvent& ev);
	void OnPrimaryReloadSound(wxCommandEvent& ev);
	void OnPrimaryChargedSound(wxCommandEvent& ev);
	void OnPrimaryProjectile(wxCommandEvent& ev);
	void OnPrimaryError(wxCommandEvent& ev);
	void OnPrimaryDX(wxCommandEvent& ev);
	void OnPrimaryDZ(wxCommandEvent& ev);
	void OnPrimaryShellCasing(wxCommandEvent& ev);
	void OnPrimaryBurstCount(wxCommandEvent& ev);

	void OnSecondaryRoundPerMagazine(wxCommandEvent& ev);
	void OnSecondaryAmmoItem(wxCommandEvent& ev);
	void OnSecondaryTicksPerRound(wxCommandEvent& ev);
	void OnSecondaryRecoveryTicks(wxCommandEvent& ev);
	void OnSecondaryChargingTicks(wxCommandEvent& ev);
	void OnSecondaryRecoil(wxCommandEvent& ev);
	void OnSecondaryFiringSound(wxCommandEvent& ev);
	void OnSecondaryClickSound(wxCommandEvent& ev);
	void OnSecondaryChargingSound(wxCommandEvent& ev);
	void OnSecondaryShellCasingSound(wxCommandEvent& ev);
	void OnSecondaryReloadSound(wxCommandEvent& ev);
	void OnSecondaryChargedSound(wxCommandEvent& ev);
	void OnSecondaryProjectile(wxCommandEvent& ev);
	void OnSecondaryError(wxCommandEvent& ev);
	void OnSecondaryDX(wxCommandEvent& ev);
	void OnSecondaryDZ(wxCommandEvent& ev);
	void OnSecondaryShellCasing(wxCommandEvent& ev);
	void OnSecondaryBurstCount(wxCommandEvent& ev);
	int common();
	wxStaticBoxSizer* getTriggerSizer(WeaponSet& trigger, wxString title);

public:
	void setup();
};


#endif

#include "WeaponTriggerPanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_PRIMARY_ROUND_PER_MAGAZINE,
	ID_PRIMARY_AMMO_ITEM,
	ID_PRIMARY_TICKS_PER_ROUND,
	ID_PRIMARY_RECOVERY_TICKS,
	ID_PRIMARY_CHARGING_TICKS,
	ID_PRIMARY_RECOIL,
	ID_PRIMARY_FIRING_SOUND,
	ID_PRIMARY_CLICK_SOUND,
	ID_PRIMARY_CHARGING_SOUND,
	ID_PRIMARY_SHELL_CASING_SOUND,
	ID_PRIMARY_RELOAD_SOUND,
	ID_PRIMARY_CHARGED_SOUND,
	ID_PRIMARY_PROJECTILE,
	ID_PRIMARY_ERROR,
	ID_PRIMARY_DX,
	ID_PRIMARY_DZ,
	ID_PRIMARY_SHELL_CASING,
	ID_PRIMARY_BURST_COUNT,

	ID_SECONDARY_ROUND_PER_MAGAZINE,
	ID_SECONDARY_AMMO_ITEM,
	ID_SECONDARY_TICKS_PER_ROUND,
	ID_SECONDARY_RECOVERY_TICKS,
	ID_SECONDARY_CHARGING_TICKS,
	ID_SECONDARY_RECOIL,
	ID_SECONDARY_FIRING_SOUND,
	ID_SECONDARY_CLICK_SOUND,
	ID_SECONDARY_CHARGING_SOUND,
	ID_SECONDARY_SHELL_CASING_SOUND,
	ID_SECONDARY_RELOAD_SOUND,
	ID_SECONDARY_CHARGED_SOUND,
	ID_SECONDARY_PROJECTILE,
	ID_SECONDARY_ERROR,
	ID_SECONDARY_DX,
	ID_SECONDARY_DZ,
	ID_SECONDARY_SHELL_CASING,
	ID_SECONDARY_BURST_COUNT,

};

BEGIN_EVENT_TABLE(WeaponTriggerPanel, wxPanel)
	EVT_TEXT(ID_PRIMARY_ROUND_PER_MAGAZINE, WeaponTriggerPanel::OnPrimaryRoundPerMagazine)
	EVT_CHOICE(ID_PRIMARY_AMMO_ITEM, WeaponTriggerPanel::OnPrimaryAmmoItem)
	EVT_TEXT(ID_PRIMARY_TICKS_PER_ROUND, WeaponTriggerPanel::OnPrimaryTicksPerRound)
	EVT_TEXT(ID_PRIMARY_RECOVERY_TICKS, WeaponTriggerPanel::OnPrimaryRecoveryTicks)
	EVT_TEXT(ID_PRIMARY_CHARGING_TICKS, WeaponTriggerPanel::OnPrimaryChargingTicks)
	EVT_TEXT(ID_PRIMARY_RECOIL, WeaponTriggerPanel::OnPrimaryRecoil)
	EVT_CHOICE(ID_PRIMARY_FIRING_SOUND, WeaponTriggerPanel::OnPrimaryFiringSound)
	EVT_CHOICE(ID_PRIMARY_CLICK_SOUND, WeaponTriggerPanel::OnPrimaryClickSound)
	EVT_CHOICE(ID_PRIMARY_CHARGING_SOUND, WeaponTriggerPanel::OnPrimaryChargingSound)
	EVT_CHOICE(ID_PRIMARY_SHELL_CASING_SOUND, WeaponTriggerPanel::OnPrimaryShellCasingSound)
	EVT_CHOICE(ID_PRIMARY_RELOAD_SOUND, WeaponTriggerPanel::OnPrimaryReloadSound)
	EVT_CHOICE(ID_PRIMARY_CHARGED_SOUND, WeaponTriggerPanel::OnPrimaryChargedSound)
	EVT_CHOICE(ID_PRIMARY_PROJECTILE, WeaponTriggerPanel::OnPrimaryProjectile)
	EVT_TEXT(ID_PRIMARY_ERROR, WeaponTriggerPanel::OnPrimaryError)
	EVT_TEXT(ID_PRIMARY_DX, WeaponTriggerPanel::OnPrimaryDX)
	EVT_TEXT(ID_PRIMARY_DZ, WeaponTriggerPanel::OnPrimaryDZ)
	EVT_CHOICE(ID_PRIMARY_SHELL_CASING, WeaponTriggerPanel::OnPrimaryShellCasing)
	EVT_TEXT(ID_PRIMARY_BURST_COUNT, WeaponTriggerPanel::OnPrimaryBurstCount)

	EVT_TEXT(ID_SECONDARY_ROUND_PER_MAGAZINE, WeaponTriggerPanel::OnSecondaryRoundPerMagazine)
	EVT_CHOICE(ID_SECONDARY_AMMO_ITEM, WeaponTriggerPanel::OnSecondaryAmmoItem)
	EVT_TEXT(ID_SECONDARY_TICKS_PER_ROUND, WeaponTriggerPanel::OnSecondaryTicksPerRound)
	EVT_TEXT(ID_SECONDARY_RECOVERY_TICKS, WeaponTriggerPanel::OnSecondaryRecoveryTicks)
	EVT_TEXT(ID_SECONDARY_CHARGING_TICKS, WeaponTriggerPanel::OnSecondaryChargingTicks)
	EVT_TEXT(ID_SECONDARY_RECOIL, WeaponTriggerPanel::OnSecondaryRecoil)
	EVT_CHOICE(ID_SECONDARY_FIRING_SOUND, WeaponTriggerPanel::OnSecondaryFiringSound)
	EVT_CHOICE(ID_SECONDARY_CLICK_SOUND, WeaponTriggerPanel::OnSecondaryClickSound)
	EVT_CHOICE(ID_SECONDARY_CHARGING_SOUND, WeaponTriggerPanel::OnSecondaryChargingSound)
	EVT_CHOICE(ID_SECONDARY_SHELL_CASING_SOUND, WeaponTriggerPanel::OnSecondaryShellCasingSound)
	EVT_CHOICE(ID_SECONDARY_RELOAD_SOUND, WeaponTriggerPanel::OnSecondaryReloadSound)
	EVT_CHOICE(ID_SECONDARY_CHARGED_SOUND, WeaponTriggerPanel::OnSecondaryChargedSound)
	EVT_CHOICE(ID_SECONDARY_PROJECTILE, WeaponTriggerPanel::OnSecondaryProjectile)
	EVT_TEXT(ID_SECONDARY_ERROR, WeaponTriggerPanel::OnSecondaryError)
	EVT_TEXT(ID_SECONDARY_DX, WeaponTriggerPanel::OnSecondaryDX)
	EVT_TEXT(ID_SECONDARY_DZ, WeaponTriggerPanel::OnSecondaryDZ)
	EVT_CHOICE(ID_SECONDARY_SHELL_CASING, WeaponTriggerPanel::OnSecondaryShellCasing)
	EVT_TEXT(ID_SECONDARY_BURST_COUNT, WeaponTriggerPanel::OnSecondaryBurstCount)
END_EVENT_TABLE()

WeaponTriggerPanel::WeaponTriggerPanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	//create
	this->primary.roundPerMagazineText = new wxTextCtrl(this, ID_PRIMARY_ROUND_PER_MAGAZINE);
	this->primary.ammoItemChoice = new wxChoice(this, ID_PRIMARY_AMMO_ITEM);
	this->primary.ticksPerRoundText = new wxTextCtrl(this, ID_PRIMARY_TICKS_PER_ROUND);
	this->primary.recoveryTicksText = new wxTextCtrl(this, ID_PRIMARY_RECOVERY_TICKS);
	this->primary.chargingTicksText = new wxTextCtrl(this, ID_PRIMARY_CHARGING_TICKS);
	this->primary.recoilText= new wxTextCtrl(this, ID_PRIMARY_RECOIL);
	this->primary.firingSoundChoice = new wxChoice(this, ID_PRIMARY_FIRING_SOUND);
	this->primary.clickSoundChoice = new wxChoice(this, ID_PRIMARY_CLICK_SOUND);
	this->primary.chargingSoundChoice = new wxChoice(this, ID_PRIMARY_CHARGING_SOUND);
	this->primary.shellSoundChoice = new wxChoice(this, ID_PRIMARY_SHELL_CASING_SOUND);
	this->primary.reloadSoundChoice = new wxChoice(this, ID_PRIMARY_RELOAD_SOUND);
	this->primary.chargedSoundChoice = new wxChoice(this, ID_PRIMARY_CHARGED_SOUND);
	this->primary.projectileChoice = new wxChoice(this, ID_PRIMARY_PROJECTILE);
	this->primary.errorText = new wxTextCtrl(this, ID_PRIMARY_ERROR);
	this->primary.dxText = new wxTextCtrl(this, ID_PRIMARY_DX);
	this->primary.dzText= new wxTextCtrl(this, ID_PRIMARY_DZ);
	this->primary.shellCasingChoice = new wxChoice(this, ID_PRIMARY_SHELL_CASING);
	this->primary.burstCountText = new wxTextCtrl(this, ID_PRIMARY_BURST_COUNT);

	this->secondary.roundPerMagazineText = new wxTextCtrl(this, ID_SECONDARY_ROUND_PER_MAGAZINE);
	this->secondary.ammoItemChoice = new wxChoice(this, ID_SECONDARY_AMMO_ITEM);
	this->secondary.ticksPerRoundText = new wxTextCtrl(this, ID_SECONDARY_TICKS_PER_ROUND);
	this->secondary.recoveryTicksText = new wxTextCtrl(this, ID_SECONDARY_RECOVERY_TICKS);
	this->secondary.chargingTicksText = new wxTextCtrl(this, ID_SECONDARY_CHARGING_TICKS);
	this->secondary.recoilText= new wxTextCtrl(this, ID_SECONDARY_RECOIL);
	this->secondary.firingSoundChoice = new wxChoice(this, ID_SECONDARY_FIRING_SOUND);
	this->secondary.clickSoundChoice = new wxChoice(this, ID_SECONDARY_CLICK_SOUND);
	this->secondary.chargingSoundChoice = new wxChoice(this, ID_SECONDARY_CHARGING_SOUND);
	this->secondary.shellSoundChoice = new wxChoice(this, ID_SECONDARY_SHELL_CASING_SOUND);
	this->secondary.reloadSoundChoice = new wxChoice(this, ID_SECONDARY_RELOAD_SOUND);
	this->secondary.chargedSoundChoice = new wxChoice(this, ID_SECONDARY_CHARGED_SOUND);
	this->secondary.projectileChoice = new wxChoice(this, ID_SECONDARY_PROJECTILE);
	this->secondary.errorText = new wxTextCtrl(this, ID_SECONDARY_ERROR);
	this->secondary.dxText = new wxTextCtrl(this, ID_SECONDARY_DX);
	this->secondary.dzText= new wxTextCtrl(this, ID_SECONDARY_DZ);
	this->secondary.shellCasingChoice = new wxChoice(this, ID_SECONDARY_SHELL_CASING);
	this->secondary.burstCountText = new wxTextCtrl(this, ID_SECONDARY_BURST_COUNT);

	//set
	for(int i = 0; i < NUMBER_OF_DEFINED_ITEMS; i ++){
		this->primary.ammoItemChoice->Insert(wxConvertMB2WX(
			wxGetApp().weaponInfo[i].jname.c_str()), i);
		this->secondary.ammoItemChoice->Insert(wxConvertMB2WX(
			wxGetApp().weaponInfo[i].jname.c_str()), i);
	}
	this->primary.ammoItemChoice->Insert(_T("NONE"), NUMBER_OF_DEFINED_ITEMS);
	this->secondary.ammoItemChoice->Insert(_T("NONE"), NUMBER_OF_DEFINED_ITEMS);

	//	sounds
	for(int i = 0; i < NUMBER_OF_SOUND_DEFINITIONS; i ++){
		this->primary.firingSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->primary.clickSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->primary.chargingSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->primary.shellSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->primary.reloadSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->primary.chargedSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);

		this->secondary.firingSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->secondary.clickSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->secondary.chargingSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->secondary.shellSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->secondary.reloadSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
		this->secondary.chargedSoundChoice->Insert(wxConvertMB2WX(
			wxGetApp().soundInfo[i].jname.c_str()), i);
	}
	this->primary.firingSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->primary.clickSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->primary.chargingSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->primary.shellSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->primary.reloadSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->primary.chargedSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->secondary.firingSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->secondary.clickSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->secondary.chargingSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->secondary.shellSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->secondary.reloadSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);
	this->secondary.chargedSoundChoice->Insert(_T("NONE"), NUMBER_OF_SOUND_DEFINITIONS);

	//	projectile
	for(int i = 0; i < NUMBER_OF_PROJECTILE_TYPES; i ++){
		this->primary.projectileChoice->Insert(wxConvertMB2WX(
			wxGetApp().projectileInfo[i].jname.c_str()), i);
		this->secondary.projectileChoice->Insert(wxConvertMB2WX(
			wxGetApp().projectileInfo[i].jname.c_str()), i);
	}
	this->primary.projectileChoice->Insert(_T("NONE"), NUMBER_OF_PROJECTILE_TYPES);
	this->secondary.projectileChoice->Insert(_T("NONE"), NUMBER_OF_PROJECTILE_TYPES);

	//layout
	wxFlexGridSizer* allSizer = new wxFlexGridSizer(1,2,0,0);
	this->SetSizer(allSizer);
	//	primary
	wxStaticBoxSizer* primarySizer = getTriggerSizer(this->primary);

	allSizer->Fit(this);
	Layout();
}

WeaponTriggerPanel::~WeaponTriggerPanel()
{
}

void WeaponTriggerPanel::OnPrimaryRoundPerMagazine(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].rounds_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryAmmoItem(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].ammunition_type =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryTicksPerRound(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].ticks_per_round =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryRecoveryTicks(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].recovery_ticks =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryChargingTicks(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].charging_ticks =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryRecoil(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryFiringSound(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0]. =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryClickSound(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryChargingSound(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryShellCasingSound(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryReloadSound(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryChargedSound(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryProjectile(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryError(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryDX(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryDZ(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryShellCasing(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}
void WeaponTriggerPanel::OnPrimaryBurstCount(wxCommandEvent& ev)
{
	int type = common();
	weapon_definitions[type].weapons_by_trigger[0].round_per_magazine =
		getNumberFromTextCtrl(&ev);
}


int WeaponTriggerPanel::common()
{
	int type = wxGetApp().getEditingWeaponIndex();
	wxGetApp().setNewAndChanged(false, true);
	return type;
}
void WeaponTriggerPanel::setup()
{
}

wxStaticBoxSizer* WeaponTriggerPanel::getTriggerSizer(WeaponTrigger& trigger,
													  wxString title)
{
	wxStaticBox* box = new wxStaticBox(this, wxID_ANY, title);
	wxStaticBoxSizer* sizer = new wxStaticBoxSizer(box, wxVERTICAL);
	wxFlexGridSizer* flexSizer = new wxFlexGridSizer(18,2,0,0);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Round Per Magazine")));
	flexSizer->Add(trigger.roundPerMagazineText);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Ammo Item")));
	flexSizer->Add(trigger.ammoItemChoice);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Ticks Per Round")));
	flexSizer->Add(trigger.ticksPerRoundText);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Recovery Ticks")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Charging Ticks")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Recoil")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Firing Sound")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Click Sound")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Charging Sound")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("Shell Casing Sound")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("")));
	flexSizer->Add(trigger.);
	flexSizer->Add(new wxStaticText(this, wxID_ANY,
		_T("")));
	flexSizer->Add(trigger.);
}

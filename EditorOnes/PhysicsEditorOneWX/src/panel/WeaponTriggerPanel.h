#ifndef _WEAPON_TRIGGER_PANEL_
#define _WEAPON_TRIGGER_PANEL_

#include "../Common.h"

typedef struct WeaponSet_tag{
	wxTextCtrl* roundPerMagazineText;
	wxChoice* ammoItemChoice;
	wxTextCtrl* Text;
	wxTextCtrl* Text;
	wxTextCtrl* Text;
	wxTextCtrl* Text;
	wxChoice* SoundChoice;
	wxChoice* SoundChoice;
	wxChoice* SoundChoice;
	wxChoice* SoundChoice;
	wxChoice* SoundChoice;
	wxChoice* SoundChoice;
	wxChoice* projectileChoice;
	wxTextCtrl* errorText;
	wxTextCtrl* dxText;
	wxTextCtrl* dzText;
	wxChoice* shellCasingChoice;
	wxTextCtrl* burstCountText;
}WeaponSet;

class WeaponTriggerPanel: public wxPanel{
private:

private:
	WeaponTriggerPanel(){}
public:
	WeaponTriggerPanel(wxWindow* parent, wxWindowID id);
	virtual ~WeaponTriggerPanel();
    DECLARE_EVENT_TABLE()
public:
	void setup();
};


#endif

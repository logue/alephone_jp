#ifndef _WEAPON_PANEL_
#define _WEAPON_PANEL_

#include "../Common.h"
#include "WeaponAppearancePanel.h"
#include "WeaponTriggerPanel.h"

class WeaponPanel: public wxPanel{
private:
	wxListBox* typeListBox;
	wxNotebook* notebook;
	WeaponAppearancePanel* appearancePanel;
	WeaponTriggerPanel* triggerPanel;

private:
	WeaponPanel(){}
public:
	WeaponPanel(wxWindow* parent, wxWindowID id);
	virtual ~WeaponPanel();
    DECLARE_EVENT_TABLE()
	void OnType(wxCommandEvent& ev);
};

#endif

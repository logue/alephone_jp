#ifndef _WEAPON_PANEL_
#define _WEAPON_PANEL_

#include "../Common.h"

class WeaponPanel: public wxPanel{
public:
	WeaponPanel(wxWindow* parent, wxWindowID id);
    DECLARE_EVENT_TABLE()
};

#endif

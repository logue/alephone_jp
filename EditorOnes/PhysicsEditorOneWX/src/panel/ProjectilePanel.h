#ifndef _PROJECTILE_PANEL_
#define _PROJECTILE_PANEL_

#include "../Common.h"

class ProjectilePanel: public wxPanel{
public:
	ProjectilePanel(wxWindow* parent, wxWindowID id);
    DECLARE_EVENT_TABLE()
};

#endif

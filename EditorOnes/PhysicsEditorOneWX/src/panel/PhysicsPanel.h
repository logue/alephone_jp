#ifndef _PHYSICS_PANEL_
#define _PHYSICS_PANEL_

#include "../Common.h"

class PhysicsPanel: public wxPanel{
public:
	PhysicsPanel(wxWindow* parent, wxWindowID id);
    DECLARE_EVENT_TABLE()
};

#endif

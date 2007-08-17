#ifndef _EFFECT_PANEL_
#define _EFFECT_PANEL_

#include "../Common.h"

class EffectPanel: public wxPanel{
public:
	EffectPanel(wxWindow* parent, wxWindowID id);
    DECLARE_EVENT_TABLE()
};

#endif

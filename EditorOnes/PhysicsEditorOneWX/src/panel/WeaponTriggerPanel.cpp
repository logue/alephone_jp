#include "WeaponTriggerPanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
};

BEGIN_EVENT_TABLE(WeaponTriggerPanel, wxPanel)
END_EVENT_TABLE()

WeaponTriggerPanel::WeaponTriggerPanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	//create

	//set

	//layout
	wxFlexGridSizer* allSizer = new wxFlexGridSizer(1,2,0,0);
	this->SetSizer(allSizer);
	allSizer->Fit(this);
	Layout();
}

WeaponTriggerPanel::~WeaponTriggerPanel()
{
}

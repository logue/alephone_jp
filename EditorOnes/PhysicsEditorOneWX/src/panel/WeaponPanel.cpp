#include "WeaponPanel.h"
#include "../PhysicsEditorOneWX.h"

enum{
	ID_TYPE,
};

BEGIN_EVENT_TABLE(WeaponPanel, wxPanel)
	EVT_LISTBOX(ID_TYPE, OnType)
END_EVENT_TABLE()

WeaponPanel::WeaponPanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	//create
	this->typeListBox = new wxListBox(this, ID_TYPE);
	
	appearancePanel = new WeaponAppearancePanel(this, wxID_ANY);
	triggerPanel = new WeaponTriggerPanel(this, wxID_ANY);
	this->notebook = new wxNotebook(this, wxID_ANY);
	notebook->AddPage(this->appearancePanel, _T("Appearance"), true);
	notebook->AddPage(this->triggerPanel, _T("Trigger"));

	//set
	this->typeListBox->SetMinSize(wxSize(-1, LIST_BOX_HEIGHT));

	//layout
	wxFlexGridSizer* allSizer = new wxFlexGridSizer(1,2,0,0);
	allSizer->Add(typeListBox);
	allSizer->Add(notebook);
	this->SetSizer(allSizer);
	allSizer->Fit(this);
	Layout();
}

WeaponPanel::~WeaponPanel()
{
}
void WeaponPanel::OnType(wxCommandEvent& ev)
{
	int index = ev.GetSelection();
	if(index >= 0 && index < MAXIMUM_NUMBER_OF_WEAPONS){
		wxGetApp().setEditingWeaponIndex(index);

		//appearance
		appearancePanel->setup();

		//trigger
		triggerPanel->setup();
	}
}

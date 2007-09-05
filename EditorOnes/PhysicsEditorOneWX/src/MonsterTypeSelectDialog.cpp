#include "MonsterTypeSelectDialog.h"
#include "PhysicsEditorOneWX.h"

BEGIN_EVENT_TABLE(MonsterTypeSelectDialog, wxDialog)
	EVT_BUTTON(wxID_OK, MonsterTypeSelectDialog::OnOk)
	EVT_BUTTON(wxID_CANCEL, MonsterTypeSelectDialog::OnCancel)
END_EVENT_TABLE()

wxString title = wxString(_T("Monster select"));

MonsterTypeSelectDialog::MonsterTypeSelectDialog(wxWindow* parent, wxWindowID id):
wxDialog(parent, id, title)
{
	this->typeListBox = new wxListBox(this, wxID_ANY);
	this->okButton = new wxButton(this, wxID_OK, _T("OK"));
	this->cancelButton = new wxButton(this, wxID_CANCEL, _T("Cancel"));

	//set/add
	for(int i = 0; i < NUMBER_OF_MONSTER_TYPES; i ++){
		this->typeListBox->Insert(wxConvertMB2WX(wxGetApp().monsterInfo[i].jname.c_str()), i);
	}

	//layout
	wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);

	wxFlexGridSizer* allSizer = new wxFlexGridSizer(2,1,0,0);
	wxFlexGridSizer* buttonSizer = new wxFlexGridSizer(1,2,0,0);
	allSizer->Add(this->typeListBox,wxEXPAND,0,0);
	buttonSizer->Add(this->typeListBox,wxEXPAND,0,0);
	buttonSizer->Add(this->typeListBox,wxEXPAND,0,0);
	allSizer->Add(buttonSizer);

	boxSizer->Add(allSizer);
	this->SetSizer(boxSizer);
	boxSizer->Fit(this);
	Layout();
}
MonsterTypeSelectDialog::~MonsterTypeSelectDialog()
{
}
void MonsterTypeSelectDialog::OnOk(wxCommandEvent& ev)
{
	int index = this->typeListBox->GetSelection();
	if(index >= 0 && index < NUMBER_OF_MONSTER_TYPES){
		SetReturnCode(wxID_OK);
		Destroy();
	}else{
		wxCommandEvent dummy;
		OnCancel(dummy);
	}
}
void MonsterTypeSelectDialog::OnCancel(wxCommandEvent& ev)
{
	SetReturnCode(wxID_CANCEL);
	Destroy();
}

int MonsterTypeSelectDialog::getIndex()
{
	return this->typeListBox->GetSelection();
}

#include "MonsterPanel.h"

enum{
	ID_TYPE,
	ID_NOTE,
};

BEGIN_EVENT_TABLE(MonsterPanel, wxPanel)
END_EVENT_TABLE()

MonsterPanel::MonsterPanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	//listbox
	monsterTypeListBox = new wxListBox(this, ID_TYPE);
	//notebook
	notebook = new wxNotebook(this, ID_NOTE);

	//Ý’è

	//”z’u
	wxFlexGridSizer* sizerBase = new wxFlexGridSizer(1,2);
	SetSizer(sizerBase);
	sizerBase->Fit(this);
	Layout();
}

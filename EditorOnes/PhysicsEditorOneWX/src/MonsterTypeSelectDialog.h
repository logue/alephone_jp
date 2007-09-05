#ifndef _MONSTER_TYPE_SELECT_DIALOG_
#define _MONSTER_TYPE_SELECT_DIALOG_

#include "Common.h"

class MonsterTypeSelectDialog:public wxDialog{
private:
	wxListBox* typeListBox;
	wxButton* okButton;
	wxButton* cancelButton;
private:
	MonsterTypeSelectDialog(){}
public:
	MonsterTypeSelectDialog(wxWindow* parent, wxWindowID id);
	virtual ~MonsterTypeSelectDialog();
    DECLARE_EVENT_TABLE()
	void OnOk(wxCommandEvent& ev);
	void OnCancel(wxCommandEvent& ev);
public:
	int getIndex();
};

#endif

#ifndef _PHYSICS_PANEL_
#define _PHYSICS_PANEL_

#include "../Common.h"

const int NUMBER_OF_PHYSICS_ITEMS = 26;

class PhysicsPanel: public wxPanel{
private:
	wxChoice* typeChoice;
	wxTextCtrl* datas[NUMBER_OF_PHYSICS_ITEMS];
	_fixed *nums[NUMBER_OF_PHYSICS_ITEMS];
private:
	PhysicsPanel(){}
public:
	PhysicsPanel(wxWindow* parent, wxWindowID id);
	virtual ~PhysicsPanel();
    DECLARE_EVENT_TABLE()
	void OnType(wxCommandEvent& ev);

	void OnData00(wxCommandEvent& ev);
	void OnData01(wxCommandEvent& ev);
	void OnData02(wxCommandEvent& ev);
	void OnData03(wxCommandEvent& ev);
	void OnData04(wxCommandEvent& ev);

	void OnData05(wxCommandEvent& ev);
	void OnData06(wxCommandEvent& ev);
	void OnData07(wxCommandEvent& ev);
	void OnData08(wxCommandEvent& ev);
	void OnData09(wxCommandEvent& ev);

	void OnData10(wxCommandEvent& ev);
	void OnData11(wxCommandEvent& ev);
	void OnData12(wxCommandEvent& ev);
	void OnData13(wxCommandEvent& ev);
	void OnData14(wxCommandEvent& ev);

	void OnData15(wxCommandEvent& ev);
	void OnData16(wxCommandEvent& ev);
	void OnData17(wxCommandEvent& ev);
	void OnData18(wxCommandEvent& ev);
	void OnData19(wxCommandEvent& ev);

	void OnData20(wxCommandEvent& ev);
	void OnData21(wxCommandEvent& ev);
	void OnData22(wxCommandEvent& ev);
	void OnData23(wxCommandEvent& ev);
	void OnData24(wxCommandEvent& ev);
	void OnData25(wxCommandEvent& ev);
private:
	void setup();
	int common();
};

#endif

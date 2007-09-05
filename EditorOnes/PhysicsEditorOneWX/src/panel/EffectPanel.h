#ifndef _EFFECT_PANEL_
#define _EFFECT_PANEL_

#include "../Common.h"

class EffectPanel: public wxPanel{
private:
	wxListBox* typeListBox;

	wxChoice* collectionChoice;
	wxTextCtrl* paletteText;
	wxTextCtrl* sequenceText;
	wxTextCtrl* soundPitchText;
	wxTextCtrl* delayText;
	wxChoice* delaySoundChoice;

	wxCheckBox* flags[5];
private:
	EffectPanel(){}
public:
	EffectPanel(wxWindow* parent, wxWindowID id);
	~EffectPanel();

    DECLARE_EVENT_TABLE()
	void OnType(wxCommandEvent& ev);
	void OnCollection(wxCommandEvent& ev);
	void OnPalette(wxCommandEvent& ev);
	void OnSequence(wxCommandEvent& ev);
	void OnSoundPitch(wxCommandEvent& ev);
	void OnDelay(wxCommandEvent& ev);
	void OnDelaySound(wxCommandEvent& ev);
	void OnFlags(wxCommandEvent& ev);
	void setup();
public:
};

#endif

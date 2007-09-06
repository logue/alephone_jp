#ifndef _PROJECTILE_PANEL_
#define _PROJECTILE_PANEL_

#include "../Common.h"

class ProjectilePanel: public wxPanel{
private:
	wxListBox* typeListBox;

	wxChoice* collectionChoice;
	wxTextCtrl* paletteType;
	wxTextCtrl* sequenceText;
	wxChoice* detonationEffectChoice;
	wxChoice* detonationMediaEffectChoice;
	wxChoice* contrailEffectChoice;
	wxTextCtrl* ticksBetweenContrailsText;
	wxTextCtrl* maxContrailsText;
	wxTextCtrl* mediaPromotionText;
	wxTextCtrl* radiusText;
	wxTextCtrl* areaText;

	//damages
	wxChoice* damageTypeChoice;
	wxTextCtrl* damageBaseText;
	wxTextCtrl* damageRandomText;
	wxTextCtrl* damageScaleText;
	wxCheckBox* damageIsAlienCheckBox;
	
	//flags
	wxCheckBox* flags[NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS];

	//reset
	wxButton* resetButton;

private:
	ProjectilePanel();
public:
	ProjectilePanel(wxWindow* parent, wxWindowID id);
	virtual ~ProjectilePanel();

    DECLARE_EVENT_TABLE()
	void OnType(wxCommandEvent& ev);
	void OnCollection(wxCommandEvent& ev);
	void OnPalette(wxCommandEvent& ev);
	void OnSequence(wxCommandEvent& ev);
	void OnDetonationEffect(wxCommandEvent& ev);
	void OnDetonationMediaEffect(wxCommandEvent& ev);
	void OnContrailEffect(wxCommandEvent& ev);
	void OnTicksBetweenContrails(wxCommandEvent& ev);
	void OnMaxContrail(wxCommandEvent& ev);
	void OnMediaPromotion(wxCommandEvent& ev);
	void OnRadius(wxCommandEvent& ev);
	void OnArea(wxCommandEvent& ev);

	void OnDamageType(wxCommandEvent& ev);
	void OnDamageBase(wxCommandEvent& ev);
	void OnDamageRandom(wxCommandEvent& ev);
	void OnDamageScale(wxCommandEvent& ev);
	void OnDamageIsAlien(wxCommandEvent& ev);

	void OnFlags(wxCommandEvent& ev);

	void OnReset(wxCommandEvent& ev);
private:
	void setup();
};

#endif

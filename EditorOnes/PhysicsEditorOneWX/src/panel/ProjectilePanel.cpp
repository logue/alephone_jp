#include "ProjectilePanel.h"

enum{
	ID_TYPE,
	ID_COLLECTION,
	ID_PALETTE,
	ID_SEQUENCE,
	ID_DETONATION_EFFECT,
	ID_DETONATION_MEDIA_EFFECT,
	ID_CONTRAIL_EFFECT,
	ID_TICKS_BETWEEN_CONTRAILS,
	ID_MAX_CONTRAILS,
	ID_MEDIA_PROMOTION,
	ID_RADIUS,
	ID_AREA,

	ID_DAMAGE_TYPE,
	ID_DAMAGE_BASE,
	ID_DAMAGE_RANDOM,
	ID_DAMAGE_SCALE,
	ID_DAMAGE_IS_ALIEN,

	ID_FLAGS,
	ID_RESET,
};

BEGIN_EVENT_TABLE(ProjectilePanel, wxPanel)
	EVT_LISTBOX(ID_TYPE, ProjectilePanel::OnCollection)

	EVT_CHOICE(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_CHOICE(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_CHOICE(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_CHOICE(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)

	EVT_CHOICE(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_TEXT(ID_COLLECTION, ProjectilePanel::OnCollection)
	EVT_CHECKBOX(ID_COLLECTION, ProjectilePanel::OnCollection)

	EVT_CHECKBOX(ID_COLLECTION, ProjectilePanel::OnCollection)

	EVT_BUTTON(ID_COLLECTION, ProjectilePanel::OnCollection)

END_EVENT_TABLE()

ProjectilePanel::ProjectilePanel(wxWindow* parent, wxWindowID id):
wxPanel(parent, id)
{
	projectile_definitions[i]
}

ProjectilePanel::~ProjectilePanel()
{
}

void ProjectilePanel::OnType(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnCollection(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnPalette(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnSequence(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnDetonationEffect(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnDetonationMediaEffect(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnContrailEffect(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnTicksBetweenContrails(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnMaxContrail(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnMediaPromotion(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnRadius(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnArea(wxCommandEvent& ev)
{
}

void ProjectilePanel::OnDamageType(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnDamageBase(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnDamageRandom(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnDamageScale(wxCommandEvent& ev)
{
}
void ProjectilePanel::OnDamageIsAlien(wxCommandEvent& ev)
{
}

void ProjectilePanel::OnFlags(wxCommandEvent& ev)
{
}

void ProjectilePanel::OnReset(wxCommandEvent& ev)
{
}

void ProjectilePanel::setup()
{
}

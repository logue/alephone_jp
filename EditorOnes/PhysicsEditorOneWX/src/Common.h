#ifndef _COMMON_
#define _COMMON_

#include <wx/wxprec.h>
#include "HPLLib/HPLAlephLib.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
// Include your minimal set of headers here, or wx.h
#include <wx/wx.h>
#endif
#include "wx/settings.h"

#include <wx/bitmap.h>
#include <wx/dcbuffer.h>
#include <wx/bmpbuttn.h>
#include <wx/sizer.h>
#include <wx/cursor.h>
#include <wx/xrc/xmlres.h>
#include <wx/filedlg.h>
#include <wx/listctrl.h>
#include <wx/image.h>
#include <wx/notebook.h>
#include <vector>
#include <string>

#include "monsters.h"
#include "effects.h"
#include "physics_models.h"
#include "projectiles.h"
#include "items.h"
#include "mysound.h"
#include "weapons.h"
#include "monster_definitions.h"
#include "effect_definitions.h"
#include "projectile_definitions.h"
#include "weapon_definitions.h"

#include "PhysicsEditorCommonSrc/PhysicsEditorCommon.h"

void setChoice(wxChoice* choice, int index, int max);
int getChoice(wxChoice* choice, int max);
int getChoice(wxCommandEvent* choice, int max);
int getNumberFromTextCtrl(wxTextCtrl* textCtrl);
int getNumberFromTextCtrl(wxCommandEvent* ev);

const int LIST_BOX_HEIGHT = 300;

#endif

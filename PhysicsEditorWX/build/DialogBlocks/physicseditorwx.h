/////////////////////////////////////////////////////////////////////////////
// Name:        physicseditorwx.h
// Purpose:     
// Author:      koji
// Modified by: 
// Created:     09/06/2007 23:14:05
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _PHYSICSEDITORWX_H_
#define _PHYSICSEDITORWX_H_

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma interface "physicseditorwx.h"
#endif

/*!
 * Includes
 */
#include "header.h"
#include "extensions.h"
#include "FileHandler.h"
#include "map.h"
#include "game_wad.h"
#include "weapons.h"
#include "items.h"
#include "monsters.h"
#include "scenery_definitions.h"
#include "mysound.h"
#include "computer_interface.h"
#include "editor.h"

////@begin includes
#include "wx/image.h"
#include "physicseditoronewx.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
////@end control identifiers

/*!
 * PhysicsEditorWXApp class declaration
 */

class PhysicsEditorWXApp: public wxApp
{    
    DECLARE_CLASS( PhysicsEditorWXApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    PhysicsEditorWXApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin PhysicsEditorWXApp event handler declarations

////@end PhysicsEditorWXApp event handler declarations

////@begin PhysicsEditorWXApp member function declarations

////@end PhysicsEditorWXApp member function declarations

////@begin PhysicsEditorWXApp member variables
////@end PhysicsEditorWXApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(PhysicsEditorWXApp)
////@end declare app

#endif
    // _PHYSICSEDITORWX_H_

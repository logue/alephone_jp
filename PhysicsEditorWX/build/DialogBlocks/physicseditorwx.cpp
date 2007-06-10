/////////////////////////////////////////////////////////////////////////////
// Name:        physicseditorwx.cpp
// Purpose:     
// Author:      koji
// Modified by: 
// Created:     09/06/2007 23:14:05
// RCS-ID:      
// Copyright:   
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "physicseditorwx.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "physicseditorwx.h"

////@begin XPM images
////@end XPM images


/*!
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( PhysicsEditorWXApp )
////@end implement app


/*!
 * PhysicsEditorWXApp type definition
 */

IMPLEMENT_CLASS( PhysicsEditorWXApp, wxApp )


/*!
 * PhysicsEditorWXApp event table definition
 */

BEGIN_EVENT_TABLE( PhysicsEditorWXApp, wxApp )

////@begin PhysicsEditorWXApp event table entries
////@end PhysicsEditorWXApp event table entries

END_EVENT_TABLE()


/*!
 * Constructor for PhysicsEditorWXApp
 */

PhysicsEditorWXApp::PhysicsEditorWXApp()
{
    Init();
}


/*!
 * Member initialisation
 */

void PhysicsEditorWXApp::Init()
{
////@begin PhysicsEditorWXApp member initialisation
////@end PhysicsEditorWXApp member initialisation
}

/*!
 * Initialisation for PhysicsEditorWXApp
 */

bool PhysicsEditorWXApp::OnInit()
{    
////@begin PhysicsEditorWXApp initialisation
	// Remove the comment markers above and below this block
	// to make permanent changes to the code.

#if wxUSE_XPM
	wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
	wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
	wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
	wxImage::AddHandler(new wxGIFHandler);
#endif
	PhysicsEditorOneWX* mainWindow = new PhysicsEditorOneWX( NULL, ID_PHYSICSEDITORONEWX );
	mainWindow->Show(true);
////@end PhysicsEditorWXApp initialisation

    return true;
}


/*!
 * Cleanup for PhysicsEditorWXApp
 */

int PhysicsEditorWXApp::OnExit()
{    
////@begin PhysicsEditorWXApp cleanup
	return wxApp::OnExit();
////@end PhysicsEditorWXApp cleanup
}


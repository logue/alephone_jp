// ShapesEditorOne.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include "HPLLogger.h"

#include "BitmapsDialog.h"
#include "SequencesDialog.h"
#include "SDLToWin32/SDLToWin32.h"
#include "AlephOne/header.h"
#include "AlephOne/extensions.h"
#include "AlephOne/FileHandler.h"
#include "AlephOne/render.h"
#include "AlephOne/shapes_sdl.h"
#include "AlephOne/shape_definitions.h"
#include "AlephOne/collection_definition.h"
#include "AlephOne/shell.h"
#include "AlephOne/editor.h"
#include "HPLLibCommon.h"
#include "HPLLibMFC.h"
#include "AlephOne/interface.h"

// CShapesEditorOneApp:
// See ShapesEditorOne.cpp for the implementation of this class
//

class CShapesEditorOneApp : public CWinApp
{
public:
	CShapesEditorOneApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

public:
    Information showTypeInformations[NUMBER_OF_BITMAPS_DIALOG_SHOW_TYPES];
    Information collectionInformations[NUMBER_OF_COLLECTIONS];
    bool isShapesLoaded;
};

extern CShapesEditorOneApp theApp;
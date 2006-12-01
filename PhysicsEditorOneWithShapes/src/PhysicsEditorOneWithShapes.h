// PhysicsEditorOneWithShapes.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"		// メイン シンボル


// CPhysicsEditorOneWithShapesApp:
// このクラスの実装については、PhysicsEditorOneWithShapes.cpp を参照してください。
//

class CPhysicsEditorOneWithShapesApp : public CWinApp
{
public:
	CPhysicsEditorOneWithShapesApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CPhysicsEditorOneWithShapesApp theApp;

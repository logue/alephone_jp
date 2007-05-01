// MapEditorOne.h : MapEditorOne アプリケーションのメイン ヘッダー ファイル
//
#pragma once

#ifndef __AFXWIN_H__
	#error このファイルを PCH に含める前に、'stdafx.h' を含めてください。
#endif

#include "resource.h"       // メイン シンボル


// CMapEditorOneApp:
// このクラスの実装については、MapEditorOne.cpp を参照してください。
//

class CMapEditorOneApp : public CWinApp
{
public:
	CMapEditorOneApp();


// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMapEditorOneApp theApp;

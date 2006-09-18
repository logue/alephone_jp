#pragma once

#include "AlephOne/SDL.h"
#include "MapEditorSDI.h"
#include "SDLToWin32/SDLToWin32.h"

// CVisualDialog ダイアログ

class CVisualDialog : public CDialog
{
	DECLARE_DYNAMIC(CVisualDialog)

public:
	CVisualDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CVisualDialog();

    //sdl to win api
	SDLToWindows *m_SDLToWindows;

// ダイアログ データ
	enum { IDD = IDD_DIALOG_VISUAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
public:
    virtual BOOL OnInitDialog();
};

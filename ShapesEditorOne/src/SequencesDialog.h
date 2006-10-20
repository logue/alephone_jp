#pragma once

#include "SDLToWin32/SDLToWin32.h"

// CSequencesDialog ダイアログ

class CSequencesDialog : public CDialog
{
	DECLARE_DYNAMIC(CSequencesDialog)

public:
	CSequencesDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSequencesDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SEQUENCES };

    SDLToWindows* sdlToWinScreen;
    CWnd *parent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
public:
    virtual BOOL OnInitDialog();
};

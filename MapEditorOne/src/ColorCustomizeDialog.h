#pragma once

#include "MapEditorOneSetting.h"

// CColorCustomizeDialog ダイアログ

class CColorCustomizeDialog : public CDialog
{
	DECLARE_DYNAMIC(CColorCustomizeDialog)

public:
	CColorCustomizeDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CColorCustomizeDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_COLOR_CUSTOMIZE };

    ColorSettings colorSetting;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
};

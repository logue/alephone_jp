#pragma once
#include "afxwin.h"


// CPlatformDialog ダイアログ

class CPlatformDialog : public CDialog
{
	DECLARE_DYNAMIC(CPlatformDialog)

public:
	CPlatformDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CPlatformDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_PLATFORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
public:
    CComboBox typeCmb;
};

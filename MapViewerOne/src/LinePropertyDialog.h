#pragma once


// CLinePropertyDialog ダイアログ

class CLinePropertyDialog : public CDialog
{
	DECLARE_DYNAMIC(CLinePropertyDialog)

public:
	CLinePropertyDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CLinePropertyDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_LINE_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};

#pragma once


// CPointPropertyDialog ダイアログ

class CPointPropertyDialog : public CDialog
{
	DECLARE_DYNAMIC(CPointPropertyDialog)

public:
	CPointPropertyDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CPointPropertyDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_POINT_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};

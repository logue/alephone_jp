#pragma once


// CSaveCheckDialog ダイアログ

class CSaveCheckDialog : public CDialog
{
	DECLARE_DYNAMIC(CSaveCheckDialog)

public:
	CSaveCheckDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSaveCheckDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SAVE_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

#pragma once


// CSequencesDialog ダイアログ

class CSequencesDialog : public CDialog
{
	DECLARE_DYNAMIC(CSequencesDialog)

public:
	CSequencesDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSequencesDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SEQUENCES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};

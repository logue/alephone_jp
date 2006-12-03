#pragma once


// CShowAnimationDialog ダイアログ

class CShowAnimationDialog : public CDialog
{
	DECLARE_DYNAMIC(CShowAnimationDialog)

public:
	CShowAnimationDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CShowAnimationDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SHOW_ANIMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};

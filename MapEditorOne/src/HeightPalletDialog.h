#pragma once


// CHeightPalletDialog ダイアログ

class CHeightPalletDialog : public CDialog
{
	DECLARE_DYNAMIC(CHeightPalletDialog)

public:
	CHeightPalletDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CHeightPalletDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_HEIGHT_PALLET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};

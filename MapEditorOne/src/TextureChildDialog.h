#pragma once


// CTextureChildDialog ダイアログ

class CTextureChildDialog : public CDialog
{
	DECLARE_DYNAMIC(CTextureChildDialog)

public:
	CTextureChildDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CTextureChildDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_TEXTURE_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};

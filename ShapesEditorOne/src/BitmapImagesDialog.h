#pragma once


// CBitmapImagesDialog ダイアログ

class CBitmapImagesDialog : public CDialog
{
	DECLARE_DYNAMIC(CBitmapImagesDialog)

public:
	CBitmapImagesDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CBitmapImagesDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_BITMAP_IMAGES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};

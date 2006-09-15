#pragma once


// CHeightDialog ダイアログ

class CHeightDialog : public CDialog
{
	DECLARE_DYNAMIC(CHeightDialog)

public:
	CHeightDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CHeightDialog();
public:
    CWnd* parent;
    BOOL Create(CWnd* par);
    virtual void PostNcDestroy();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_HEIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClose();
public:
    virtual BOOL DestroyWindow();
};

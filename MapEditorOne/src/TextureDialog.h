#pragma once
#include "afxwin.h"


// CTextureDialog ダイアログ

class CTextureDialog : public CDialog
{
	DECLARE_DYNAMIC(CTextureDialog)

public:
	CTextureDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CTextureDialog();

    CWnd *parent;
    BOOL Create(CWnd *par);
    virtual void PostNcDestroy();
    virtual BOOL DestroyWindow();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_TEXTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    CComboBox typeCmb;
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnClose();
    afx_msg void OnPaint();
};

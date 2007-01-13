#pragma once
#include "afxwin.h"

#include "TextureChildDialog.h"

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
    //
    int collection;

    //コレクションを設定して更新
    void setupDialog(int col);

    CTextureChildDialog *child;

    void resizeChild();

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
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

#pragma once

#include "SDLToWin32/SDLToWin32.h"
#include "afxcmn.h"

// CBitmapCLUTDialog ダイアログ

class CBitmapCLUTDialog : public CDialog
{
	DECLARE_DYNAMIC(CBitmapCLUTDialog)

public:
	CBitmapCLUTDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CBitmapCLUTDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_BITMAP_CLUT };

    SDLToWindows* sdlToWinScreen;
    CWnd *parent;
    void setupDialog();

    //offset for draw
    int offset;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnPaint();
public:
    CSliderCtrl scrollSlider;
public:
    afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
};

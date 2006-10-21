#pragma once

#include "SDLToWin32/SDLToWin32.h"
#include "afxcmn.h"

// CBitmapCLUTDialog �_�C�A���O

class CBitmapCLUTDialog : public CDialog
{
	DECLARE_DYNAMIC(CBitmapCLUTDialog)

public:
	CBitmapCLUTDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CBitmapCLUTDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_BITMAP_CLUT };

    SDLToWindows* sdlToWinScreen;
    CWnd *parent;
    void setupDialog();

    //offset for draw
    int offset;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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

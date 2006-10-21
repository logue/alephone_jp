#pragma once

#include "SDLToWin32/SDLToWin32.h"
#include "afxwin.h"
#include "afxcmn.h"

// CBitmapImagesDialog �_�C�A���O

class CBitmapImagesDialog : public CDialog
{
	DECLARE_DYNAMIC(CBitmapImagesDialog)

public:
	CBitmapImagesDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CBitmapImagesDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_BITMAP_IMAGES };

    SDLToWindows* sdlToWinScreen;
    CWnd *parent;
    void setupDialog();

    //zoom
    int zoom;

    //offset
    int offset;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
public:
    virtual BOOL OnInitDialog();
public:
    int clutNum;
public:
    CComboBox clutCmb;
public:
    CSliderCtrl scrollSlider;
public:
    afx_msg void OnPaint();
public:
    afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
public:
    afx_msg void OnCbnSelchangeCombo1();
};

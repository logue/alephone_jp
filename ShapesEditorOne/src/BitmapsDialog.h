#pragma once

#include "BitmapImagesDialog.h"
#include "BitmapCLUTDialog.h"
#include "afxwin.h"


// CBitmapsDialog �_�C�A���O

enum{
    eBitmapDialogImages,
    eBitmapDialogCLUT,

    NUMBER_OF_BITMAPS_DIALOG_SHOW_TYPES
};

class CBitmapsDialog : public CDialog
{
	DECLARE_DYNAMIC(CBitmapsDialog)

public:
	CBitmapsDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CBitmapsDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_BITMAPS };

public:
    CBitmapImagesDialog *bitmapImagesDialog;
    CBitmapCLUTDialog *bitmapCLUTDialog;

    int showMode;
    void setupDialog();
    
    //selecting show type
    //selecting collection
    void resize();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CComboBox showTypeCmb;
    afx_msg void OnCbnSelchangeCombo1();
public:
    CComboBox collectionCmb;
public:
    afx_msg void OnCbnSelchangeCombo2();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

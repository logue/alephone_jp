#pragma once

#include "BitmapImagesDialog.h"
#include "BitmapCLUTDialog.h"
#include "afxwin.h"


// CBitmapsDialog �_�C�A���O

enum{
    eBitmapDialogImages,
    eBitmapDialogCLUT,
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
    CBitmapImagesDialog bitmapImagesDialog;
    CBitmapCLUTDialog bitmapCLUTDialog;

    int showMode;
    void setupDialog();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CComboBox showTypeCmb;
    afx_msg void OnCbnSelchangeCombo1();
};

#pragma once

#include "BitmapImagesDialog.h"
#include "BitmapCLUTDialog.h"
#include "afxwin.h"


// CBitmapsDialog ダイアログ

enum{
    eBitmapDialogImages,
    eBitmapDialogCLUT,

    NUMBER_OF_BITMAPS_DIALOG_SHOW_TYPES
};

class CBitmapsDialog : public CDialog
{
	DECLARE_DYNAMIC(CBitmapsDialog)

public:
	CBitmapsDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CBitmapsDialog();

// ダイアログ データ
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

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

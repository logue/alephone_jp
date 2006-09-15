#pragma once
#include "afxwin.h"


// CEffectPage ダイアログ

class CEffectPage : public CDialog
{
	DECLARE_DYNAMIC(CEffectPage)

public:
	CEffectPage(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CEffectPage();
    BOOL OnInitDialog();
    void setupDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    CComboBox effectTypeCmb;
public:
    CEdit effectTypeNum;
public:
    CComboBox effectCollectionCmb;
public:
    CEdit effectCollectionNum;
public:
    CEdit effectSequence;
public:
    CEdit effectPitch;
public:
    CEdit effectDelay;
public:
    CComboBox effectDelaySoundCmb;
public:
    CEdit effectDelaySoundNum;
public:
    afx_msg void OnBnClickedButton1();
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
    afx_msg void OnCbnSelchangeCombo1();
public:
    afx_msg void OnCbnSelchangeCombo15();
public:
    afx_msg void OnEnChangeEdit37();
public:
    afx_msg void OnEnChangeEdit39();
public:
    afx_msg void OnBnClickedCheck5();
public:
    afx_msg void OnEnChangeEdit40();
public:
    afx_msg void OnCbnSelchangeCombo29();
public:
    afx_msg void OnEnChangeEdit4();
public:
    afx_msg void OnBnClickedButton2();
public:
    CButton effectFlags[5];
public:
    afx_msg void OnBnClickedButton3();
public:
    afx_msg void OnBnClickedButton4();
public:
    afx_msg void OnBnClickedButton5();
public:
    afx_msg void OnBnClickedButton13();
public:
    afx_msg void OnBnClickedButton6();
};

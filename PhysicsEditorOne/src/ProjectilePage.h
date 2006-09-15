#pragma once
#include "afxwin.h"


// CProjectilePage ダイアログ

class CProjectilePage : public CDialog
{
	DECLARE_DYNAMIC(CProjectilePage)

public:
	CProjectilePage(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CProjectilePage();
    virtual BOOL OnInitDialog();
    void setupDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_PROJECTILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnCbnSelchangeCombo1();
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
    CComboBox prTypeCmb;
public:
    CComboBox prCollectionCmb;
public:
    CEdit prTypeNum;
public:
    CEdit prCollectionNum;
public:
    CEdit prSequence;
public:
    CComboBox prDetonationEffect;
public:
    CEdit prDetonationEffectNum;
public:
    CComboBox prMediaDetonationEffectCmb;
public:
    CEdit prMediaDetonationEffectNum;
public:
    CComboBox prContrailEffectCmb;
public:
    CEdit prContrailEffectNum;
public:
    CEdit prTicksBetweenContrail;
public:
    CEdit prMaximumContrail;
public:
    CEdit prMediaProjectilePromotion;
public:
    CEdit prRadius;
public:
    CEdit prAreaOfEffect;
public:
    CComboBox prDamageTypeCmb;
public:
    CEdit prDamageTypeNum;
public:
    CEdit prDamageBase;
public:
    CEdit prDamageRandom;
public:
    CEdit prDamageScale;
public:
    CButton prDamageFlag;
public:
    CEdit prSpeed;
public:
    CEdit prRange;
public:
    CEdit prPitch;
public:
    CEdit prFlyBySoundNum;
public:
    CComboBox prFlyBySoundCmb;
public:
    CEdit prBoundSoundNum;
public:
    CComboBox prBoundSoundCmb;
public:
    afx_msg void OnCbnSelchangeCombo15();
public:
    afx_msg void OnEnChangeEdit37();
public:
    CButton prFlags[NUMBER_OF_PROJECTILE_FLAG_INFORMATIONS];
public:
    afx_msg void OnBnClickedCheck5();
public:
    afx_msg void OnEnChangeEdit5();
public:
    afx_msg void OnEnChangeEdit75();
public:
    afx_msg void OnEnChangeEdit76();
public:
    afx_msg void OnCbnSelchangeCombo4();
public:
    afx_msg void OnCbnSelchangeCombo5();
public:
    afx_msg void OnCbnSelchangeCombo16();
public:
    afx_msg void OnCbnSelchangeCombo29();
public:
    afx_msg void OnCbnSelchangeCombo30();
public:
    afx_msg void OnCbnSelchangeCombo6();
public:
    afx_msg void OnBnClickedCheck22();
public:
    afx_msg void OnBnClickedButton2();
public:
    afx_msg void OnBnClickedButton3();
public:
    afx_msg void OnBnClickedButton4();
public:
    afx_msg void OnBnClickedButton5();
public:
    afx_msg void OnBnClickedButton43();
public:
    afx_msg void OnBnClickedButton44();
public:
    afx_msg void OnBnClickedButton45();
public:
    afx_msg void OnBnClickedButton35();
public:
    afx_msg void OnBnClickedButton8();
public:
    afx_msg void OnBnClickedButton9();
public:
    afx_msg void OnBnClickedButton38();
public:
    afx_msg void OnBnClickedButton39();
public:
    afx_msg void OnBnClickedButton40();
public:
    afx_msg void OnBnClickedButton46();
public:
    afx_msg void OnBnClickedButton47();
public:
    afx_msg void OnBnClickedButton48();
public:
    afx_msg void OnBnClickedButton49();
public:
    afx_msg void OnBnClickedButton1();
public:
    afx_msg void OnEnChangeEdit80();
public:
    afx_msg void OnEnChangeEdit81();
public:
    afx_msg void OnEnChangeEdit82();
public:
    afx_msg void OnEnChangeEdit39();
public:
    afx_msg void OnEnChangeEdit71();
public:
    afx_msg void OnEnChangeEdit72();
public:
    afx_msg void OnEnChangeEdit73();
public:
    afx_msg void OnEnChangeEdit74();
};

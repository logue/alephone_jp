#pragma once
#include "afxwin.h"


// CWeaponPage ダイアログ

class CWeaponPage : public CDialog
{
	DECLARE_DYNAMIC(CWeaponPage)

public:
	CWeaponPage(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CWeaponPage();
    virtual BOOL OnInitDialog();
    void setupDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_WEAPON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    CComboBox weaponTypeCmb;
public:
    CEdit weaponTypeNum;
public:
    CComboBox weaponCollectionCmb;
public:
    CEdit weaponCollectionNum;
public:
    CEdit weaponIdleSequence;
public:
    CEdit weaponFiringSequence;
public:
    CEdit weaponReloadSequence;
    CEdit weaponChargingSequence;
public:
    CEdit weaponChargedSequence;
public:
    CComboBox weaponItemCmb;
public:
    CEdit weaponItemNum;
public:
    CComboBox weaponClassCmb;
public:
    CEdit weaponClassNum;
public:
    CComboBox weaponPowerUpCmb;
public:
    CEdit weaponPowerUpNum;
public:
    CButton weaponFlags[NUMBER_OF_WEAPON_FLAG_INFORMATIONS];
public:
    CEdit weaponInstantLight;
public:
    CEdit weaponInstantLightContinue;
public:
    CEdit weaponIdleWidth;
public:
    CEdit weaponIdleHeight;
public:
    CEdit weaponKickHeight;
public:
    CEdit weaponReloadHeight;
public:
    CEdit weaponHorizontalAmplitude;
public:
    CEdit weaponBobAmplitude;
public:
    CEdit weaponReady;
public:
    CEdit weaponAwaitReload;
public:
    CEdit weaponReloading;
public:
    CEdit weaponReloaded;
public:
    CEdit weaponPowerUp;
public:
    afx_msg void OnCbnSelchangeCombo1();
public:
    afx_msg void OnCbnSelchangeCombo29();
public:
    afx_msg void OnEnChangeEdit11();
public:
    afx_msg void OnEnChangeEdit44();
public:
    afx_msg void OnEnChangeEdit12();
public:
    afx_msg void OnEnChangeEdit13();
public:
    afx_msg void OnEnChangeEdit83();
public:
    afx_msg void OnCbnSelchangeCombo15();
public:
    afx_msg void OnCbnSelchangeCombo16();
public:
    afx_msg void OnCbnSelchangeCombo20();
public:
    afx_msg void OnBnClickedCheck2();
public:
    afx_msg void OnEnChangeEdit6();
public:
    afx_msg void OnEnChangeEdit34();
public:
    afx_msg void OnEnChangeEdit35();
public:
    afx_msg void OnEnChangeEdit38();
public:
    afx_msg void OnEnChangeEdit66();
public:
    afx_msg void OnEnChangeEdit41();
public:
    afx_msg void OnEnChangeEdit42();
public:
    afx_msg void OnEnChangeEdit43();
public:
    afx_msg void OnEnChangeEdit47();
public:
    afx_msg void OnEnChangeEdit48();
public:
    afx_msg void OnEnChangeEdit49();
public:
    afx_msg void OnEnChangeEdit84();
public:
    afx_msg void OnEnChangeEdit50();
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

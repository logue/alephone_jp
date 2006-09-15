#pragma once
#include "afxwin.h"


// CWeaponPage2 ダイアログ

class WeaponTrigger
{
public:
    CEdit weaponTypeNum;
    CEdit weaponRoundPerMagazine;
    CComboBox weaponAmmurationTypeCmb;
    CEdit weaponAmmurationTypeNum;
    CEdit weaponRoundTicks;
    CEdit weaponRecoveryTicks;
    CEdit weaponChargingTicks;
    CEdit weaponRecoil;
    CComboBox weaponFiringSoundCmb;
    CEdit weaponFiringSoundNum;
    CComboBox weaponClickSoundCmb;
    CEdit weaponClickSoundNum;
    CComboBox weaponChargingSoundCmb;
    CEdit weaponChargingSoundNum;
    CComboBox weaponShellCasingSoundCmb;
    CEdit weaponShellCasingSoundNum;
    CComboBox weaponReloadingSoundCmb;
    CEdit weaponReloadingSoundNum;
    CComboBox weaponChargedSoundCmb;
    CEdit weaponChargedSoundNum;
    CComboBox weaponProjectileTypeCmb;
    CEdit weaponProjectileTypeNum;
    CEdit weaponError;
    CEdit weaponDeltaX;
    CEdit weaponDeltaZ;
    CComboBox weaponShellCasingTypeCmb;
    CEdit weaponShellCasingTypeNum;
    CEdit weaponBurstCount;
};

class CWeaponPage2 : public CDialog
{
	DECLARE_DYNAMIC(CWeaponPage2)

public:
	CWeaponPage2(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CWeaponPage2();
    virtual BOOL OnInitDialog();
    void setupDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_WEAPON_02 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
    CComboBox weaponTypeCmb;
public:
    WeaponTrigger triggers[NUMBER_OF_TRIGGERS];
public:
    afx_msg void OnCbnSelchangeCombo1();
public:
    afx_msg void OnEnChangeEdit2();
public:
    afx_msg void OnCbnSelchangeCombo15();
public:
    afx_msg void OnEnChangeEdit39();
public:
    afx_msg void OnEnChangeEdit40();
public:
    afx_msg void OnEnChangeEdit62();
public:
    afx_msg void OnEnChangeEdit63();
public:
    afx_msg void OnCbnSelchangeCombo31();
public:
    afx_msg void OnCbnSelchangeCombo32();
public:
    afx_msg void OnCbnSelchangeCombo33();
public:
    afx_msg void OnCbnSelchangeCombo34();
public:
    afx_msg void OnCbnSelchangeCombo35();
public:
    afx_msg void OnCbnSelchangeCombo36();
public:
    afx_msg void OnCbnSelchangeCombo37();
public:
    afx_msg void OnEnChangeEdit83();
public:
    afx_msg void OnEnChangeEdit87();
public:
    afx_msg void OnEnChangeEdit88();
public:
    afx_msg void OnCbnSelchangeCombo38();
public:
    afx_msg void OnEnChangeEdit89();
public:
    CEdit weaponTypeNum;
public:
    afx_msg void OnEnChangeEdit16();
public:
    afx_msg void OnCbnSelchangeCombo25();
public:
    afx_msg void OnEnChangeEdit53();
public:
    afx_msg void OnEnChangeEdit54();
public:
    afx_msg void OnEnChangeEdit91();
public:
    afx_msg void OnEnChangeEdit92();
public:
    afx_msg void OnCbnSelchangeCombo39();
public:
    afx_msg void OnCbnSelchangeCombo40();
public:
    afx_msg void OnCbnSelchangeCombo41();
public:
    afx_msg void OnCbnSelchangeCombo42();
public:
    afx_msg void OnCbnSelchangeCombo43();
public:
    afx_msg void OnCbnSelchangeCombo44();
public:
    afx_msg void OnCbnSelchangeCombo45();
public:
    afx_msg void OnEnChangeEdit99();
public:
    afx_msg void OnEnChangeEdit100();
public:
    afx_msg void OnEnChangeEdit101();
public:
    afx_msg void OnCbnSelchangeCombo46();
public:
    afx_msg void OnEnChangeEdit102();
};

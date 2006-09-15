#pragma once
#include "afxwin.h"


// CMonsterPage ダイアログ

class CMonsterPage : public CDialog
{
	DECLARE_DYNAMIC(CMonsterPage)

public:
	CMonsterPage(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CMonsterPage();
    virtual BOOL OnInitDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	CComboBox MonsterType;
	afx_msg void OnEnChangeEdit1();
    // 種類
    CComboBox monsterActivateSoundCmb;
    CComboBox monsterApologySoundCmb;
    CComboBox monsterCarryingItemTypeCmb;
    CComboBox monsterClassCmb;
    CComboBox monsterClearSoundCmb;
    CComboBox monsterCollectionCmb;
    CComboBox monsterContrailEffectCmb;
    CComboBox monsterDoorRetryMaskCmb;
    CComboBox monsterFramingSoundCmb;
    CComboBox monsterFriendlyActivateSoundCmb;
    CComboBox monsterFriendlyFireSoundCmb;
    CComboBox monsterImpactEffect;
    CComboBox monsterIntelligenceCmb;
    CComboBox monsterKillSoundCmb;
    CComboBox monsterMeleeImpactEffectCmb;
    CComboBox monsterSpeedCmb;
    CEdit monsterActivateSoundNum;
    CEdit monsterApologySoundNum;
    CEdit monsterCarryingItemTypeNum;
    CEdit monsterClass;
    CEdit monsterClearSoundNum;
    CEdit monsterClut;
    CEdit monsterCollectionNumber;
    CEdit monsterContrailEffectNum;
    CEdit monsterDarkVisualArc;
    CEdit monsterDoorRetryMask;
    CEdit monsterExternalVelocityScale;
    CEdit monsterFramingSoundNum;
    CEdit monsterFriendlyActivateSoundNum;
    CEdit monsterFriendlyFireSoundNum;
    CEdit monsterGravity;
    CEdit monsterHeight;
    CEdit monsterImpactEffectNum;
    CEdit monsterIntelligence;
    CEdit monsterKillSoundNum;
    CEdit monsterMaximumLedgeDelta;
    CEdit monsterMeleeImpactEffectNum;
    CEdit monsterMinimumLedgeDelta;
    CEdit monsterPitch;
    CEdit monsterPreferredHoverHeight;
    CEdit monsterRadius;
    CEdit monsterRandomSoundMaskNum;
    CEdit monsterRandomSoundNum;
    CEdit monsterSpeedNum;
    CEdit monsterTerminalSpeedNum;
    CEdit monsterTypeNum;
    CEdit monsterVisualArc;
    CEdit monsterVitality;
    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButton6();
    afx_msg void OnBnClickedButton7();
    afx_msg void OnBnClickedButton8();
    afx_msg void OnBnClickedButton9();
    afx_msg void OnBnClickedButton10();
    afx_msg void OnBnClickedButton11();
    afx_msg void OnBnClickedButton12();
    //afx_msg void OnBnClickedButton13();
    afx_msg void OnBnClickedButton14();
    afx_msg void OnBnClickedButton15();
    afx_msg void OnBnClickedButton16();
    afx_msg void OnBnClickedButton17();
    afx_msg void OnBnClickedButton18();
    afx_msg void OnBnClickedButton19();
    afx_msg void OnBnClickedButton20();
    afx_msg void OnBnClickedButton21();
    afx_msg void OnBnClickedButton22();
    afx_msg void OnBnClickedButton23();
    afx_msg void OnBnClickedButton24();
    afx_msg void OnBnClickedButton25();
    afx_msg void OnBnClickedButton26();
    afx_msg void OnBnClickedButton27();
    afx_msg void OnBnClickedButton28();
    afx_msg void OnBnClickedButton29();
    afx_msg void OnBnClickedButton30();
    afx_msg void OnBnClickedButton31();
    afx_msg void OnBnClickedButton32();
    afx_msg void OnBnClickedButton33();
    afx_msg void OnCbnSelchangeCombo1();
    afx_msg void OnCbnSelchangeCombo10();
    afx_msg void OnCbnSelchangeCombo11();
    afx_msg void OnCbnSelchangeCombo2();
    afx_msg void OnCbnSelchangeCombo4();
    afx_msg void OnCbnSelchangeCombo5();
    afx_msg void OnCbnSelchangeCombo6();
    afx_msg void OnCbnSelchangeCombo7();
    afx_msg void OnCbnSelchangeCombo8();
    afx_msg void OnCbnSelchangeCombo9();
    afx_msg void OnEnChangeEdit19();
    afx_msg void OnEnChangeEdit20();
    afx_msg void OnEnChangeEdit21();
    afx_msg void OnEnChangeEdit36();
    afx_msg void OnEnChangeEdit4();
    afx_msg void OnEnChangeEdit6();
    afx_msg void OnEnChangeEdit7();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    void setupDialog(int type);
    afx_msg void OnEnChangeEdit22();
    afx_msg void OnEnChangeEdit23();
    afx_msg void OnEnChangeEdit24();
public:
    afx_msg void OnCbnSelchangeCombo3();
public:
    afx_msg void OnEnChangeEdit5();
public:
    afx_msg void OnCbnSelchangeCombo17();
public:
    afx_msg void OnEnChangeEdit29();
public:
    afx_msg void OnCbnSelchangeCombo18();
public:
    afx_msg void OnEnChangeEdit30();
public:
    afx_msg void OnEnChangeEdit31();
public:
    afx_msg void OnEnChangeEdit32();
public:
    afx_msg void OnCbnSelchangeCombo19();
public:
    afx_msg void OnCbnSelchangeCombo12();
public:
    afx_msg void OnCbnSelchangeCombo13();
public:
    afx_msg void OnCbnSelchangeCombo14();
public:
    afx_msg void OnEnChangeEdit16();
public:
    CComboBox monsterRandomSound;
public:
    afx_msg void OnCbnSelchangeCombo46();
public:
    afx_msg void OnEnChangeEdit28();
public:
    afx_msg void OnEnChangeEdit17();
};
//
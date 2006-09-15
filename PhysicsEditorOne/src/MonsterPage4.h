#pragma once
#include "afxwin.h"


// CMonsterPage4 ダイアログ

class CMonsterPage4 : public CDialog
{
	DECLARE_DYNAMIC(CMonsterPage4)

public:
	CMonsterPage4(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CMonsterPage4();
    virtual BOOL OnInitDialog();
    void setupDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_MONSTER_04_ATTACK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
    afx_msg void OnCbnSelchangeCombo1();
public:
    CComboBox monsterType;
public:
    CEdit monsterTypeNum;
public:
    CEdit monsterAttackFrequency;
public:
    CComboBox monsterMeleeType;
public:
    CEdit monsterMeleeTypeNum;
public:
    CEdit monsterMeleeRepeat;
public:
    CEdit monsterMeleeError;
public:
    CEdit monsterMeleeRange;
public:
    CEdit monsterMeleeSequence;
public:
    CEdit monsterMeleeDeltaX;
public:
    CEdit monsterMeleeDeltaY;
public:
    CEdit monsterMeleeDeltaZ;
public:
    afx_msg void OnBnClickedButton1();
public:
    afx_msg void OnCbnSelchangeCombo15();
public:
    afx_msg void OnBnClickedButton2();
public:
    CEdit monsterAwayTypeNum;
public:
    CComboBox monsterAwayTypeCmb;
public:
    CEdit monsterAwayRepeat;
public:
    CEdit monsterAwayError;
public:
    CEdit monsterAwayRange;
public:
    CEdit monsterAwaySequence;
public:
    CEdit monsterAwayDeltaX;
public:
    CEdit monsterAwayDeltaY;
public:
    CEdit monsterAwayDeltaZ;
public:
    afx_msg void OnCbnSelchangeCombo28();
public:
    afx_msg void OnBnClickedButton3();
public:
    afx_msg void OnEnChangeEdit1();
public:
    afx_msg void OnEnChangeEdit37();
public:
    afx_msg void OnEnChangeEdit39();
public:
    afx_msg void OnEnChangeEdit40();
public:
    afx_msg void OnEnChangeEdit62();
public:
    afx_msg void OnEnChangeEdit63();
public:
    afx_msg void OnEnChangeEdit64();
public:
    afx_msg void OnEnChangeEdit65();
public:
    afx_msg void OnEnChangeEdit38();
public:
    afx_msg void OnEnChangeEdit66();
public:
    afx_msg void OnEnChangeEdit41();
public:
    afx_msg void OnEnChangeEdit67();
public:
    afx_msg void OnEnChangeEdit68();
public:
    afx_msg void OnEnChangeEdit69();
public:
    afx_msg void OnEnChangeEdit70();
};

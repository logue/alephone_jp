#pragma once
#include "afxwin.h"


// CMonsterPage3 ダイアログ

class CMonsterPage3 : public CDialog
{
	DECLARE_DYNAMIC(CMonsterPage3)

public:
	CMonsterPage3(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CMonsterPage3();
    virtual BOOL OnInitDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_MONSTER_03 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

public:
    void setupDialog();
    afx_msg void OnCbnSelchangeCombo1();
    CComboBox monsterTypeCmb;
    CEdit monsterTypeNum;
    CEdit monsterStationalyNum;
    CEdit monsterMoving;
    CEdit monsterHitting;
    CEdit monsterLightDying;
    CEdit monsterLightDeath;
    CEdit monsterHeavyDying;
    CEdit monsterHeavyDeath;
    CEdit monsterTeleportIn;
    CEdit monsterTeleportOut;
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButton35();
    afx_msg void OnBnClickedButton36();
    afx_msg void OnBnClickedButton37();
    afx_msg void OnBnClickedButton38();
    afx_msg void OnBnClickedButton39();
    afx_msg void OnBnClickedButton40();
    afx_msg void OnBnClickedButton41();
    afx_msg void OnBnClickedButton42();
    afx_msg void OnEnChangeEdit37();
    afx_msg void OnEnChangeEdit40();
    afx_msg void OnEnChangeEdit43();
    afx_msg void OnEnChangeEdit46();
    afx_msg void OnEnChangeEdit49();
    afx_msg void OnEnChangeEdit52();
    afx_msg void OnEnChangeEdit55();
    afx_msg void OnEnChangeEdit58();
    afx_msg void OnEnChangeEdit61();
    CButton collectionUnify;
    CButton clutUnify;
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
    CEdit monsterStationalyCollectionNum;
public:
    CEdit monsterCollectionNum;
public:
    CEdit monsterCLUT;
public:
    afx_msg void OnCbnSelchangeCombo15();
public:
    CComboBox monsterCollectionCmb;
public:
    afx_msg void OnEnChangeEdit1();
};

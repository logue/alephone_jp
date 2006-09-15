#pragma once
#include "afxwin.h"


// CMonsterPage2 ダイアログ

class CMonsterPage2 : public CDialog
{
	DECLARE_DYNAMIC(CMonsterPage2)

public:
	CMonsterPage2(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CMonsterPage2();
    virtual BOOL OnInitDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_MONSTER_02 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    CComboBox monsterTypeCmb;
public:
    CEdit monsterTypeNum;

    //耐性ビット更新
    void setupImmunities();
    //各フラグの状態から耐性ビットを取得
    uint32 getImmunitiesBits();

    //弱点ビット更新
    void setupWeaknesses();
    //各フラグの状態から弱点ビットを取得
    uint32 getWeaknessesBits();

    //フラグ更新
    void setupFlag();
    //フラグの状態を統合
    uint32 getFlagBits();

    void setupDialog();

    //敵ビット更新
    void setupEnemy();
    //各フラグの状態から敵ビットを取得
    uint32 getEnemyBits();

    //味方ビット更新
    void setupFriend();
    //各フラグの状態から味方ビットを取得
    uint32 getFriendBits();
public:
    //特徴フラグ
    CButton monsterFlag[NUMBER_OF_MONSTER_FLAG_INFORMATIONS];

    //耐性ダメージ
    CButton monsterImmunities[NUMBER_OF_DAMAGE_TYPES];

    //弱点ダメージ
    CButton monsterWeaknesses[NUMBER_OF_DAMAGE_TYPES];

    //敵
    CButton monsterEnemy[NUMBER_OF_CLASS_INFORMATIONS];

    //味方
    CButton monsterFriend[NUMBER_OF_CLASS_INFORMATIONS];
public:
    //immunities
    afx_msg void OnBnClickedCheck1();

    //weaknesses
    afx_msg void OnBnClickedCheck2();

    //flags
    afx_msg void OnBnClickedCheck3();

    //enemy
    afx_msg void OnBnClickedCheck10();

    //friend
    afx_msg void OnBnClickedCheck11();
public:
    afx_msg void OnBnClickedButton9();
public:
    afx_msg void OnBnClickedButton4();
public:
    afx_msg void OnCbnSelchangeCombo1();
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
public:
    afx_msg void OnBnClickedButton13();
public:
    afx_msg void OnBnClickedButton34();
};

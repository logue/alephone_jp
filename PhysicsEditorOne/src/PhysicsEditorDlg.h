// PhysicsEditorDlg.h : ヘッダー ファイル
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MonsterPage.h"
#include "MonsterPage2.h"
#include "MonsterPage3.h"
#include "MonsterPage4.h"
#include "EffectPage.h"
#include "ProjectilePage.h"
#include "WeaponPage.h"
#include "WeaponPage2.h"
#include "PhysicsPage.h"

// CPhysicsEditorDlg ダイアログ
class CPhysicsEditorDlg : public CDialog
{
// コンストラクション
public:
	CPhysicsEditorDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_PHYSICSEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート
    void setupDialogs();

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpenPhysics();
public:
	CString physicsFileNameField;
public:
	CEdit physicsFileName;
public:
	CTabCtrl phyTabPane;
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
public:
	CMonsterPage monsterPage;
	CMonsterPage2 monsterPage2;
	CMonsterPage3 monsterPage3;
	CMonsterPage4 monsterPage4;
	CEffectPage effectPage;
    CProjectilePage projectilePage;
    CPhysicsPage physicsPage;
    CWeaponPage weaponPage;
    CWeaponPage2 weaponPage2;
public:
	afx_msg void OnFileExit32774();
public:
	afx_msg void OnFileNew32771();
public:
	afx_msg void OnFileSave();
    void importPhysicsFile(const char* filename);

public:
    afx_msg void OnDestroy();
public:
    afx_msg void OnClose();
protected:
    //HACCEL accel;
public:
    //BOOL PreTranslateMessage(MSG* pMsg);
	//afx_msg void OnKeyDown();
};

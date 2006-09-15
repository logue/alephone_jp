// PhysicsEditorDlg.h : �w�b�_�[ �t�@�C��
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

// CPhysicsEditorDlg �_�C�A���O
class CPhysicsEditorDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CPhysicsEditorDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PHYSICSEDITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g
    void setupDialogs();

// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
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

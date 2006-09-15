#pragma once
#include "afxwin.h"


// CMonsterPage2 �_�C�A���O

class CMonsterPage2 : public CDialog
{
	DECLARE_DYNAMIC(CMonsterPage2)

public:
	CMonsterPage2(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CMonsterPage2();
    virtual BOOL OnInitDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_MONSTER_02 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    CComboBox monsterTypeCmb;
public:
    CEdit monsterTypeNum;

    //�ϐ��r�b�g�X�V
    void setupImmunities();
    //�e�t���O�̏�Ԃ���ϐ��r�b�g���擾
    uint32 getImmunitiesBits();

    //��_�r�b�g�X�V
    void setupWeaknesses();
    //�e�t���O�̏�Ԃ����_�r�b�g���擾
    uint32 getWeaknessesBits();

    //�t���O�X�V
    void setupFlag();
    //�t���O�̏�Ԃ𓝍�
    uint32 getFlagBits();

    void setupDialog();

    //�G�r�b�g�X�V
    void setupEnemy();
    //�e�t���O�̏�Ԃ���G�r�b�g���擾
    uint32 getEnemyBits();

    //�����r�b�g�X�V
    void setupFriend();
    //�e�t���O�̏�Ԃ��疡���r�b�g���擾
    uint32 getFriendBits();
public:
    //�����t���O
    CButton monsterFlag[NUMBER_OF_MONSTER_FLAG_INFORMATIONS];

    //�ϐ��_���[�W
    CButton monsterImmunities[NUMBER_OF_DAMAGE_TYPES];

    //��_�_���[�W
    CButton monsterWeaknesses[NUMBER_OF_DAMAGE_TYPES];

    //�G
    CButton monsterEnemy[NUMBER_OF_CLASS_INFORMATIONS];

    //����
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

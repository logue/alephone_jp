#pragma once
#include "afxwin.h"
#include "map.h"


// CLevelParameterDialog �_�C�A���O

/**
    level parameters dialog
*/
class CLevelParameterDialog : public CDialog
{
	DECLARE_DYNAMIC(CLevelParameterDialog)

public:
	//CLevelParameterDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
    /**
        @param isNewLevelDialog
        �V�K���x���Ƃ��ČĂяo�������ǂ���
        �V�K�Ȃ�Βl�͐ݒ肵�Ȃ�
        �V�K�łȂ���Γǂݍ���ł��郌�x���̏��𔽉f������
    */
    CLevelParameterDialog(CWnd* pParent , bool isNewLevelDialog);
	virtual ~CLevelParameterDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_LEVEL_PARAMETER };

    bool isNew;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    CEdit levelName;
public:
    CComboBox environment;
public:
    CComboBox landscape;
public:
    CButton gameTypes[NUMBER_OF_GAME_TYPES];
public:
    CButton envTypes[NUMBER_OF_ENV_TYPES];
public:
    CButton missionFlags[NUMBER_OF_MISSION_TYPES];
public:
    virtual BOOL OnInitDialog();
};

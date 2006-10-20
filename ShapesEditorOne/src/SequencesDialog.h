#pragma once

#include "SDLToWin32/SDLToWin32.h"

// CSequencesDialog �_�C�A���O

class CSequencesDialog : public CDialog
{
	DECLARE_DYNAMIC(CSequencesDialog)

public:
	CSequencesDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSequencesDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_SEQUENCES };

    SDLToWindows* sdlToWinScreen;
    CWnd *parent;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
public:
    virtual BOOL OnInitDialog();
};

#pragma once
#include "afxwin.h"


// CPlatformDialog �_�C�A���O

class CPlatformDialog : public CDialog
{
	DECLARE_DYNAMIC(CPlatformDialog)

public:
	CPlatformDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CPlatformDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_PLATFORM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
public:
    CComboBox typeCmb;
};

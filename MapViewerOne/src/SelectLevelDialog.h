#pragma once
#include "afxwin.h"


// CSelectLevelDialog �_�C�A���O

class CSelectLevelDialog : public CDialog
{
	DECLARE_DYNAMIC(CSelectLevelDialog)

public:
	CSelectLevelDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSelectLevelDialog();

// �_�C�A���O �f�[�^
	enum { IDD = ID_DIALOG_SELECT_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    CListBox selectLevelListBox;
    afx_msg void OnLbnSelchangeList1();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    virtual BOOL OnInitDialog();
    afx_msg void OnLbnDblclkList1();
};

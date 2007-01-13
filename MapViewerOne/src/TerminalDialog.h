#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTerminalDialog �_�C�A���O

class CTerminalDialog : public CDialog
{
	DECLARE_DYNAMIC(CTerminalDialog)

public:
	CTerminalDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CTerminalDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_TERMINAL };

    //editing terminal index
    int editTerminalIndex;
    //-1 for no select
    int editTerminalGroupIndex;
    //setup dialog
    void setupDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
public:
    CListBox terminalList;
public:
    CListBox terminalGroupList;
public:
//    CRichEditCtrl terminalEdit;
public:
    afx_msg void OnLbnSelchangeListTerminals();
public:
    afx_msg void OnLbnSelchangeListGroups();
    CEdit terminalEdit;
    CListBox informationList;
};

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CTerminalDialog ダイアログ

class CTerminalDialog : public CDialog
{
	DECLARE_DYNAMIC(CTerminalDialog)

public:
	CTerminalDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CTerminalDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_TERMINAL };

    //editing terminal index
    int editTerminalIndex;
    //-1 for no select
    int editTerminalGroupIndex;
    //setup dialog
    void setupDialog();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

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

#pragma once
#include "afxwin.h"


// CSelectLevelDialog ダイアログ

class CSelectLevelDialog : public CDialog
{
	DECLARE_DYNAMIC(CSelectLevelDialog)

public:
	CSelectLevelDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSelectLevelDialog();

// ダイアログ データ
	enum { IDD = ID_DIALOG_SELECT_LEVEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    CListBox selectLevelListBox;
    afx_msg void OnLbnSelchangeList1();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    virtual BOOL OnInitDialog();
    afx_msg void OnLbnDblclkList1();
};

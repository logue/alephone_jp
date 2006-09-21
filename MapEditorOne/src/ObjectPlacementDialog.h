#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CObjectPlacementDialog ダイアログ

class CObjectPlacementDialog : public CDialog
{
	DECLARE_DYNAMIC(CObjectPlacementDialog)

public:
	CObjectPlacementDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CObjectPlacementDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_OBJECT_PLACEMENT };
    int idColumn[7];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CListCtrl objectPlacementListCtrl;
    CEdit minimumNum;
    CEdit maximum;
    CEdit randomCountNum;
    afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
};

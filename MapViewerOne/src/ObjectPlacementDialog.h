#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CObjectPlacementDialog �_�C�A���O

class CObjectPlacementDialog : public CDialog
{
	DECLARE_DYNAMIC(CObjectPlacementDialog)

public:
	CObjectPlacementDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CObjectPlacementDialog();

    //setup list control
    void setupDialog();

    //
    void setListControlItem(CListCtrl *ctrl,
        object_frequency_definition *place,
        LVITEM *item);

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_OBJECT_PLACEMENT };
    int idColumn[7];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
    CListCtrl objectPlacementListCtrl;
    CEdit minimumNum;
    CEdit maximum;
    CEdit randomCountNum;
    afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
public:
    afx_msg void OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult);
public:
    CEdit randomChanceNum;
public:
    CButton placementFlags;
public:
    afx_msg void OnBnClickedCheck1();
public:
    afx_msg void OnEnChangeEdit1();
public:
    afx_msg void OnEnChangeEdit2();
public:
    afx_msg void OnEnChangeEdit3();
public:
    afx_msg void OnEnChangeEdit4();
public:
    CEdit initialNum;
public:
    afx_msg void OnEnChangeEdit5();
};

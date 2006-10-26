#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CHeightDialog �_�C�A���O

class CHeightDialog : public CDialog
{
	DECLARE_DYNAMIC(CHeightDialog)

public:
	CHeightDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CHeightDialog();
public:
    CWnd* parent;
    BOOL Create(CWnd* par);
    virtual void PostNcDestroy();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_HEIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClose();
public:
    virtual BOOL DestroyWindow();
public:
    virtual BOOL OnInitDialog();
public:
    CSliderCtrl maxSlider;
public:
    CSliderCtrl minSlider;
public:
    afx_msg void OnNMCustomdrawSlider2(NMHDR *pNMHDR, LRESULT *pResult);
public:
    afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
public:
    CEdit maxNum;
public:
    CEdit minNum;
public:
    afx_msg void OnEnChangeEdit1();
public:
    afx_msg void OnEnChangeEdit6();
public:
    afx_msg void OnBnClickedCheck1();
public:
    BOOL isRevealHiddenLines;
};

#pragma once
#include "afxcmn.h"


// CPolygonTypeDialog �_�C�A���O

class CPolygonTypeDialog : public CDialog
{
	DECLARE_DYNAMIC(CPolygonTypeDialog)

public:
	CPolygonTypeDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CPolygonTypeDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_POLYGON_TYPE };

    CWnd* parent;
    BOOL Create(CWnd *par);
    virtual void PostNcDestroy();
public:
    afx_msg void OnClose();
    CImageList imageList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
public:
    CListCtrl polygonTypeListCtrl;
public:
    virtual BOOL DestroyWindow();
};

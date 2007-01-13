#pragma once
#include "afxcmn.h"


// CPolygonTypeDialog ダイアログ

class CPolygonTypeDialog : public CDialog
{
	DECLARE_DYNAMIC(CPolygonTypeDialog)

public:
	CPolygonTypeDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CPolygonTypeDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_POLYGON_TYPE };

    CWnd* parent;
    BOOL Create(CWnd *par);
    virtual void PostNcDestroy();
public:
    afx_msg void OnClose();
    CImageList imageList;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
public:
    CListCtrl polygonTypeListCtrl;
public:
    virtual BOOL DestroyWindow();
};

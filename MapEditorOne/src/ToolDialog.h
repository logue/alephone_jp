#pragma once


// CToolDialog �_�C�A���O

class CToolDialog : public CDialog
{
	DECLARE_DYNAMIC(CToolDialog)

public:
	CToolDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CToolDialog();

    CWnd *parent;
    BOOL Create(CWnd *par);
    virtual void PostNcDestroy();

    //tool's icons
    CImageList imageList;
    vector<CBitmap*> bitmaps;

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_TOOL };
    BOOL CToolDialog::DestroyWindow();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClose();
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnPaint();
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

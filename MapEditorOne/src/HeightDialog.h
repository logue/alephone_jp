#pragma once


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
};

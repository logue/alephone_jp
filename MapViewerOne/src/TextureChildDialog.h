#pragma once


// CTextureChildDialog �_�C�A���O

class CTextureChildDialog : public CDialog
{
	DECLARE_DYNAMIC(CTextureChildDialog)

public:
	CTextureChildDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CTextureChildDialog();
    
    CWnd *parent;

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_TEXTURE_CHILD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnPaint();
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
};

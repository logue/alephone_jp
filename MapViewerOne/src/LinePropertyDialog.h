#pragma once


// CLinePropertyDialog �_�C�A���O

class CLinePropertyDialog : public CDialog
{
	DECLARE_DYNAMIC(CLinePropertyDialog)

public:
	CLinePropertyDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CLinePropertyDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_LINE_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};

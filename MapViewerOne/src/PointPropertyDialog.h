#pragma once


// CPointPropertyDialog �_�C�A���O

class CPointPropertyDialog : public CDialog
{
	DECLARE_DYNAMIC(CPointPropertyDialog)

public:
	CPointPropertyDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CPointPropertyDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_POINT_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};

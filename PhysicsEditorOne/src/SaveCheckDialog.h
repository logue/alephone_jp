#pragma once


// CSaveCheckDialog �_�C�A���O

class CSaveCheckDialog : public CDialog
{
	DECLARE_DYNAMIC(CSaveCheckDialog)

public:
	CSaveCheckDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSaveCheckDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_SAVE_CHECK };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

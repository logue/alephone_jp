#pragma once


// CShowAnimationDialog �_�C�A���O

class CShowAnimationDialog : public CDialog
{
	DECLARE_DYNAMIC(CShowAnimationDialog)

public:
	CShowAnimationDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CShowAnimationDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_SHOW_ANIMATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};

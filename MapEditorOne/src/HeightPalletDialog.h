#pragma once


// CHeightPalletDialog �_�C�A���O

class CHeightPalletDialog : public CDialog
{
	DECLARE_DYNAMIC(CHeightPalletDialog)

public:
	CHeightPalletDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CHeightPalletDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_HEIGHT_PALLET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};

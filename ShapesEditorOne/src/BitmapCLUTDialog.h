#pragma once


// CBitmapCLUTDialog �_�C�A���O

class CBitmapCLUTDialog : public CDialog
{
	DECLARE_DYNAMIC(CBitmapCLUTDialog)

public:
	CBitmapCLUTDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CBitmapCLUTDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_BITMAP_CLUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};

#pragma once


// CBitmapImagesDialog �_�C�A���O

class CBitmapImagesDialog : public CDialog
{
	DECLARE_DYNAMIC(CBitmapImagesDialog)

public:
	CBitmapImagesDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CBitmapImagesDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_BITMAP_IMAGES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};

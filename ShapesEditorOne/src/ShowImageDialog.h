#pragma once


// CShowImageDialog �_�C�A���O

class CShowImageDialog : public CDialog
{
	DECLARE_DYNAMIC(CShowImageDialog)

public:
	CShowImageDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CShowImageDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_SHOW_IMAGE };

    int collectionIndex;
    int bitmapIndex;
    int clutNum;

    void setupDialog(int col, int bitmap, int clut);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnPaint();
};

#pragma once
#include "afxwin.h"

#include "TextureDialog.h"

// CTextureDialog �_�C�A���O

class CTextureDialog : public CDialog
{
	DECLARE_DYNAMIC(CTextureDialog)

public:
	CTextureDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CTextureDialog();

    CWnd *parent;
    BOOL Create(CWnd *par);
    virtual void PostNcDestroy();
    virtual BOOL DestroyWindow();
    //
    int collection;

    //�R���N�V������ݒ肵�čX�V
    void setupDialog(int col);

    CTextureDialog *child;

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_TEXTURE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    CComboBox typeCmb;
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnClose();
    afx_msg void OnPaint();
};

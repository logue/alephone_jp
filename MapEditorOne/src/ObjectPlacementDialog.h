#pragma once


// CObjectPlacementDialog �_�C�A���O

class CObjectPlacementDialog : public CDialog
{
	DECLARE_DYNAMIC(CObjectPlacementDialog)

public:
	CObjectPlacementDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CObjectPlacementDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_OBJECT_PLACEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};

#pragma once


// CAnnotationDialog �_�C�A���O

class CAnnotationDialog : public CDialog
{
	DECLARE_DYNAMIC(CAnnotationDialog)

public:
	CAnnotationDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CAnnotationDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_ANNOTATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    CString annotationText;
public:
    BOOL isOnlyDisplayWhenPolygonShown;
public:
    afx_msg void OnEnChangeEdit1();
};

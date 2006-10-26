#pragma once


// CAnnotationDialog ダイアログ

class CAnnotationDialog : public CDialog
{
	DECLARE_DYNAMIC(CAnnotationDialog)

public:
	CAnnotationDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CAnnotationDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_ANNOTATION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    CString annotationText;
public:
    BOOL isOnlyDisplayWhenPolygonShown;
public:
    afx_msg void OnEnChangeEdit1();
};

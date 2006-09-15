#pragma once


// CObjectPlacementDialog ダイアログ

class CObjectPlacementDialog : public CDialog
{
	DECLARE_DYNAMIC(CObjectPlacementDialog)

public:
	CObjectPlacementDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CObjectPlacementDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_OBJECT_PLACEMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();
};

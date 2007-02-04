#pragma once


// CSidePropertyDialog ダイアログ

class CSidePropertyDialog : public CDialog
{
	DECLARE_DYNAMIC(CSidePropertyDialog)

public:
	CSidePropertyDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSidePropertyDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SIDE_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    /////////////////////
    CWnd* parent;
    void OnClose();
    BOOL Create(CWnd* par);
    virtual void PostNcDestroy();
    side_data store;
    void setupDialog(int index_);
    void setupDialogByStore();
    int index;
    ////////////////////////

};

#pragma once


// CSidePropertyDialog �_�C�A���O

class CSidePropertyDialog : public CDialog
{
	DECLARE_DYNAMIC(CSidePropertyDialog)

public:
	CSidePropertyDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSidePropertyDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_SIDE_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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

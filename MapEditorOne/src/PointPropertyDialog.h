#pragma once
#include "afxwin.h"


// CPointPropertyDialog �_�C�A���O

class CPointPropertyDialog : public CDialog
{
	DECLARE_DYNAMIC(CPointPropertyDialog)

public:
	CPointPropertyDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CPointPropertyDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_POINT_PROPERTY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

public:
    /////////////////////
    CWnd* parent;
    BOOL Create(CWnd* par);
    virtual void PostNcDestroy();
    point_data store;
    void setupDialog(int index_);
    void setupDialogByStore();
    int index;
    ////////////////////////
public:
    bool flagSolid;
public:
    bool flagTransparent;
public:
    CButton flagElevation;
public:
    CEdit pointFloor;
public:
    CEdit pointHeight;
public:
    CEdit pointVertexX;
public:
    CEdit pointVertexY;
public:
    CEdit pointTransX;
public:
    CEdit pointTransY;
public:
    CEdit pointSupPolygonIndex;
};

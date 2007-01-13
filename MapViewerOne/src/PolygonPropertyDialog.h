#pragma once
#include "afxwin.h"

#include "PlatformDialog.h"

// CPolygonPropertyDialog ダイアログ

class CPolygonPropertyDialog : public CDialog
{
	DECLARE_DYNAMIC(CPolygonPropertyDialog)

public:
	CPolygonPropertyDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CPolygonPropertyDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_POLYGON_PROPERTY };

public:
    CWnd* parent;
    BOOL Create(CWnd* par);
    virtual void PostNcDestroy();
    polygon_data store;
    void setupDialog(int index_);
    void setupDialogByStore();
    int index;
    void setupLightSourceIndex(CComboBox* combo, int index, int max);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClose();
public:
    CEdit idNum;
public:
    CComboBox typeCmb;
public:
    CEdit permutationNum;
public:
    CComboBox floorLightCmb;
public:
    CComboBox ceilingLightCmb;
public:
    CEdit areaNum;
public:
    CEdit firstObjectNum;
public:
    CEdit floorExZone;
public:
    CEdit lineExZone;
public:
    CEdit floorTrans;
public:
    CEdit ceilingTrans;
public:
    CEdit firstNeighbourNum;
public:
    CEdit nearCountNum;
public:
    CEdit centerXNum;
public:
    CEdit centerYNum;
public:
    CEdit floorOriginNum;
public:
    CEdit ceilingOrigiinNum;
public:
    CComboBox mediaCmb;
public:
    CComboBox mediaLightCmb;
public:
    CEdit soundSourceIndexNum;
public:
    CComboBox ambientSoundIndexNum;
public:
    CComboBox randomSoundCmb;
public:
    CEdit floorOriginYNum;
public:
    CEdit ceilingOriginYNum;
public:
    afx_msg void OnBnClickedButton1();
public:
    virtual BOOL OnInitDialog();
};

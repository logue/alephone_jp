#pragma once
#include "afxwin.h"


// CMonsterPropertyDialog ダイアログ
const int NUMBER_OF_OBJECT_FLAGS = 6;

class CMonsterPropertyDialog : public CDialog
{
	DECLARE_DYNAMIC(CMonsterPropertyDialog)

public:
	CMonsterPropertyDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CMonsterPropertyDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG3 };

public:
    CWnd* parent;
    BOOL Create(CWnd* par);
    virtual void PostNcDestroy();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnClose();
    CComboBox objectTypeCmb;
public:
    CEdit objectTypeNum;
public:
    CComboBox objectClassedTypeCmb;
public:
    CEdit objectClassedTypeNum;
public:
    CButton objectFlags[NUMBER_OF_OBJECT_FLAGS];
public:
    CEdit objectIndex;
public:
    CEdit objectPolygonId;
public:
    CComboBox objectActivation;
public:
    CEdit objectPositionX;
public:
    CEdit objectPositionY;
public:
    CEdit objectPositionZ;
    //setup dialog
    //object == NULL ->clear
    //caution !!!! indexOfSavedObjectList is not map_object.index!!!
    void setupDialog(int indexOfSavedObjectList);
    void setupDialogByStore();

    //get flags num
    int getFlags();

    //direction circle / mark
    CBitmap directionCircleImage, directionMarkerImage;
 public:
    virtual BOOL OnInitDialog();
    CEdit objectFacingNum;
    afx_msg void OnPaint();

    //selected object' index (in SavedObjectList)
    int selectedObjectIndex;
    void setSelectedObjectIndex(int indexOfSavedObjectList);
    int getSelectedObjectIndex();

    //remembering nums
    map_object store;

    //store classed type (=index) combo
    void storeClassedTypeCombo(int objectType);

public:
    virtual BOOL DestroyWindow();
public:
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    void clickFacing(int px, int py);
public:
    afx_msg void OnCbnSelchangeCombo2();
public:
    afx_msg void OnCbnSelchangeCombo3();
public:
    afx_msg void OnBnClickedCheck1();
};

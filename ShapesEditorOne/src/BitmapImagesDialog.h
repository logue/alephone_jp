#pragma once

#include "SDLToWin32/SDLToWin32.h"
#include "afxwin.h"
#include "afxcmn.h"

// CBitmapImagesDialog ダイアログ

class CBitmapImagesDialog : public CDialog
{
	DECLARE_DYNAMIC(CBitmapImagesDialog)

public:
	CBitmapImagesDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CBitmapImagesDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_BITMAP_IMAGES };

    SDLToWindows* sdlToWinScreen;
    CWnd *parent;
    void setupDialog();

    //zoom
    //int zoom;

    //offset
    int offset;

    int selectBitmapIndex;
    
    //get image list canvas's rect
    void getImageRect(CRect* rect);

    //search index mouse point is in
    int getIndexPointIn(int px, int py);
    vector<CBitmap*> stockBitmapList;

    CBitmap bufferBitmap;
    CDC bufferDC;
    void draw(CDC *cdc);

    //get dest image rect
    void getDestRect(CRect* rect, int index, CRect& imageRect);

    //int maxHeight;

    //
    void freeBitmaps();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
public:
    virtual BOOL OnInitDialog();
public:
    int clutNum;
public:
    CComboBox clutCmb;
public:
    CSliderCtrl scrollSlider;
public:
    afx_msg void OnPaint();
public:
    afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
public:
    afx_msg void OnCbnSelchangeCombo1();
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
    CString idNum;
public:
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

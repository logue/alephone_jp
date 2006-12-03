#pragma once

#include "SDLToWin32/SDLToWin32.h"
#include "afxwin.h"

// CSequencesDialog ダイアログ

class CSequencesDialog : public CDialog
{
	DECLARE_DYNAMIC(CSequencesDialog)

public:
	CSequencesDialog(CWnd* pParent = NULL);   // 標準コンストラクタ
	virtual ~CSequencesDialog();

// ダイアログ データ
	enum { IDD = IDD_DIALOG_SEQUENCES };

    SDLToWindows* sdlToWinScreen;
    CWnd *parent;
    void setupDialog();
    void setupHighLevelData();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnPaint();
public:
    CComboBox collectionCmb;
public:
    CEdit versionNum;
public:
    CComboBox typeCmb;
public:
    CEdit flagNum;
public:
    CEdit colorCountNum;
public:
    CEdit CLUTCountNum;
public:
    CEdit colorTableOffsetNum;
public:
    CEdit highLevelShapeCountNum;
public:
    CEdit highLevelShapeOffsetTableOffsetNum;
public:
    CEdit lowLevelShapeCountNum;
public:
    CEdit lowLevelShapeOffsetTableOffsetNum;
public:
    CEdit bitmapCountNum;
public:
    CEdit bitmapOffsetTableOffset;
public:
    CEdit pixelsToWorldNum;
public:
    CEdit sizeNum;
public:
    CComboBox highLevelShapeIndexCmb;
public:
    afx_msg void OnCbnSelchangeCombo1();
public:
    afx_msg void OnCbnSelchangeCombo3();
public:
    CEdit highNumberOfViews;
public:
    CEdit highFramesPerView;
public:
    CEdit highTicksPerView;
public:
    CEdit highKeyFrame;
public:
    CEdit highTransferMode;
public:
    CEdit highPeriod;
public:
    CComboBox highFirstFrameSound;
public:
    CComboBox highKeyFrameSound;
public:
    CComboBox highLastFrameSound;
public:
    CEdit highPixelsToWorld;
public:
    CEdit highLoopFrames;
};

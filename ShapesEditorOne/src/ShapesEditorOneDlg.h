// ShapesEditorOneDlg.h : header file
//

#pragma once

#include "BitmapsDialog.h"
/*
#include "BitmapImageDialog.h"
#include "BitmapsDialog.h"
*/
#include "SequencesDialog.h"
#include "afxwin.h"

//show/hide
enum{
    eDialogShowBitmaps,
    eDialogShowSequences,
};

// CShapesEditorOneDlg dialog
class CShapesEditorOneDlg : public CDialog
{
// Construction
public:
	CShapesEditorOneDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SHAPESEDITORONE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
    //init app
    bool initialize();

    int showMode;
    
    //setup show/hide dialog
    void setupDialog();

    CBitmapsDialog bitmapsDialog;
    CSequencesDialog sequencesDialog;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    //CButton bitmapSelect;
    //CButton sequenceSelect;
    int bitmapSelect;
    int sequencesSelect;
    afx_msg void OnBnClickedRadio1();
    afx_msg void OnBnClickedRadio2();
};

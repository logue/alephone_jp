#pragma once
#include "afxwin.h"


// CSelectPolygonDialog �_�C�A���O

class CSelectPolygonDialog : public CDialog
{
	DECLARE_DYNAMIC(CSelectPolygonDialog)

public:
	CSelectPolygonDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CSelectPolygonDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_SELECT_POLYGON };

    //what number of points polygon have?
    //3,4,5,6,7,8
    int pointsOfPolygon;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
public:
    CButton polygon3;
public:
    CButton polygon4;
public:
    CButton polygon5;
public:
    CButton polygon6;
public:
    CButton polygon7;
public:
    CButton polygon8;
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
    afx_msg void OnBnClickedButton1();
public:
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();
    afx_msg void OnBnClickedButton4();
    afx_msg void OnBnClickedButton5();
    afx_msg void OnBnClickedButton6();
};

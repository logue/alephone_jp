#pragma once
#include "afxwin.h"

#include "ColorCustomizeDialog.h"

// CEditorInforDialog �_�C�A���O

class CEditorInforDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditorInforDialog)

public:
	CEditorInforDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CEditorInforDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_EDITOR_INFO };

public:
    //color settings for custom
    ColorSettings colorSetting;

    //when select customize not initial
    bool isInitialSelect;

    int gridIndex;

    bool flags[NUMBER_OF_EDITOR_FLAGS];
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    CComboBox gridSizeCmb;
public:
    CButton editorFlags[NUMBER_OF_EDITOR_FLAGS];
public:
    CComboBox colorSetCmb;
public:
    virtual BOOL OnInitDialog();
public:
    afx_msg void OnBnClickedButton1();
public:
    afx_msg void OnCbnSelchangeCombo2();
public:
    afx_msg void OnCbnSelchangeCombo1();
public:
    afx_msg void OnBnClickedCheck1();
};

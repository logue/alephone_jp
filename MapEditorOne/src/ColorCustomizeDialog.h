#pragma once

#include "MapEditorOneSetting.h"

// CColorCustomizeDialog �_�C�A���O

class CColorCustomizeDialog : public CDialog
{
	DECLARE_DYNAMIC(CColorCustomizeDialog)

public:
	CColorCustomizeDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CColorCustomizeDialog();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_COLOR_CUSTOMIZE };

    ColorSettings colorSetting;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
};

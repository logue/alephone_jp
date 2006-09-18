#pragma once

#include "AlephOne/SDL.h"
#include "MapEditorSDI.h"
#include "SDLToWin32/SDLToWin32.h"

// CVisualDialog �_�C�A���O

class CVisualDialog : public CDialog
{
	DECLARE_DYNAMIC(CVisualDialog)

public:
	CVisualDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^
	virtual ~CVisualDialog();

    //sdl to win api
	SDLToWindows *m_SDLToWindows;

// �_�C�A���O �f�[�^
	enum { IDD = IDD_DIALOG_VISUAL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnPaint();
public:
    virtual BOOL OnInitDialog();
};

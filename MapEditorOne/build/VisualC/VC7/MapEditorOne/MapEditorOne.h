// MapEditorOne.h : MapEditorOne �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error ���̃t�@�C���� PCH �Ɋ܂߂�O�ɁA'stdafx.h' ���܂߂Ă��������B
#endif

#include "resource.h"       // ���C�� �V���{��


// CMapEditorOneApp:
// ���̃N���X�̎����ɂ��ẮAMapEditorOne.cpp ���Q�Ƃ��Ă��������B
//

class CMapEditorOneApp : public CWinApp
{
public:
	CMapEditorOneApp();


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();

// ����
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMapEditorOneApp theApp;

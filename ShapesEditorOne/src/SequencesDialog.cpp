// SequencesDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "SequencesDialog.h"


// CSequencesDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CSequencesDialog, CDialog)
CSequencesDialog::CSequencesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSequencesDialog::IDD, pParent)
{
}

CSequencesDialog::~CSequencesDialog()
{
}

void CSequencesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSequencesDialog, CDialog)
END_MESSAGE_MAP()


// CSequencesDialog ���b�Z�[�W �n���h��

BOOL CSequencesDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

BOOL CSequencesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
    setupDialog();
    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CSequencesDialog::setupDialog()
{
    UpdateData();

}

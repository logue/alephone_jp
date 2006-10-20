// BitmapImagesDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapImagesDialog.h"


// CBitmapImagesDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CBitmapImagesDialog, CDialog)
CBitmapImagesDialog::CBitmapImagesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapImagesDialog::IDD, pParent)
    , clutNum(0)
{
}

CBitmapImagesDialog::~CBitmapImagesDialog()
{
}

void CBitmapImagesDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT1, clutNum);
    DDX_Control(pDX, IDC_COMBO1, clutCmb);
}


BEGIN_MESSAGE_MAP(CBitmapImagesDialog, CDialog)
END_MESSAGE_MAP()


// CBitmapImagesDialog ���b�Z�[�W �n���h��

BOOL CBitmapImagesDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    parent = pParentWnd;
    return CDialog::Create(lpszTemplateName, pParentWnd);
}

BOOL CBitmapImagesDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������

    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CBitmapImagesDialog::setupDialog()
{
    Invalidate(FALSE);
}
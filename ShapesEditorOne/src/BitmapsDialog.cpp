// BitmapsDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "ShapesEditorOne.h"
#include "BitmapsDialog.h"
#include ".\bitmapsdialog.h"


// CBitmapsDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CBitmapsDialog, CDialog)
CBitmapsDialog::CBitmapsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapsDialog::IDD, pParent)
{
}

CBitmapsDialog::~CBitmapsDialog()
{
}

void CBitmapsDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, showTypeCmb);
}


BEGIN_MESSAGE_MAP(CBitmapsDialog, CDialog)
    ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CBitmapsDialog ���b�Z�[�W �n���h��

void CBitmapsDialog::setupDialog()
{
    bitmapImagesDialog.ShowWindow(showMode == eBitmapDialogImages? SW_SHOW : SW_HIDE);
    bitmapCLUTDialog.ShowWindow(showMode == eBitmapDialogCLUT? SW_SHOW : SW_HIDE);

    int sel = showTypeCmb.GetCurSel();

    UpdateData();
}
BOOL CBitmapsDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO :  �����ɏ�������ǉ����Ă�������
    bitmapImagesDialog.Create(CBitmapImagesDialog::IDD, this);
    bitmapCLUTDialog.Create(CBitmapCLUTDialog::IDD, this);

    CRect parentRect;
    this->GetWindowRect(&parentRect);
    parentRect.top = 20;
    bitmapImagesDialog.MoveWindow(&parentRect);
    bitmapCLUTDialog.MoveWindow(&parentRect);

    showTypeCmb.SetCurSel(0);

    setupDialog();
    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CBitmapsDialog::OnCbnSelchangeCombo1()
{
    // TODO : �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
    int sel = showTypeCmb.GetCurSel();
    showMode = sel;
    setupDialog();
}

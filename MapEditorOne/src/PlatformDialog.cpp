// PlatformDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "PlatformDialog.h"


// CPlatformDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CPlatformDialog, CDialog)

CPlatformDialog::CPlatformDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPlatformDialog::IDD, pParent)
{

}

CPlatformDialog::~CPlatformDialog()
{
}

void CPlatformDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, typeCmb);
}


BEGIN_MESSAGE_MAP(CPlatformDialog, CDialog)
END_MESSAGE_MAP()


// CPlatformDialog ���b�Z�[�W �n���h��

BOOL CPlatformDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �����ɏ�������ǉ����Ă�������
    //store speed
    //store delay
    
    //set nums

    return TRUE;  // return TRUE unless you set the focus to a control
    // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

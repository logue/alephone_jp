// SaveCheckDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "SaveCheckDialog.h"


// CSaveCheckDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CSaveCheckDialog, CDialog)

CSaveCheckDialog::CSaveCheckDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveCheckDialog::IDD, pParent)
{

}

CSaveCheckDialog::~CSaveCheckDialog()
{
}

void CSaveCheckDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveCheckDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CSaveCheckDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CSaveCheckDialog ���b�Z�[�W �n���h��

void CSaveCheckDialog::OnBnClickedOk()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	OnOK();
}

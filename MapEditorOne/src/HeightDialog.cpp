// HeightDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "HeightDialog.h"


// CHeightDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CHeightDialog, CDialog)

CHeightDialog::CHeightDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CHeightDialog::IDD, pParent)
{

}

CHeightDialog::~CHeightDialog()
{
}

void CHeightDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHeightDialog, CDialog)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CHeightDialog ���b�Z�[�W �n���h��
// CMonsterPropertyDialog ���b�Z�[�W �n���h��
BOOL CHeightDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CHeightDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CHeightDialog::PostNcDestroy()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CHeightDialog::OnClose()
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CHeightDialog::DestroyWindow()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    //�\������������
    theApp.isHeightDialogShow = FALSE;
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

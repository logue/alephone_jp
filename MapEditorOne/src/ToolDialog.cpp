// ToolDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "ToolDialog.h"
#include ".\tooldialog.h"


// CToolDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CToolDialog, CDialog)
CToolDialog::CToolDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CToolDialog::IDD, pParent)
{
}

CToolDialog::~CToolDialog()
{
}

void CToolDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CToolDialog, CDialog)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CToolDialog ���b�Z�[�W �n���h��

BOOL CToolDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CToolDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CToolDialog::PostNcDestroy()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CToolDialog::OnClose()
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CToolDialog::DestroyWindow()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    theApp.isToolDialogShow = FALSE;
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

// SidePropertyDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "SidePropertyDialog.h"


// CSidePropertyDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CSidePropertyDialog, CDialog)

CSidePropertyDialog::CSidePropertyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSidePropertyDialog::IDD, pParent)
{

}

CSidePropertyDialog::~CSidePropertyDialog()
{
}

void CSidePropertyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSidePropertyDialog, CDialog)
END_MESSAGE_MAP()


// CSidePropertyDialog ���b�Z�[�W �n���h��

BOOL CSidePropertyDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CSidePropertyDialog::IDD, parent);

    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(TEXT("Failed"));
    }
    return ret;
}

void CSidePropertyDialog::PostNcDestroy()
{
    // TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CSidePropertyDialog::OnClose()
{
    // TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}
void CSidePropertyDialog::setupDialog(int index_)
{
    if(index_ < 0 || index_ >= (int)EndpointList.size()){
        char cstr[256];
        sprintf(cstr, "illigal polygon index:%d", index_);
        MessageBox(CString(cstr));
        return;
    }
    //point index
    index = index_;
    endpoint_data *p = get_endpoint_data(index);
    memcpy(&store, p, sizeof(endpoint_data));

    setupDialogByStore();
}

void CSidePropertyDialog::setupDialogByStore()
{
}

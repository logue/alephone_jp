// SidePropertyDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "SidePropertyDialog.h"


// CSidePropertyDialog ダイアログ

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


// CSidePropertyDialog メッセージ ハンドラ

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
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CSidePropertyDialog::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
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

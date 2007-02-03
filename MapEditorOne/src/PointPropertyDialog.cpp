// PointPropertyDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "PointPropertyDialog.h"


// CPointPropertyDialog ダイアログ

IMPLEMENT_DYNAMIC(CPointPropertyDialog, CDialog)

CPointPropertyDialog::CPointPropertyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPointPropertyDialog::IDD, pParent)
    , flagSolid(false)
    , flagTransparent(false)
{

}

CPointPropertyDialog::~CPointPropertyDialog()
{
}

void CPointPropertyDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CHECK3, flagElevation);
    DDX_Control(pDX, IDC_EDIT1, pointFloor);
    DDX_Control(pDX, IDC_EDIT6, pointHeight);
    DDX_Control(pDX, IDC_EDIT8, pointVertexX);
    DDX_Control(pDX, IDC_EDIT9, pointVertexY);
    DDX_Control(pDX, IDC_EDIT10, pointTransX);
    DDX_Control(pDX, IDC_EDIT11, pointTransY);
    DDX_Control(pDX, IDC_EDIT13, pointSupPolygonIndex);
}


BEGIN_MESSAGE_MAP(CPointPropertyDialog, CDialog)
END_MESSAGE_MAP()


// CPointPropertyDialog メッセージ ハンドラ

BOOL CPointPropertyDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CPointPropertyDialog::IDD, parent);

    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CPointPropertyDialog::PostNcDestroy()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CPointPropertyDialog::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}
void CPointPropertyDialog::setupDialog(int index_)
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

void CPointPropertyDialog::setupDialogByStore()
{
}

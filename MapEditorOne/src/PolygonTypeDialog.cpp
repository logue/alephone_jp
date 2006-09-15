// PolygonTypeDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "PolygonTypeDialog.h"


// CPolygonTypeDialog ダイアログ

IMPLEMENT_DYNAMIC(CPolygonTypeDialog, CDialog)

CPolygonTypeDialog::CPolygonTypeDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPolygonTypeDialog::IDD, pParent)
{

}

CPolygonTypeDialog::~CPolygonTypeDialog()
{
}

void CPolygonTypeDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST2, polygonTypeListCtrl);
}


BEGIN_MESSAGE_MAP(CPolygonTypeDialog, CDialog)
    ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPolygonTypeDialog メッセージ ハンドラ

BOOL CPolygonTypeDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    polygonTypeListCtrl.InsertItem(0, L"標準", IDI_ICON_POLYGON_NORMAL);
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CPolygonTypeDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CPolygonTypeDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CPolygonTypeDialog::PostNcDestroy()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CPolygonTypeDialog::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CPolygonTypeDialog::DestroyWindow()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    theApp.isPolygonTypeDialogShow = FALSE;
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

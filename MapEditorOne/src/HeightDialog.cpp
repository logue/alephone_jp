// HeightDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "HeightDialog.h"


// CHeightDialog ダイアログ

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


// CHeightDialog メッセージ ハンドラ
// CMonsterPropertyDialog メッセージ ハンドラ
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
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CHeightDialog::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CHeightDialog::DestroyWindow()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    //表示を消すだけ
    theApp.isHeightDialogShow = FALSE;
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

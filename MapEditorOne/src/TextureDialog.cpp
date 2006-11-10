// TextureDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "TextureDialog.h"
#include ".\texturedialog.h"


// CTextureDialog ダイアログ

IMPLEMENT_DYNAMIC(CTextureDialog, CDialog)
CTextureDialog::CTextureDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureDialog::IDD, pParent)
{
}

CTextureDialog::~CTextureDialog()
{
}

void CTextureDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, typeCmb);
}


BEGIN_MESSAGE_MAP(CTextureDialog, CDialog)
    ON_WM_CLOSE()
    ON_WM_PAINT()
END_MESSAGE_MAP()


// CTextureDialog メッセージ ハンドラ

BOOL CTextureDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO :  ここに初期化を追加してください
    
    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CTextureDialog::Create(CWnd* par)
{
    parent = par;
    BOOL ret = CDialog::Create(CTextureDialog::IDD, parent);
    if(ret == TRUE){
        ShowWindow(SW_SHOW);
    }else{
        MessageBox(L"Failed");
    }
    return ret;
}

void CTextureDialog::PostNcDestroy()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    if(parent != NULL){
        delete this;
    }

    CDialog::PostNcDestroy();
}

void CTextureDialog::OnClose()
{
    // TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
    if(parent != NULL){
        DestroyWindow();
    }else{
        CDialog::OnClose();
    }
}

BOOL CTextureDialog::DestroyWindow()
{
    // TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
    ShowWindow(FALSE);
    return TRUE;//CDialog::DestroyWindow();
}

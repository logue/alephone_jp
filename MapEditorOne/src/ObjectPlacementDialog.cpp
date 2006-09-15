// ObjectPlacementDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "ObjectPlacementDialog.h"


// CObjectPlacementDialog ダイアログ

IMPLEMENT_DYNAMIC(CObjectPlacementDialog, CDialog)

CObjectPlacementDialog::CObjectPlacementDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectPlacementDialog::IDD, pParent)
{

}

CObjectPlacementDialog::~CObjectPlacementDialog()
{
}

void CObjectPlacementDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CObjectPlacementDialog, CDialog)
END_MESSAGE_MAP()


// CObjectPlacementDialog メッセージ ハンドラ

BOOL CObjectPlacementDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    //リストコントロールに流し込む

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

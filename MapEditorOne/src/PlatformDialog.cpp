// PlatformDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "PlatformDialog.h"


// CPlatformDialog ダイアログ

IMPLEMENT_DYNAMIC(CPlatformDialog, CDialog)

CPlatformDialog::CPlatformDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CPlatformDialog::IDD, pParent)
{

}

CPlatformDialog::~CPlatformDialog()
{
}

void CPlatformDialog::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COMBO1, typeCmb);
}


BEGIN_MESSAGE_MAP(CPlatformDialog, CDialog)
END_MESSAGE_MAP()


// CPlatformDialog メッセージ ハンドラ

BOOL CPlatformDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  ここに初期化を追加してください
    //store speed
    //store delay
    
    //set nums

    return TRUE;  // return TRUE unless you set the focus to a control
    // 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

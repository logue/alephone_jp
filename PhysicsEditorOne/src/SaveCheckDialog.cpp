// SaveCheckDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "PhysicsEditor.h"
#include "SaveCheckDialog.h"


// CSaveCheckDialog ダイアログ

IMPLEMENT_DYNAMIC(CSaveCheckDialog, CDialog)

CSaveCheckDialog::CSaveCheckDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CSaveCheckDialog::IDD, pParent)
{

}

CSaveCheckDialog::~CSaveCheckDialog()
{
}

void CSaveCheckDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveCheckDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CSaveCheckDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CSaveCheckDialog メッセージ ハンドラ

void CSaveCheckDialog::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	OnOK();
}

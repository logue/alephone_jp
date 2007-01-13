// HeightPalletDialog.cpp : 実装ファイル
//

#include "stdafx.h"
#include "MapEditorSDI.h"
#include "HeightPalletDialog.h"


// CHeightPalletDialog ダイアログ

IMPLEMENT_DYNAMIC(CHeightPalletDialog, CDialog)

CHeightPalletDialog::CHeightPalletDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CHeightPalletDialog::IDD, pParent)
{

}

CHeightPalletDialog::~CHeightPalletDialog()
{
}

void CHeightPalletDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHeightPalletDialog, CDialog)
END_MESSAGE_MAP()


// CHeightPalletDialog メッセージ ハンドラ
